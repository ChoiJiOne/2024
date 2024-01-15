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
		Box3D aabb0(Vector3f(-2.0f, 0.0f, -2.0f), Vector3f(1.0f, 1.0f, 1.0f));
		Box3D aabb1(Vector3f(+2.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
		
		Camera3D* camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
		camera->Initialize(
			Vector3f(0.0f, 5.0f, 5.0f),
			Vector3f(0.0f, -1.0f, -1.0f),
			Vector3f(0.0f, 1.0f, 0.0f),
			MathUtils::ToRadian(45.0f),
			window_->GetAspectSize(),
			0.1f,
			100.0f
		);


		Vector4f collision;

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_RIGHT) == EPressState::Pressed)
			{
				Vector3f center0 = aabb0.GetCenter();
				center0.x += 0.1f;
				center0.z += 0.1f;
				aabb0.SetCenter(center0);
			}
			
			collision = aabb0.IsCollision(aabb1) ? Vector4f(1.0f, 0.0f, 0.0f, 1.0f) : Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderManager::Get().SetWindowViewport();

			RenderManager::Get().RenderAxisAlignedBoundingBox3D(camera, aabb0.GetCenter(), aabb0.GetExtents(), collision);
			RenderManager::Get().RenderAxisAlignedBoundingBox3D(camera, aabb1.GetCenter(), aabb1.GetExtents(), collision);

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