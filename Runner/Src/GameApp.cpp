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
#include "Box.h"
#include "Button.h"
#include "CountDowner.h"
#include "Floor.h"
#include "GameApp.h"
#include "GameOver.h"
#include "Player.h"
#include "PlayerMessenger.h"
#include "RewardViewer.h"
#include "Spawner.h"
#include "Title.h"

GameApp::GameApp() : IApp("Runner", 100, 100, 800, 600, false, false)
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
			Player::EStatus status = player->GetStatus();

			if (status_ == EStatus::PLAY && (status != Player::EStatus::HURT))
			{
				playerStatus_ = static_cast<int32_t>(status);
				player->SetStatus(Player::EStatus::STOP);

				status_ = EStatus::PAUSE;
			}
		};

	AddWindowEventAction(WindowEvent::FOCUS_LOST, pauseEvent, true);
	AddWindowEventAction(WindowEvent::MOVED, pauseEvent, true);

	Camera2D* camera = Camera2D::CreateScreenCamera();
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

	CountDowner* countDowner = EntityManager::Get().Create<CountDowner>();
	EntityManager::Get().Register("CountDowner", countDowner);

	GameOver* gameOver = EntityManager::Get().Create<GameOver>();
	EntityManager::Get().Register("GameOver", gameOver);

	Button::Layout startButtonLayout;
	startButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	startButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	startButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	startButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	startButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	startButtonLayout.center = Vec2f(0.0f, -100.0f);
	startButtonLayout.size = Vec2f(200.0f, 50.0f);
	startButtonLayout.mouse = Mouse::LEFT;
	startButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	startButtonLayout.text = L"START";
	startButtonLayout.side = 10.0f;
	Button* startButton = EntityManager::Get().Create<Button>(startButtonLayout, 
		[&]() 
		{ 
			EntityManager::Get().GetByName<PlayerMessenger>("PlayerMessenger")->Send(L"PRESS SPACE KEY!", Vec4f(0.0f, 0.0f, 0.0f, 1.0f), 6.0f);
			EntityManager::Get().GetByName<CountDowner>("CountDowner")->Start();
			status_ = EStatus::PLAY;

			Sound* buttonSound = ResourceManager::Get().GetByName<Sound>("Button");
			buttonSound->Reset();
			buttonSound->Play();
		});
	EntityManager::Get().Register("StartButton", startButton);

	Button::Layout quitButtonLayout;
	quitButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	quitButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	quitButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	quitButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	quitButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	quitButtonLayout.center = Vec2f(0.0f, -180.0f);
	quitButtonLayout.size = Vec2f(200.0f, 50.0f);
	quitButtonLayout.mouse = Mouse::LEFT;
	quitButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	quitButtonLayout.text = L"QUIT";
	quitButtonLayout.side = 10.0f;
	Button* quitButton = EntityManager::Get().Create<Button>(quitButtonLayout, [&]() { bIsQuit_ = true; });
	EntityManager::Get().Register("QuitButton", quitButton);

	Button::Layout resumeButtonLayout;
	resumeButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	resumeButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	resumeButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	resumeButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	resumeButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	resumeButtonLayout.center = Vec2f(0.0f, -100.0f);
	resumeButtonLayout.size = Vec2f(200.0f, 50.0f);
	resumeButtonLayout.mouse = Mouse::LEFT;
	resumeButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	resumeButtonLayout.text = L"RESUME";
	resumeButtonLayout.side = 10.0f;
	Button* resumeButton = EntityManager::Get().Create<Button>(resumeButtonLayout, 
		[&]() 
		{
			Player* player = EntityManager::Get().GetByName<Player>("Player");
			player->SetStatus(static_cast<Player::EStatus>(playerStatus_));

			status_ = EStatus::PLAY;

			Sound* buttonSound = ResourceManager::Get().GetByName<Sound>("Button");
			buttonSound->Reset();
			buttonSound->Play();
		});
	EntityManager::Get().Register("ResumeButton", resumeButton);

	Button::Layout resetButtonLayout;
	resetButtonLayout.textColor = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	resetButtonLayout.disableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.4f);
	resetButtonLayout.enableColor = Vec4f(1.0f, 1.0f, 1.0f, 0.6f);
	resetButtonLayout.pressColor = Vec4f(1.0f, 1.0f, 1.0f, 0.9f);
	resetButtonLayout.releaseColor = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	resetButtonLayout.center = Vec2f(0.0f, -100.0f);
	resetButtonLayout.size = Vec2f(200.0f, 50.0f);
	resetButtonLayout.mouse = Mouse::LEFT;
	resetButtonLayout.font = ResourceManager::Get().GetByName<TTFont>("Font32");
	resetButtonLayout.text = L"RESET";
	resetButtonLayout.side = 10.0f;
	Button* resetButton = EntityManager::Get().Create<Button>(resetButtonLayout,
		[&]()
		{
			Player* player = EntityManager::Get().GetByName<Player>("Player");
			player->Reset();

			Spawner* spawner = EntityManager::Get().GetByName<Spawner>("Spawner");
			spawner->Reset();

			EntityManager::Get().GetByName<PlayerMessenger>("PlayerMessenger")->Send(L"PRESS SPACE KEY!", Vec4f(0.0f, 0.0f, 0.0f, 1.0f), 6.0f);
			EntityManager::Get().GetByName<CountDowner>("CountDowner")->Start();
			status_ = EStatus::PLAY;

			Sound* buttonSound = ResourceManager::Get().GetByName<Sound>("Button");
			buttonSound->Reset();
			buttonSound->Play();
		});
	EntityManager::Get().Register("ResetButton", resetButton);
	
	camera_ = camera;

	StatusEntities readyEntities;
	readyEntities.updateEntities = { camera, background, startButton, quitButton, title, };
	readyEntities.renderEntities = { background, startButton, quitButton, title, };
	statusEntities_.insert({ EStatus::READY, readyEntities });

	StatusEntities playEntities;
	playEntities.updateEntities = { camera, player, floor, spawner, playerMessenger, rewardViewer, countDowner, background, };
	playEntities.renderEntities = { background, floor, spawner, player, playerMessenger, rewardViewer, countDowner, };
	statusEntities_.insert({ EStatus::PLAY, playEntities });

	StatusEntities pauseEntities;
	pauseEntities.updateEntities = { camera, background, resumeButton, quitButton, title };
	pauseEntities.renderEntities = { background, resumeButton, quitButton, title, };
	statusEntities_.insert({ EStatus::PAUSE, pauseEntities });

	StatusEntities doneEntities;
	doneEntities.updateEntities = { camera, player, floor, spawner, playerMessenger, rewardViewer, countDowner, background, gameOver, resetButton, quitButton };
	doneEntities.renderEntities = { background, floor, spawner, player, playerMessenger, rewardViewer, countDowner, gameOver, resetButton, quitButton };
	statusEntities_.insert({ EStatus::DONE, doneEntities });
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
	resourceRootPath_ = "Runner\\Res\\";
	
	Atlas2D* atlas = ResourceManager::Get().Create<Atlas2D>(resourceRootPath_ + "Atlas\\Atlas.png", resourceRootPath_ + "Atlas\\Atlas.json", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Atlas", atlas);

	std::string fontPath = resourceRootPath_ + "Font\\Yolk.ttf";
	std::array<int32_t, 4> fontSizes = { 16, 24, 32, 64 };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		ResourceManager::Get().Register(GameUtils::PrintF("Font%d", fontSize), font);
	}

	TTFont* font = ResourceManager::Get().Create<TTFont>(fontPath, 0x00, 0x128, 128.0f);
	ResourceManager::Get().Register("Font128", font);

	std::string soundPath = resourceRootPath_ + "Sound\\";
	std::array<std::pair<std::string, std::string>, 6> soundPaths =
	{
		std::pair {"Button",  ".wav"},
		std::pair {"Done",    ".wav"},
		std::pair {"Jump",    ".mp3"},
		std::pair {"Reward",  ".wav"},
		std::pair {"SpeedUp", ".wav"},
		std::pair {"Theme",   ".mp3"},
	};

	for (const auto& path : soundPaths)
	{
		Sound* sound = ResourceManager::Get().Create<Sound>(soundPath + path.first + path.second);
		ResourceManager::Get().Register(path.first, sound);
	}
}