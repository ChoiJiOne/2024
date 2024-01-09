#include "IApplication.h"


/**
 * @brief ���� ���ø����̼��Դϴ�.
 */
class GameApplication : public IApplication
{
public:
	/**
	 * @brief ���� ���ø����̼��� ����Ʈ �������Դϴ�.
	 */
	GameApplication() = default;


	/**
	 * @brief ���� ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameApplication()
	{
		Shutdown();
	}


	/**
	 * @brief ���� ���ø����̼��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameApplication);


	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		clientPath_ = rootPath_ + L"Client/";
	}


	/**
	 * @brief ���� �����ӿ�ũ ����� �����մϴ�.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief ���� �����ӿ�ũ�� �����մϴ�.
	 */
	virtual void Run() override
	{
		Vector3f cameraPosition = Vector3f(1.0f, 5.0f, 10.0f);

		Shader* depthShader = ResourceManager::Get().GetResource<Shader>("ShadowMap");

		Shader* shadowShader = ResourceManager::Get().CreateResource<Shader>("shadow");
		shadowShader->Initialize(clientPath_ + L"Shader/Shadow.vert", clientPath_ + L"Shader/Shadow.frag");

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;;

		StaticMesh* floor = ResourceManager::Get().CreateResource<StaticMesh>("floor");
		GeometryGenerator::CreateCube(Vector3f(50.0f, 1.0f, 50.0f), vertices, indices);
		floor->Initialize(vertices, indices);

		StaticMesh* cube = ResourceManager::Get().CreateResource<StaticMesh>("cube");
		GeometryGenerator::CreateCube(Vector3f(2.0f, 2.0f, 2.0f), vertices, indices);
		cube->Initialize(vertices, indices);

		StaticMesh* sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
		GeometryGenerator::CreateSphere(0.5f, 30, vertices, indices);
		sphere->Initialize(vertices, indices);

		const uint32_t SHADOW_WIDTH = 1024;
		const uint32_t SHADOW_HEIGHT = 1024;

		ShadowMap* shadowMap = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
		shadowMap->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

		Vector3f lightPosition = Vector3f(-4.0f, 4.0f, +0.0f);

		timer_.Reset();
		RenderManager::Get().SetVsyncMode(true);
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			float nearPlane = 0.1f;
			float farPlane = 100.0f;
			Matrix4x4f view = MathUtils::CreateLookAt(cameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), window_->GetAspectSize(), 0.1f, 100.0f);
			Matrix4x4f lightView = MathUtils::CreateLookAt(lightPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Matrix4x4f lightProjection = MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, nearPlane, farPlane);
			{
				depthShader->Bind();
				depthShader->SetUniform("lightView", lightView);
				depthShader->SetUniform("lightProjection", lightProjection);

				glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
				shadowMap->Bind();
				shadowMap->Clear();

				// 1. 
				depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, -3.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(floor);

				// 2.
				depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-1.0f, 1.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(sphere);

				// 3.
				depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 1.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(sphere);

				// 4.
				depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+1.0f, 1.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(sphere);

				shadowMap->Unbind();
				depthShader->Unbind();
			}
			{
				RenderManager::Get().SetWindowViewport();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				shadowShader->Bind();
				shadowShader->SetUniform("view", view);
				shadowShader->SetUniform("projection", projection);
				shadowShader->SetUniform("lightView", lightView);
				shadowShader->SetUniform("lightProjection", lightProjection);
				shadowShader->SetUniform("lightPosition", lightPosition);
				shadowShader->SetUniform("viewPosition", cameraPosition);

				shadowMap->Active(0);

				// 1.
				shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, -3.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(floor);

				// 2.
				shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-1.0f, 1.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(sphere);

				// 3.
				shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 1.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(sphere);

				// 4.
				shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+1.0f, 1.0f, 0.0f)));
				RenderManager::Get().RenderStaticMesh3D(sphere);

				shadowShader->Unbind();
			}

			RenderManager::Get().RenderLine3D(view, projection, Vector3f(-10.0f, 0.0f, 0.0f), Vector3f(+10.0f, 0.0f, 0.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
			RenderManager::Get().RenderLine3D(view, projection, Vector3f(0.0f, -10.0f, 0.0f), Vector3f(0.0f, +10.0f, 0.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
			RenderManager::Get().RenderLine3D(view, projection, Vector3f(0.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, +10.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
			RenderManager::Get().RenderLine3D(view, projection, Vector3f(0.0f, 0.0f, 0.0f), lightPosition, Vector4f(0.0f, 1.0f, 1.0f, 1.0f));
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief Ŭ���̾�Ʈ ����Դϴ�.
	 */
	std::wstring clientPath_;


	/**
	 * @brief ���� Ÿ�̸��Դϴ�.
	 */
	GameTimer timer_;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}