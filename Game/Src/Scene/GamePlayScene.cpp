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

	Player* player = entityManager_->Create<Player>();
	player->SetTickOrder(0);
	player->SetRenderOrder(1);
	AddUpdateEntity(player);
	AddRenderEntity(player);

	mainCamera_ = entityManager_->Create<Camera2D>(glm::vec2(0.0f, 0.0f), screenSize);
	mainCamera_->SetTickOrder(1);
	AddUpdateEntity(mainCamera_);

	Background* background = entityManager_->Create<Background>();
	background->SetTickOrder(2);
	background->SetRenderOrder(0);
	AddUpdateEntity(background);
	AddRenderEntity(background);

	Coin* coin = entityManager_->Create<Coin>();
	coin->SetTickOrder(3);
	coin->SetRenderOrder(2);
	AddUpdateEntity(coin);
	AddRenderEntity(coin);
}

GamePlayScene::~GamePlayScene()
{
	renderManager_ = nullptr;
	glManager_ = nullptr;
	entityManager_ = nullptr;
}

void GamePlayScene::Tick(float deltaSeconds)
{
	IGameScene::Tick(deltaSeconds);
}

void GamePlayScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderManager_->Begin(mainCamera_);
		{
			for (auto& renderEntity : renderEntities_)
			{
				renderEntity->Render();
			}
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