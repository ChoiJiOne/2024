#include "App/GameApp.h"
#include "Audio/AudioManager.h"
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

GameApp::GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, const char* windowIcon, bool bIsWindowCentered)
	: IApp(windowWidth, windowHeight, windowTitle, windowIcon, bIsWindowCentered)
{
	LoadResource();
}

GameApp::~GameApp()
{
	UnloadResource();
}

void GameApp::Startup()
{
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
}

void GameApp::LoadResource()
{
	float width = 0.0f;
	float height = 0.0f;
	glfwManager_->GetWindowSize(width, height);
	frameBuffer_ = glManager_->Create<FrameBuffer>(static_cast<int32_t>(width), static_cast<int32_t>(height), FrameBuffer::EPixelFormat::RGBA, FrameBuffer::EFilter::LINEAR);
	glManager_->Register("FrameBuffer", frameBuffer_);

	textureAtlas_ = glManager_->Create<TextureAtlas2D>("Resource\\TextureAtlas\\TextureAtlas.png", "Resource\\TextureAtlas\\TextureAtlas.atlas", TextureAtlas2D::EFilter::NEAREST);
	glManager_->Register("TextureAtlas", textureAtlas_);

	fontSizes_ = { 24, 32, 48 };
	for (const auto& fontSize : fontSizes_)
	{
		TTFont* font = glManager_->Create<TTFont>("Resource\\Font\\lower.ttf", 0x00, 0x128, static_cast<float>(fontSize), ITexture::EFilter::LINEAR);
		glManager_->Register(PrintF("Font%d", fontSize), font);
	}

	soundNames_ = 
	{
		"Charge",
		"Click",
		"Coin",
		"Dash",
		"EndSound",
		"Explosion",
		"Theme",
	};

	for (const std::string& name : soundNames_)
	{
		std::string soundPath = PrintF("Resource\\Sound\\%s.mp3", name.c_str());
		Sound* sound = audioManager_->Create<Sound>(soundPath);
		sound->SetLooping(false);

		audioManager_->Register(name, sound);
	}
}

void GameApp::UnloadResource()
{
	for (const std::string& name : soundNames_)
	{
		Sound* sound = audioManager_->GetByName<Sound>(name);
		audioManager_->Unregister(name);
		audioManager_->Destroy(sound);
	}

	for (const auto& fontSize : fontSizes_)
	{
		std::string name = PrintF("Font%d", fontSize);
		TTFont* font = glManager_->GetByName<TTFont>(name);
		
		glManager_->Unregister(name);
		glManager_->Destroy(font);
	}

	if (textureAtlas_)
	{
		glManager_->Unregister("TextureAtlas");
		glManager_->Destroy(textureAtlas_);
		textureAtlas_ = nullptr;
	}

	if (frameBuffer_)
	{
		glManager_->Unregister("FrameBuffer");
		glManager_->Destroy(frameBuffer_);
		frameBuffer_ = nullptr;
	}
}
