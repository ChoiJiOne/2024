#include "IApplication.h"

#include "EastWall.h"
#include "Floor.h"
#include "MovableCamera.h"
#include "NorthWall.h"
#include "Player.h"
#include "SouthWall.h"
#include "StaticLight.h"
#include "WestWall.h"


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
		MovableCamera* camera = ObjectManager::Get().CreateObject<MovableCamera>("MainCamera");
		camera->Initialize();

		StaticLight* light = ObjectManager::Get().CreateObject<StaticLight>("GlobalLight");
		light->Initialize();

		Floor* floor = ObjectManager::Get().CreateObject<Floor>("Floor");
		floor->Initialize();

		Player* player = ObjectManager::Get().CreateObject<Player>("Player");
		player->Initialize();

		NorthWall* northWall = ObjectManager::Get().CreateObject<NorthWall>("NorthWall");
		northWall->Initialize();

		SouthWall* southWall = ObjectManager::Get().CreateObject<SouthWall>("SouthWall");
		southWall->Initialize();

		WestWall* westWall = ObjectManager::Get().CreateObject<WestWall>("WestWall");
		westWall->Initialize();

		EastWall* eastWall = ObjectManager::Get().CreateObject<EastWall>("EastWall");
		eastWall->Initialize();

		ShadowShader* shadowShader = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
		LightShader* lightShader = ResourceManager::Get().GetResource<LightShader>("LightShader");

		const uint32_t SHADOW_WIDTH = 1024;
		const uint32_t SHADOW_HEIGHT = 1024;
		ShadowMap* shadowMap = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
		shadowMap->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);
		
		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			player->Tick(timer_.GetDeltaSeconds());
			floor->Tick(timer_.GetDeltaSeconds());
			northWall->Tick(timer_.GetDeltaSeconds());
			southWall->Tick(timer_.GetDeltaSeconds());
			westWall->Tick(timer_.GetDeltaSeconds());
			eastWall->Tick(timer_.GetDeltaSeconds());
			camera->Tick(timer_.GetDeltaSeconds());
			light->Tick(timer_.GetDeltaSeconds());
			
			{// ���� �� �׸���
				RenderManager::Get().SetDepthMode(true);
				RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

				shadowMap->Bind();
				shadowMap->Clear();

				shadowShader->Bind();
				shadowShader->SetLight(light);

				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(floor->GetPosition()),  floor->GetMesh());
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(northWall->GetPosition()), northWall->GetMesh());
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(southWall->GetPosition()), southWall->GetMesh());
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(westWall->GetPosition()), westWall->GetMesh());
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(eastWall->GetPosition()), eastWall->GetMesh());
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(player->GetPosition()), player->GetMesh());

				shadowShader->Unbind();
				shadowMap->Unbind();
			}

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			{ // �� �׸���
				RenderManager::Get().SetWindowViewport();

				lightShader->Bind();
				lightShader->SetLight(light);
				lightShader->SetCamera(camera);

				lightShader->SetMaterial(floor->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(floor->GetPosition()), floor->GetMesh(), shadowMap);

				lightShader->SetMaterial(northWall->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(northWall->GetPosition()), northWall->GetMesh(), shadowMap);

				lightShader->SetMaterial(southWall->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(southWall->GetPosition()), southWall->GetMesh(), shadowMap);

				lightShader->SetMaterial(westWall->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(westWall->GetPosition()), westWall->GetMesh(), shadowMap);

				lightShader->SetMaterial(eastWall->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(eastWall->GetPosition()), eastWall->GetMesh(), shadowMap);
				
				lightShader->SetMaterial(player->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(player->GetPosition()), player->GetMesh(), shadowMap);

				lightShader->Unbind();
			}

			RenderManager::Get().RenderAxisAlignedBoundingBox3D(
				camera,
				northWall->GetBoundingVolume().GetCenter(),
				northWall->GetBoundingVolume().GetExtents(),
				Vector4f(1.0f, 0.0f, 0.0f, 1.0f)
			);

			RenderManager::Get().RenderAxisAlignedBoundingBox3D(
				camera,
				southWall->GetBoundingVolume().GetCenter(),
				southWall->GetBoundingVolume().GetExtents(),
				Vector4f(0.0f, 0.0f, 1.0f, 1.0f)
			);
			RenderManager::Get().RenderAxisAlignedBoundingBox3D(
				camera,
				westWall->GetBoundingVolume().GetCenter(),
				westWall->GetBoundingVolume().GetExtents(),
				Vector4f(0.0f, 1.0f, 0.0f, 1.0f)
			);
			RenderManager::Get().RenderAxisAlignedBoundingBox3D(
				camera,
				eastWall->GetBoundingVolume().GetCenter(),
				eastWall->GetBoundingVolume().GetExtents(),
				Vector4f(1.0f, 1.0f, 0.0f, 1.0f)
			);
			RenderManager::Get().RenderWireframeSphere3D(camera, player->GetBoundingVolume().GetCenter(), player->GetBoundingVolume().GetRadius(), Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
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