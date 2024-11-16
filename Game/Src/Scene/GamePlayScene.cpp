#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
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

	Player* player = entityManager_->Create<Player>();
	entityManager_->Register("Player", player);
	AddUpdateEntity(player);
	AddRenderEntity(player);

	mainCamera_ = entityManager_->Create<PlayerFollowCamera>();
	AddUpdateEntity(mainCamera_);

	Background* background = entityManager_->Create<Background>();
	AddUpdateEntity(background);
	AddRenderEntity(background);

	Coin* coin = entityManager_->Create<Coin>(glm::vec2(-100.0f, -100.0f));
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