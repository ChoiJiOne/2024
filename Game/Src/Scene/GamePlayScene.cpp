#include <imgui.h>
#include <glm/gtc/constants.hpp>

#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
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

	uiCamera_ = entityManager_->Create<UICamera>();

	MiniMap* miniMap = entityManager_->Create<MiniMap>(uiCamera_, randomChests);
	AddUIEntity(miniMap);

	UIBar* hpBar = entityManager_->Create<UIBar>(uiCamera_, glManager_->GetByName<TTFont>("Font24"), "Resource\\UI\\HP.bar");
	AddUIEntity(hpBar);

	UIBar* mpBar = entityManager_->Create<UIBar>(uiCamera_, glManager_->GetByName<TTFont>("Font24"), "Resource\\UI\\MP.bar");
	AddUIEntity(mpBar);
}

GamePlayScene::~GamePlayScene()
{
	renderManager_ = nullptr;
	glManager_ = nullptr;
	entityManager_ = nullptr;
}

void GamePlayScene::Tick(float deltaSeconds)
{
	for (auto& updateEntity : updateEntites_)
	{
		updateEntity->Tick(deltaSeconds);
	}

	for (auto& uiEntity : uiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
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

		renderManager_->Begin(uiCamera_);
		{
			for (auto& uiEntity : uiEntities_)
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
	updateEntites_.sort(GamePlayScene::CompareUpdateOrder);
}

void GamePlayScene::RemoveUpdateEntity(IEntity* entity)
{
	updateEntites_.remove(entity);
}

void GamePlayScene::AddRenderEntity(IEntity2D* entity)
{
	renderEntities_.push_back(entity);
	renderEntities_.sort(GamePlayScene::CompareRenderOrder);
}

void GamePlayScene::RemoveRenderEntity(IEntity2D* entity)
{
	renderEntities_.remove(entity);
}

void GamePlayScene::AddUIEntity(IEntity2D* entity)
{
	uiEntities_.push_back(entity);
	uiEntities_.sort(GamePlayScene::CompareRenderOrder);
}

void GamePlayScene::RemoveUIEntity(IEntity2D* entity)
{
	uiEntities_.remove(entity);
}
