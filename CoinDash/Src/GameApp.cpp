#include "Assertion.h"
#include "Atlas2D.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "Texture2D.h"
#include "TTFont.h"

#include "Background.h"
#include "Button.h"
#include "Cactus.h"
#include "CoinSpawner.h"
#include "CoinViewer.h"
#include "CountDowner.h"
#include "Entity2D.h"
#include "GameApp.h"
#include "GameOver.h"
#include "Player.h"
#include "PlayerMessenger.h"
#include "PowerUpCoin.h"
#include "Title.h"

GameApp::GameApp() : IApp("CoinDash", 100, 100, 480, 720, false, false)
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

	camera_ = Camera2D::CreateScreenCamera();
	EntityManager::Get().Register("Camera", camera_);

	Background* background = EntityManager::Get().Create<Background>();
	EntityManager::Get().Register("Background", background);

	Player* player = EntityManager::Get().Create<Player>();
	EntityManager::Get().Register("Player", player);

	Cactus* cactus0 = EntityManager::Get().Create<Cactus>(Rect2D(Vec2f(-120.0f, +150.0f), Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus0", cactus0);

	Cactus* cactus1 = EntityManager::Get().Create<Cactus>(Rect2D(Vec2f(+120.0f, +150.0f), Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus1", cactus1);

	Cactus* cactus2 = EntityManager::Get().Create<Cactus>(Rect2D(Vec2f(-120.0f, -150.0f), Vec2f(50.0f, 60.0f)));
	EntityManager::Get().Register("Cactus2", cactus2);

	Cactus* cactus3 = EntityManager::Get().Create<Cactus>(Rect2D(Vec2f(+120.0f, -150.0f), Vec2f(50.0f, 60.0f)));
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

	GameOver* gameOver = EntityManager::Get().Create<GameOver>();
	EntityManager::Get().Register("GameOver", gameOver);

	Button::Layout startButtonLayout;
	startButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	startButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	startButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	startButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	startButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	startButtonLayout.center = Vec2f(0.0f, 0.0f);
	startButtonLayout.size = Vec2f(200.0f, 50.0f);
	startButtonLayout.mouse = Mouse::LEFT;
	startButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	startButtonLayout.text = L"START";
	startButtonLayout.side = 10.0f;
	Button* startButton = EntityManager::Get().Create<Button>(startButtonLayout, [&]() 
		{ 
			Sound* click = ResourceManager::Get().GetByName<Sound>("Click");
			click->Reset();
			click->Play();

			status_ = Status::PLAY; 
		});
	EntityManager::Get().Register("StartButton", startButton);

	Button::Layout resumeButtonLayout;
	resumeButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	resumeButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	resumeButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	resumeButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	resumeButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	resumeButtonLayout.center = Vec2f(0.0f, 0.0f);
	resumeButtonLayout.size = Vec2f(200.0f, 50.0f);
	resumeButtonLayout.mouse = Mouse::LEFT;
	resumeButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	resumeButtonLayout.text = L"RESUME";
	resumeButtonLayout.side = 10.0f;
	Button* resumeButton = EntityManager::Get().Create<Button>(resumeButtonLayout, [&]() 
		{ 			
			Sound* click = ResourceManager::Get().GetByName<Sound>("Click");
			click->Reset();
			click->Play();

			status_ = Status::PLAY; 
		});
	EntityManager::Get().Register("ResumeButton", resumeButton);

	Button::Layout resetButtonLayout;
	resetButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	resetButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	resetButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	resetButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	resetButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	resetButtonLayout.center = Vec2f(0.0f, 0.0f);
	resetButtonLayout.size = Vec2f(200.0f, 50.0f);
	resetButtonLayout.mouse = Mouse::LEFT;
	resetButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	resetButtonLayout.text = L"RESET";
	resetButtonLayout.side = 10.0f;
	Button* resetButton = EntityManager::Get().Create<Button>(resetButtonLayout, [&]() 
		{			
			Sound* click = ResourceManager::Get().GetByName<Sound>("Click");
			click->Reset();
			click->Play();

			EntityManager::Get().GetByName<Player>("Player")->Reset();
			EntityManager::Get().GetByName<CoinSpawner>("CoinSpawner")->Reset();
			EntityManager::Get().GetByName<PowerUpCoin>("PowerUpCoin")->Reset();
			EntityManager::Get().GetByName<CountDowner>("CountDowner")->Reset();
			EntityManager::Get().GetByName<CoinViewer>("CoinViewer")->Reset();
			EntityManager::Get().GetByName<PlayerMessenger>("PlayerMessenger")->Reset();

			status_ = Status::PLAY; 
		});
	EntityManager::Get().Register("ResetButton", resetButton);

	Button::Layout quitButtonLayout;
	quitButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	quitButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	quitButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	quitButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	quitButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	quitButtonLayout.center = Vec2f(0.0f, -70.0f);
	quitButtonLayout.size = Vec2f(200.0f, 50.0f);
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
	doneEntities.updateEntities = { camera_, player, coinSpawner, resetButton, quitButton, gameOver, };
	doneEntities.renderEntities = { background, player, coinSpawner, cactus0, cactus1, cactus2, cactus3, countDowner, coinViewer, gameOver, resetButton, quitButton, };
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

			if (status_ == Status::PLAY && GetKeyPress(Key::KEY_ESCAPE) == Press::PRESSED)
			{
				status_ = Status::PAUSE;
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
	std::string resourcePath = "CoinDash\\Res\\";

	Atlas2D* atlas = ResourceManager::Get().Create<Atlas2D>(resourcePath + "Atlas\\Atlas.png", resourcePath + "Atlas\\Atlas.json", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Atlas", atlas);

	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 5> fontSizes = { 16, 24, 32, 64, 72 };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		ResourceManager::Get().Register(GameUtils::PrintF("Font%d", fontSize), font);
	}

	std::string soundPath = resourcePath + "Sound\\";
	std::array<std::pair<std::string, std::string>, 5> soundPaths =
	{
		std::pair {"Click",    ".mp3"},
		std::pair {"Coin",     ".wav"},
		std::pair {"Hit",      ".wav"},
		std::pair {"Level",    ".wav"},
		std::pair {"PowerUp",  ".wav"},
	};

	for (const auto& path : soundPaths)
	{
		Sound* sound = ResourceManager::Get().Create<Sound>(soundPath + path.first + path.second);
		ResourceManager::Get().Register(path.first, sound);
	}
}