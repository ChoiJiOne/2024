#include "App/GameApp.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"

GameApp::GameApp() 
	: IApp(windowWidth_, windowHeight_, "HyperCoinDash2D", bIsWindowCentered_)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	TextureAtlas2D* textureAtlas = glManager_->Create<TextureAtlas2D>("Resource\\TextureAtlas\\TextureAtlas.png", "Resource\\TextureAtlas\\TextureAtlas.atlas", TextureAtlas2D::EFilter::NEAREST);
	glManager_->Register("TextureAtlas", textureAtlas);

	GamePlayScene* gamePlayScene = sceneManager_->Create<GamePlayScene>();
	sceneManager_->Register("GamePlayScene", gamePlayScene);

	SetAppScene(gamePlayScene);
}

void GameApp::Shutdown()
{
}
