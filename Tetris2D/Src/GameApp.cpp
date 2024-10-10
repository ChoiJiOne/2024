#include "Assertion.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "TTFont.h"

#include "Board.h"
#include "GameApp.h"
#include "GameAppStatusController.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "ParticleScheduler.h"
#include "Score.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GameApp::GameApp() : IApp("Tetris2D", 200, 200, 600, 800, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	LoadResource();

	EntityManager& entityMgr = EntityManager::Get();

	mainCamera_ = entityMgr.Create<MainCamera2D>();
	entityMgr.Register("MainCamera", mainCamera_);

	gameAppStatusController_ = entityMgr.Create<GameAppStatusController>();
	entityMgr.Register("GameAppStatusController", gameAppStatusController_);
	
	LoadTitleStatusEntities();
}

void GameApp::Shutdown()
{
	EntityManager::Get().Destroy(mainCamera_);
	mainCamera_ = nullptr;
}

void GameApp::Run()
{
	RunLoop(
		[&](float deltaSeconds)
		{
			StatusEntities& statusEntities = statusEntities_.at(status_);

			for (auto& entity : statusEntities.updateEntities_)
			{
				entity->Tick(deltaSeconds);
			}

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			IEntity2D** renderEntities = statusEntities.renderEntities_.data();
			uint32_t count = static_cast<uint32_t>(statusEntities.renderEntities_.size());

			RenderManager2D::Get().BatchRenderEntities(mainCamera_, renderEntities, count);

			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	ResourceManager& resourceMgr = ResourceManager::Get();
	std::string resourcePath = "Tetris2D\\Res\\";

	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 1> fontSizes = { 32, };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = resourceMgr.Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		resourceMgr.Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}

void GameApp::LoadTitleStatusEntities()
{
	EntityManager& entityMgr = EntityManager::Get();

	StatusEntities statusEntities;
	statusEntities.updateEntities_ = 
	{
		mainCamera_,
		gameAppStatusController_,
	};
	statusEntities.renderEntities_ = 
	{

	};

	statusEntities_.insert({ Status::TITLE, statusEntities });
}
