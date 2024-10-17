#include "Assertion.h"
#include "ButtonUI.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "PanelUI.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "RenderStateManager.h"
#include "TextUI.h"
#include "TTFont.h"
#include "UIManager.h"

#include "GameApp.h"
#include "GamePlayScene2D.h"
#include "MainCamera2D.h"
#include "TitleScene2D.h"

GameApp::GameApp() : IApp("Tetris2D", 200, 200, 600, 800, false, false)
{
	entityMgr_ = EntityManager::GetPtr();
	resourceMgr_ = ResourceManager::GetPtr();

	RenderStateManager::GetRef().SetAlphaBlendMode(true);
}

GameApp::~GameApp()
{
	resourceMgr_ = nullptr;
	entityMgr_ = nullptr;
}

void GameApp::Startup()
{
	LoadResource();

	MainCamera2D* mainCamera = entityMgr_->Create<MainCamera2D>();
	entityMgr_->Register("MainCamera", mainCamera);

	titleScene_ = std::make_unique<TitleScene2D>();
	AddSceneByName("TitleScene", titleScene_.get());

	gamePlayScene_ = std::make_unique<GamePlayScene2D>();
	AddSceneByName("GamePlayScene", gamePlayScene_.get());

	SetCurrentScene(titleScene_.get());
}

void GameApp::Shutdown()
{
	gamePlayScene_.reset();
	titleScene_.reset();
}

void GameApp::LoadResource()
{
	std::string resourcePath = "Tetris2D\\Res\\";
	std::string fontPath = resourcePath + "Font\\SeoulNamsanEB.ttf";
	std::array<int32_t, 2> fontSizes = { 32, 128, };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = resourceMgr_->Create<TTFont>(fontPath, 0x00, 0x128, static_cast<float>(fontSize));
		resourceMgr_->Register(GameUtils::PrintF("Font%d", fontSize), font);
	}
}