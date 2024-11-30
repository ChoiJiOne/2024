#include "App/GameApp.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/UICamera.h"
#include "GL/FrameBuffer.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "GLFW/GLFWManager.h"
#include "Scene/GameOptionScene.h"
#include "Scene/GameOverScene.h"
#include "Scene/GamePauseScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameRecordScene.h"
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
	float width = 0.0f;
	float height = 0.0f;
	glfwManager_->GetWindowSize(width, height);
	frameBuffer_ = glManager_->Create<FrameBuffer>(static_cast<int32_t>(width), static_cast<int32_t>(height), FrameBuffer::EPixelFormat::RGBA, FrameBuffer::EFilter::LINEAR);

	TextureAtlas2D* textureAtlas = glManager_->Create<TextureAtlas2D>("Resource\\TextureAtlas\\TextureAtlas.png", "Resource\\TextureAtlas\\TextureAtlas.atlas", TextureAtlas2D::EFilter::NEAREST);
	glManager_->Register("TextureAtlas", textureAtlas);

	std::array<int32_t, 3> fontSizes = { 24, 32, 48 };
	for (const auto& fontSize : fontSizes)
	{
		TTFont* font = glManager_->Create<TTFont>("Resource\\Font\\lower.ttf", 0x00, 0x128, static_cast<float>(fontSize), ITexture::EFilter::LINEAR);
		glManager_->Register(PrintF("Font%d", fontSize), font);
	}

	UICamera* uiCamera = entityManager_->Create<UICamera>();
	entityManager_->Register("UICamera", uiCamera);

	FadeEffector* fadeEffector = entityManager_->Create<FadeEffector>();
	entityManager_->Register("FadeEffector", fadeEffector);

	GameTitleScene* gameTitleScene = sceneManager_->Create<GameTitleScene>();
	GameRecordScene* gameRecordScene = sceneManager_->Create<GameRecordScene>();
	GameOptionScene* gameOptionScene = sceneManager_->Create<GameOptionScene>();
	GamePlayScene* gamePlayScene = sceneManager_->Create<GamePlayScene>();
	GameOverScene* gameOverScene = sceneManager_->Create<GameOverScene>();
	GamePauseScene* gamePauseScene = sceneManager_->Create<GamePauseScene>();

	SetAppScene(gameTitleScene);
}

void GameApp::Shutdown()
{
	if (frameBuffer_)
	{
		glManager_->Destroy(frameBuffer_);
		frameBuffer_ = nullptr;
	}
}
