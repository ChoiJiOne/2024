#include "App/GameApp.h"
#include "Entity/EntityManager.h"
#include "Entity/UICamera.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Utils.h"

GameApp::GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered)
	: IApp(windowWidth, windowHeight, windowTitle, bIsWindowCentered)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	TextureAtlas2D* textureAtlas = glManager_->Create<TextureAtlas2D>("Resource\\TextureAtlas\\TextureAtlas.png", "Resource\\TextureAtlas\\TextureAtlas.atlas", TextureAtlas2D::EFilter::NEAREST);
	glManager_->Register("TextureAtlas", textureAtlas);

	std::array<int32_t, 2> fontSizes = { 24, 32, };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = glManager_->Create<TTFont>("Resource\\Font\\lower.ttf", 0x00, 0x128, static_cast<float>(fontSize), ITexture::EFilter::NEAREST);
		glManager_->Register(PrintF("Font%d", fontSize), font);
	}

	UICamera* uiCamera = entityManager_->Create<UICamera>();
	entityManager_->Register("UICamera", uiCamera);

	GameTitleScene* gameTitleScene = sceneManager_->Create<GameTitleScene>();
	GamePlayScene* gamePlayScene = sceneManager_->Create<GamePlayScene>();

	SetAppScene(gameTitleScene);
}

void GameApp::Shutdown()
{
}
