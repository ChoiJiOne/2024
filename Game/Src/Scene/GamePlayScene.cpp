#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/GamePlayScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GamePlayScene::GamePlayScene()
{
	entityManager_ = EntityManager::GetPtr();
	glManager_ = GLManager::GetPtr();
	renderManager_ = RenderManager2D::GetPtr();

	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	mainCamera_ = entityManager_->Create<Camera2D>(glm::vec2(0.0f, 0.0f), screenSize);
	background_ = entityManager_->Create<Background>();
	player_ = entityManager_->Create<Player>();
	coin_ = entityManager_->Create<Coin>();
}

GamePlayScene::~GamePlayScene()
{
	entityManager_->Destroy(coin_);
	entityManager_->Destroy(player_);
	entityManager_->Destroy(background_);
	entityManager_->Destroy(mainCamera_);

	renderManager_ = nullptr;
	glManager_ = nullptr;
	entityManager_ = nullptr;
}

void GamePlayScene::Tick(float deltaSeconds)
{
	player_->Tick(deltaSeconds);
	background_->Tick(deltaSeconds);
	coin_->Tick(deltaSeconds);
}

void GamePlayScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderManager_->Begin(mainCamera_);
		{
			background_->Render();
			player_->Render();
			coin_->Render();
		}
		renderManager_->End();
	}
	glManager_->EndFrame();
}

void GamePlayScene::Enter()
{
}

void GamePlayScene::Exit()
{
}