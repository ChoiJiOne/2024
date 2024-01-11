#include "IApplication.h"

#include "DirectionalLightShader.h"
#include "Properties.h"


/**
 * @brief Geometry ���� �� ���ø����̼��Դϴ�.
 */
class GeometryExporterApp : public IApplication
{
public:
	/**
	 * @brief ���� �� ���ø����̼��� ����Ʈ �������Դϴ�.
	 */
	GeometryExporterApp() = default;


	/**
	 * @brief ���� �� ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GeometryExporterApp()
	{
		Shutdown();
	}


	/**
	 * @brief ���� �� ���ø����̼��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryExporterApp);


	/**
	 * @brief ���� �� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		toolPath_ = rootPath_ + L"GeometryExporter/";
	}


	/**
	 * @brief ���� �� �����ӿ�ũ ����� �����մϴ�.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief ���� �� �����ӿ�ũ�� �����մϴ�.
	 */
	virtual void Run() override
	{
		Camera3D* camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
		camera->Initialize(
			Vector3f(0.0f, 5.0f, 5.0f),
			Vector3f(0.0f, -1.0f, -1.0f),
			Vector3f(0.0f, 1.0f, 0.0f),
			MathUtils::ToRadian(45.0f),
			window_->GetAspectSize(),
			0.01f,
			1000.0f
		);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);

		StaticMesh* sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
		sphere->Initialize(vertices, indices);

		Material* material = ResourceManager::Get().CreateResource<Material>("material");
		material->Initialize(
			Vector3f(0.329412f, 0.223529f, 0.027451f),
			Vector3f(0.780392f, 0.568627f, 0.113725f),
			Vector3f(0.992157f, 0.941176f, 0.807843f),
			128.0f * 0.21794872f
		);

		DirectionalLightShader* directionalLightShader = ResourceManager::Get().CreateResource<DirectionalLightShader>("DirectionalLightShader");
		directionalLightShader->Initialize(toolPath_ + L"Shader/DirectionalLight.vert", toolPath_ + L"Shader/DirectionalLight.frag");

		Properties* properties = ObjectManager::Get().CreateObject<Properties>("Properties");
		properties->Initialize();

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();
			
			properties->Tick(timer_.GetDeltaSeconds());
			
			RenderManager::Get().SetWindowViewport();
			RenderManager::Get().SetDepthMode(true);
			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			
			directionalLightShader->Bind();
			directionalLightShader->SetCamera(camera);
			directionalLightShader->SetMaterial(material);
			directionalLightShader->SetDirectionalLight(properties->GetDirectionalLight());

			directionalLightShader->DrawMesh3D(Matrix4x4f::GetIdentity(), sphere);

			directionalLightShader->Unbind();

			RenderManager::Get().RenderGrid3D(
				camera->GetViewMatrix(), camera->GetProjectionMatrix(),
				-10.0f, +10.0f, 1.0f, -10.0f, +10.0f, 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f)
			);
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief �� ����Դϴ�.
	 */
	std::wstring toolPath_;


	/**
	 * @brief Ÿ�̸��Դϴ�.
	 */
	GameTimer timer_;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> app = std::make_unique<GeometryExporterApp>();
	app->Setup();
	app->Run();
	app->Shutdown();
	return 0;
}