#include <glm/gtc/constants.hpp>

#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
#include "Entity/CoinSpawner.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
#include "Entity/Playground.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/SceneManager.h"
#include "Scene/GamePlayScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GamePlayScene::GamePlayScene()
{
	entityManager_ = EntityManager::GetPtr();
	glManager_ = GLManager::GetPtr();
	renderManager_ = RenderManager2D::GetPtr();
	sceneManager_ = SceneManager::GetPtr();

	sceneManager_->Register("GamePlayScene", this);

	Player* player = entityManager_->Create<Player>();
	entityManager_->Register("Player", player);
	AddUpdateEntity(player);
	AddRenderEntity(player);

	Playground* playground = entityManager_->Create<Playground>();
	entityManager_->Register("Playground", playground);
	AddUpdateEntity(playground);
	AddRenderEntity(playground);

	mainCamera_ = entityManager_->Create<PlayerFollowCamera>();
	AddUpdateEntity(mainCamera_);

	Background* background = entityManager_->Create<Background>();
	AddUpdateEntity(background);
	AddRenderEntity(background);

	float boundRadius = playground->GetSafeBound()->radius;
	for (uint32_t count = 0; count < 4; ++count)
	{
		float theta = (2.0f * glm::pi<float>() * static_cast<float>(count)) / 4.0f;
		CoinSpawner* coinSpawner = entityManager_->Create<CoinSpawner>(glm::vec2(boundRadius * glm::cos(theta), boundRadius * glm::sin(theta)));
		AddUpdateEntity(coinSpawner);
		AddRenderEntity(coinSpawner);
	}
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