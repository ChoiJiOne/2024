#include <imgui.h>
#include <glm/gtc/constants.hpp>

#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
#include "Entity/CoinCollector.h"
#include "Entity/EntityManager.h"
#include "Entity/MiniMap.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
#include "Entity/Playground.h"
#include "Entity/RandomChest.h"
#include "Entity/UIBar.h"
#include "Entity/UICamera.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/SceneManager.h"
#include "Scene/GamePlayScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GamePlayScene::GamePlayScene()
{
	sceneManager_->Register("GamePlayScene", this);

	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	AddUpdateUIEntity(uiCamera_);

	Playground* playground = entityManager_->Create<Playground>();
	entityManager_->Register("Playground", playground);
	AddUpdateEntity(playground);
	AddRenderEntity(playground);

	Player* player = entityManager_->Create<Player>();
	entityManager_->Register("Player", player);
	AddUpdateEntity(player);
	AddRenderEntity(player);
	
	mainCamera_ = entityManager_->Create<PlayerFollowCamera>();
	entityManager_->Register("PlayerFollowCamera", mainCamera_);
	AddUpdateEntity(mainCamera_);
	
	Background* background = entityManager_->Create<Background>();
	AddUpdateEntity(background);
	AddRenderEntity(background);

	CoinCollector* coinCollector = entityManager_->Create<CoinCollector>(glManager_->GetByName<TTFont>("Font24"));
	entityManager_->Register("CoinCollector", coinCollector);
	AddUpdateEntity(coinCollector);
	AddRenderEntity(coinCollector);

	static const uint32_t COUNT_RANDOM_CHEST = 8;
	float boundRadius = playground->GetSafeBound()->radius;
	std::vector<RandomChest*> randomChests(COUNT_RANDOM_CHEST);
	for (uint32_t count = 0; count < COUNT_RANDOM_CHEST; ++count)
	{
		float theta = (2.0f * glm::pi<float>() * static_cast<float>(count)) / 8.0f;
		RandomChest* randomChest = entityManager_->Create<RandomChest>(glm::vec2(boundRadius * glm::cos(theta), boundRadius * glm::sin(theta)));

		AddUpdateEntity(randomChest);
		AddRenderEntity(randomChest);

		randomChests[count] = randomChest;
	}
	
	MiniMap* miniMap = entityManager_->Create<MiniMap>(uiCamera_, randomChests);
	AddUpdateUIEntity(miniMap);
	AddRenderUIEntity(miniMap);
}

GamePlayScene::~GamePlayScene()
{
	renderManager_ = nullptr;
	glManager_ = nullptr;
	entityManager_ = nullptr;
}

void GamePlayScene::Tick(float deltaSeconds)
{
	if (bNeedSortUpdateEntites_)
	{
		updateEntites_.sort(GamePlayScene::CompareUpdateOrder);
		bNeedSortUpdateEntites_ = false;
	}

	for (auto& updateEntity : updateEntites_)
	{
		updateEntity->Tick(deltaSeconds);
	}

	if (bNeedSortUpdateUiEntites_)
	{
		updateUiEntities_.sort(GamePlayScene::CompareUpdateOrder);
		bNeedSortUpdateUiEntites_ = false;
	}

	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GamePlayScene::Render()
{
	if (bNeedSortRenderEntites_)
	{
		renderEntities_.sort(GamePlayScene::CompareRenderOrder);
		bNeedSortRenderEntites_ = false;
	}

	if (bNeedSortRenderUiEntites_)
	{
		renderUiEntities_.sort(GamePlayScene::CompareRenderOrder);
		bNeedSortRenderUiEntites_ = false;
	}
	
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

		renderManager_->Begin(uiCamera_);
		{
			for (auto& uiEntity : renderUiEntities_)
			{
				uiEntity->Render();
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

void GamePlayScene::AddUpdateEntity(IEntity* entity)
{
	updateEntites_.push_back(entity);
	bNeedSortUpdateEntites_ = true;
}

void GamePlayScene::RemoveUpdateEntity(IEntity* entity)
{
	updateEntites_.remove(entity);
}

void GamePlayScene::AddRenderEntity(IEntity2D* entity)
{
	renderEntities_.push_back(entity);
	bNeedSortRenderEntites_ = true;
}

void GamePlayScene::RemoveRenderEntity(IEntity2D* entity)
{
	renderEntities_.remove(entity);
}

void GamePlayScene::AddUpdateUIEntity(IEntity* entity)
{
	updateUiEntities_.push_back(entity);
	bNeedSortUpdateUiEntites_ = true;
}

void GamePlayScene::RemoveUpdateUIEntity(IEntity* entity)
{
	updateUiEntities_.remove(entity);
}

void GamePlayScene::AddRenderUIEntity(IEntity2D* entity)
{
	renderUiEntities_.push_back(entity);
	bNeedSortRenderUiEntites_ = true;
}

void GamePlayScene::RemoveRenderUIEntity(IEntity2D* entity)
{
	renderUiEntities_.remove(entity);
}
