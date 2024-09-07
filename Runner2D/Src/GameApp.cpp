#include "Assertion.h"
#include "Atlas2D.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "TTFont.h"

#include "Background.h"
#include "Box.h"
#include "Button.h"
#include "Camera.h"
#include "Floor.h"
#include "GameApp.h"
#include "Player.h"
#include "PlayerMessenger.h"
#include "RewardViewer.h"
#include "Spawner.h"
#include "Title.h"

GameApp::GameApp() : IApp("Runner2D", 100, 100, 800, 600, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	LoadResource();

	Camera* camera = EntityManager::Get().Create<Camera>();
	EntityManager::Get().Register("Camera", camera);

	Player* player = EntityManager::Get().Create<Player>();
	EntityManager::Get().Register("Player", player);

	Background* background = EntityManager::Get().Create<Background>();
	EntityManager::Get().Register("Background", background);

	Floor* floor = EntityManager::Get().Create<Floor>();
	EntityManager::Get().Register("Floor", floor);

	Spawner* spawner = EntityManager::Get().Create<Spawner>();
	EntityManager::Get().Register("Spawner", spawner);

	PlayerMessenger* playerMessenger = EntityManager::Get().Create<PlayerMessenger>();
	EntityManager::Get().Register("PlayerMessenger", playerMessenger);

	RewardViewer* rewardViewer = EntityManager::Get().Create<RewardViewer>();
	EntityManager::Get().Register("RewardViewer", rewardViewer);

	Title* title = EntityManager::Get().Create<Title>();
	EntityManager::Get().Register("Title", title);

	Button::Layout layout;
	layout.textColor = GameMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	layout.disableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	layout.enableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	layout.pressColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	layout.releaseColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	layout.center = GameMath::Vec2f(0.0f, -100.0f);
	layout.size = GameMath::Vec2f(200.0f, 50.0f);
	layout.mouse = Mouse::LEFT;
	layout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	layout.text = L"START!";
	layout.side = 10.0f;
	Button* startButton = EntityManager::Get().Create<Button>(layout, [&]() { OutputDebugString("HELLO!\n"); });
	EntityManager::Get().Register("Button", startButton);

	camera_ = camera;

	StatusEntities readyEntities;
	readyEntities.updateEntities = { camera, background, startButton, title, };
	readyEntities.renderEntities = { background, startButton, title, };
	statusEntities_.insert({ EStatus::READY, readyEntities });

	StatusEntities playEntities;
	playEntities.updateEntities = { camera, player, floor, spawner, playerMessenger, rewardViewer, };
	playEntities.renderEntities = { background, floor, spawner, player, playerMessenger, rewardViewer, };
	statusEntities_.insert({ EStatus::PLAY, playEntities });
}

void GameApp::Shutdown()
{
	EntityManager::Get().Destroy(camera_);
	camera_ = nullptr;
}

void GameApp::Run()
{
	RunLoop(
		[&](float deltaSeconds)
		{
			StatusEntities& statusEntities = statusEntities_.at(status_);
			for (auto& entity : statusEntities.updateEntities)
			{
				entity->Tick(deltaSeconds);
			}

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderManager2D::Get().Begin(camera_);
			{
				for (auto& entity : statusEntities.renderEntities)
				{
					entity->Render();
				}
			}
			RenderManager2D::Get().End();
			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	resourceRootPath_ = "Runner2D\\Res\\";
	
	Atlas2D* atlas = ResourceManager::Get().Create<Atlas2D>(resourceRootPath_ + "Atlas\\Atlas.png", resourceRootPath_ + "Atlas\\Atlas.json", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Atlas", atlas);

	std::string fontPath = resourceRootPath_ + "Font\\Yolk.ttf";
	std::array<int32_t, 4> fontSizes = { 16, 24, 32, 64 };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0, 9660, static_cast<float>(fontSize));
		ResourceManager::Get().Register(GameUtils::PrintF("Font%d", fontSize), font);
	}

	TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0x00, 0x128, 128.0f);
	ResourceManager::Get().Register("Font128", font);
}