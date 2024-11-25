#include <glm/gtc/constants.hpp>

#include "App/GameApp.h"
#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
#include "Entity/CoinCollector.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/MiniMap.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
#include "Entity/Playground.h"
#include "Entity/RandomChest.h"
#include "Entity/UIBar.h"
#include "Entity/UICamera.h"
#include "GL/PostProcessor.h"
#include "GLFW/GLFWManager.h"
#include "Scene/SceneManager.h"
#include "Scene/GameOverScene.h"
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

	player_ = entityManager_->Create<Player>();
	entityManager_->Register("Player", player_);
	AddUpdateEntity(player_);
	AddRenderEntity(player_);
	
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

	postProcessor_ = renderManager_->GetPostProcessor();
	frameBuffer_ = reinterpret_cast<GameApp*>(IApp::GetPtr())->GetFrameBuffer();
	renderTargetOption_ = RenderTargetOption{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true };

	fadeEffector_ = entityManager_->GetByName<FadeEffector>("FadeEffector");
	AddUpdateUIEntity(fadeEffector_);
}

GamePlayScene::~GamePlayScene()
{
	frameBuffer_ = nullptr;
	postProcessor_ = nullptr;
}

void GamePlayScene::Tick(float deltaSeconds)
{
	const Player::EState& playerState = player_->GetState();
	if (playerState == Player::EState::HURT)
	{
		const FadeEffector::EState& state = fadeEffector_->GetState();

		if (state == FadeEffector::EState::WAIT)
		{
			fadeEffector_->StartOut(fadeOutTime_);
		}
		else if (state == FadeEffector::EState::PROGRESS)
		{
			fadeEffector_->Tick(deltaSeconds);
		}
		else // state == FadeEffector::EState::DONE
		{
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameOverScene>("GameOverScene");
		}
	}
	else
	{
		if (fadeEffector_->GetState() == FadeEffector::EState::PROGRESS)
		{
			fadeEffector_->Tick(deltaSeconds);
			if (fadeEffector_->GetState() == FadeEffector::EState::DONE)
			{
				fadeEffector_->Reset();
			}
			return;
		}
	}

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
		renderTargetOption_.bIsClearBuffer = true;
		renderManager_->Begin(mainCamera_, frameBuffer_, renderTargetOption_);
		{
			for (auto& renderEntity : renderEntities_)
			{
				renderEntity->Render();
			}
		}
		renderManager_->End();

		renderTargetOption_.bIsClearBuffer = false;
		renderManager_->Begin(uiCamera_, frameBuffer_, renderTargetOption_);
		{
			for (auto& uiEntity : renderUiEntities_)
			{
				uiEntity->Render();
			}
		}
		renderManager_->End();

		PostProcessor::EType type = PostProcessor::EType::BLIT;
		if (fadeEffector_->GetState() != FadeEffector::EState::WAIT)
		{
			type = PostProcessor::EType::BLEND_COLOR;
			postProcessor_->SetBlendColor(fadeEffector_->GetBlendColor(), fadeEffector_->GetFactor());
		}

		postProcessor_->Blit(type, frameBuffer_);
	}
	glManager_->EndFrame();
}

void GamePlayScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;

	fadeEffector_->StartIn(fadeInTime_);
}

void GamePlayScene::Exit()
{
	fadeEffector_->Reset();

	bIsSwitched_ = false;
	bIsEnter_ = false;
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
