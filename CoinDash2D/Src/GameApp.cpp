#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "TTFont.h"

#include "Background.h"
#include "Button.h"
#include "Cactus.h"
#include "Camera.h"
#include "CoinSpawner.h"
#include "CoinViewer.h"
#include "CountDowner.h"
#include "Entity2D.h"
#include "GameApp.h"
#include "Player.h"
#include "PlayerMessenger.h"
#include "PowerUpCoin.h"
#include "Title.h"

GameApp::GameApp() : IApp("CoinDash2D", 100, 100, 480, 720, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	LoadResource();

	auto pauseEvent = [&]()
		{
			Player* player = EntityManager::Get().GetByName<Player>("Player");
			Player::Status status = player->GetStatus();
			if (status_ == Status::PLAY && (status != Player::Status::HURT))
			{
				status_ = Status::PAUSE;
			}
		};
	AddWindowEventAction(WindowEvent::FOCUS_LOST, pauseEvent, true);
	AddWindowEventAction(WindowEvent::MOVED, pauseEvent, true);

	camera_ = EntityManager::Get().Create<Camera>();
	EntityManager::Get().Register("Camera", camera_);

	Background* background = EntityManager::Get().Create<Background>();
	EntityManager::Get().Register("Background", background);

	Player* player = EntityManager::Get().Create<Player>();
	EntityManager::Get().Register("Player", player);

	Cactus* cactus0 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(-120.0f, +150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus0", cactus0);

	Cactus* cactus1 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(+120.0f, +150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus1", cactus1);

	Cactus* cactus2 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(-120.0f, -150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus2", cactus2);

	Cactus* cactus3 = EntityManager::Get().Create<Cactus>(Rect2D(GameMath::Vec2f(+120.0f, -150.0f), GameMath::Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus3", cactus3);

	CoinSpawner* coinSpawner = EntityManager::Get().Create<CoinSpawner>();
	EntityManager::Get().Register("CoinSpawner", coinSpawner);

	PlayerMessenger* playerMessenger = EntityManager::Get().Create<PlayerMessenger>();
	EntityManager::Get().Register("PlayerMessenger", playerMessenger);

	PowerUpCoin* powerUpCoin = EntityManager::Get().Create<PowerUpCoin>();
	EntityManager::Get().Register("PowerUpCoin", powerUpCoin);

	CountDowner* countDowner = EntityManager::Get().Create<CountDowner>();
	EntityManager::Get().Register("CountDowner", countDowner);

	CoinViewer* coinViewer = EntityManager::Get().Create<CoinViewer>();
	EntityManager::Get().Register("CoinViewer", coinViewer);

	Title* title = EntityManager::Get().Create<Title>();
	EntityManager::Get().Register("Title", title);

	Button::Layout startButtonLayout;
	startButtonLayout.textColor = GameMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	startButtonLayout.disableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	startButtonLayout.enableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	startButtonLayout.pressColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	startButtonLayout.releaseColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	startButtonLayout.center = GameMath::Vec2f(0.0f, 0.0f);
	startButtonLayout.size = GameMath::Vec2f(200.0f, 50.0f);
	startButtonLayout.mouse = Mouse::LEFT;
	startButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	startButtonLayout.text = L"START";
	startButtonLayout.side = 10.0f;
	Button* startButton = EntityManager::Get().Create<Button>(startButtonLayout, [&]() { status_ = Status::PLAY; });
	EntityManager::Get().Register("StartButton", startButton);

	Button::Layout resumeButtonLayout;
	resumeButtonLayout.textColor = GameMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	resumeButtonLayout.disableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	resumeButtonLayout.enableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	resumeButtonLayout.pressColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	resumeButtonLayout.releaseColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	resumeButtonLayout.center = GameMath::Vec2f(0.0f, 0.0f);
	resumeButtonLayout.size = GameMath::Vec2f(200.0f, 50.0f);
	resumeButtonLayout.mouse = Mouse::LEFT;
	resumeButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	resumeButtonLayout.text = L"RESUME";
	resumeButtonLayout.side = 10.0f;
	Button* resumeButton = EntityManager::Get().Create<Button>(resumeButtonLayout, [&]() { status_ = Status::PLAY; });
	EntityManager::Get().Register("ResumeButton", resumeButton);

	Button::Layout quitButtonLayout;
	quitButtonLayout.textColor = GameMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	quitButtonLayout.disableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	quitButtonLayout.enableColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	quitButtonLayout.pressColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	quitButtonLayout.releaseColor = GameMath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	quitButtonLayout.center = GameMath::Vec2f(0.0f, -70.0f);
	quitButtonLayout.size = GameMath::Vec2f(200.0f, 50.0f);
	quitButtonLayout.mouse = Mouse::LEFT;
	quitButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	quitButtonLayout.text = L"QUIT";
	quitButtonLayout.side = 10.0f;
	Button* quitButton = EntityManager::Get().Create<Button>(quitButtonLayout, [&]() { bIsQuit_ = true; });
	EntityManager::Get().Register("QuitButton", quitButton);

	StatusEntities readyEntities;
	readyEntities.updateEntities = { camera_, startButton, quitButton, };
	readyEntities.renderEntities = { background, cactus0, cactus1, cactus2, cactus3, title, startButton, quitButton, };
	statusEntities_.insert({ Status::READY, readyEntities });

	StatusEntities playEntities;
	playEntities.updateEntities = { camera_, player, coinSpawner, powerUpCoin, cactus0, cactus1, cactus2, cactus3, playerMessenger, countDowner, coinViewer, background, };
	playEntities.renderEntities = { background, player, coinSpawner, powerUpCoin, cactus0, cactus1, cactus2, cactus3, playerMessenger, countDowner, coinViewer, };
	statusEntities_.insert({ Status::PLAY, playEntities });

	StatusEntities pauseEntities;
	pauseEntities.updateEntities = { camera_, resumeButton, quitButton, };
	pauseEntities.renderEntities = { background, cactus0, cactus1, cactus2, cactus3, resumeButton, quitButton, };
	statusEntities_.insert({ Status::PAUSE, pauseEntities });

	StatusEntities doneEntities;
	doneEntities.updateEntities = { camera_, };
	doneEntities.renderEntities = { background, cactus0, cactus1, cactus2, cactus3 };
	statusEntities_.insert({ Status::DONE, doneEntities });
}

void GameApp::Shutdown()
{
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
			for (auto& entity : statusEntities.renderEntities)
			{
				entity->Render();
			}
			RenderManager2D::Get().End();

			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	std::string resourcePath = "CoinDash2D\\Res\\";

	Atlas2D* atlas = ResourceManager::Get().Create<Atlas2D>(resourcePath + "Atlas\\Atlas.png", resourcePath + "Atlas\\Atlas.json", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Atlas", atlas);

	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 5> fontSizes = { 16, 24, 32, 64, 72 };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		ResourceManager::Get().Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}