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
		int32_t width;
		int32_t height;
		window_->GetSize(width, height);

		shadowShader = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
		lightShader = ResourceManager::Get().GetResource<LightShader>("LightShader");
		inversionEffect = ResourceManager::Get().GetResource<PostEffectShader>("InversionEffect");
		grayscaleEffect = ResourceManager::Get().GetResource<PostEffectShader>("GrayscaleEffect");
		gaussianBlurEffect = ResourceManager::Get().GetResource<PostEffectShader>("GaussianBlurEffect");
		fadeEffect = ResourceManager::Get().GetResource<PostEffectShader>("FadeEffect");

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;;

		floor = ResourceManager::Get().CreateResource<StaticMesh>("floor");
		GeometryGenerator::CreateCube(Vector3f(50.0f, 1.0f, 50.0f), vertices, indices);
		floor->Initialize(vertices, indices);

		cube = ResourceManager::Get().CreateResource<StaticMesh>("cube");
		GeometryGenerator::CreateCube(Vector3f(2.0f, 2.0f, 2.0f), vertices, indices);
		cube->Initialize(vertices, indices);

		sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
		GeometryGenerator::CreateSphere(0.5f, 30, vertices, indices);
		sphere->Initialize(vertices, indices);

		material = ResourceManager::Get().CreateResource<Material>("material");
		material->Initialize(
			Vector3f(0.329412f, 0.223529f, 0.027451f),
			Vector3f(0.780392f, 0.568627f, 0.113725f),
			Vector3f(0.992157f, 0.941176f, 0.807843f),
			128.0f * 0.21794872f
		);

		framebuffer = ResourceManager::Get().CreateResource<Framebuffer>("framebuffer");
		framebuffer->Initialize(width, height);

		shadowMap = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
		shadowMap->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

		camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
		camera->Initialize(
			Vector3f(0.0f, 20.0f, 20.0f),
			Vector3f(0.0f, -1.0f, -1.0f),
			Vector3f(0.0f, 1.0f, 0.0f),
			MathUtils::ToRadian(45.0f),
			window_->GetAspectSize(),
			0.1f,
			100.0f
		);

		light = ObjectManager::Get().CreateObject<Light>("light");
		light->Initialize(
			Vector3f(-10.0f, +10.0f, 0.0f),
			Vector3f(1.0f, -1.0f, 0.0f),
			Vector3f(0.5f, 0.5f, 0.5f),
			Vector3f(0.5f, 0.5f, 0.5f),
			Vector3f(1.0f, 1.0f, 1.0f),
			Vector3f(0.0f, 0.0f, +1.0f),
			MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, 0.1f, 100.0f)
		);

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			RenderManager::Get().SetDepthMode(true);
			{// 1. 
				RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
				shadowMap->Bind();
				shadowMap->Clear();

				shadowShader->Bind();
				shadowShader->SetLight(light);
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(0.0f, 0.0f, 0.0f)), floor);

				for (float x = -2.0f; x <= 2.0f; x += 1.0f)
				{
					for (float z = -2.0f; z <= 2.0f; z += 1.0f)
					{
						shadowShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(x, 1.0f, z)), sphere);
					}
				}

				shadowShader->Unbind();
				shadowMap->Unbind();
			}
			{// 2. 
				RenderManager::Get().SetWindowViewport();
				framebuffer->Bind();
				framebuffer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

				lightShader->Bind();
				lightShader->SetLight(light);
				lightShader->SetMaterial(material);
				lightShader->SetCamera(camera);
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(0.0f, 0.0f, 0.0f)), floor, shadowMap);

				for (float x = -2.0f; x <= 2.0f; x += 1.0f)
				{
					for (float z = -2.0f; z <= 2.0f; z += 1.0f)
					{
						lightShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(x, 1.0f, z)), sphere, shadowMap);
					}
				}

				lightShader->Unbind();

				framebuffer->Unbind();
			}

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			{
				RenderManager::Get().SetViewport(0, 0, width / 2, height / 2);
				inversionEffect->Bind();
				inversionEffect->BlitEffect(framebuffer);
				inversionEffect->Unbind();
			}
			{
				RenderManager::Get().SetViewport(width / 2, 0, width / 2, height / 2);
				grayscaleEffect->Bind();
				grayscaleEffect->BlitEffect(framebuffer);
				grayscaleEffect->Unbind();
			}
			{
				RenderManager::Get().SetViewport(0, height / 2, width / 2, height / 2);
				gaussianBlurEffect->Bind();
				gaussianBlurEffect->SetUniform("blurBias", 0.5f);
				gaussianBlurEffect->BlitEffect(framebuffer);
				gaussianBlurEffect->Unbind();
			}
			{
				RenderManager::Get().SetViewport(width / 2, height / 2, width / 2, height / 2);
				fadeEffect->Bind();
				fadeEffect->SetUniform("fadeBias", std::abs(MathUtils::Sin(timer_.GetTotalSeconds())));
				fadeEffect->BlitEffect(framebuffer);
				fadeEffect->Unbind();
			}
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

	
	/**
	 * @brief ��� ���� �׽�Ʈ���Դϴ�.
	 */
	Camera3D* camera;

	ShadowShader* shadowShader;
	LightShader* lightShader;
	PostEffectShader* inversionEffect;
	PostEffectShader* grayscaleEffect;
	PostEffectShader* gaussianBlurEffect;
	PostEffectShader* fadeEffect;

	StaticMesh* floor;
	StaticMesh* cube;
	StaticMesh* sphere;
	Material* material;
	Framebuffer* framebuffer;

	ShadowMap* shadowMap;

	Light* light;

	const uint32_t SHADOW_WIDTH = 1024;
	const uint32_t SHADOW_HEIGHT = 1024;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}