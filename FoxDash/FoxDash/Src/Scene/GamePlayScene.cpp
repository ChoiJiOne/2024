#include <algorithm>

#include <glm/gtc/constants.hpp>

#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/Coin.h"
#include "Entity/CoinCollector.h"
#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Entity/GamePlayRecorder.h"
#include "Entity/KeyArrowPressViewer.h"
#include "Entity/KeyEventTrigger.h"
#include "Entity/MiniMap.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
#include "Entity/Playground.h"
#include "Entity/RandomChest.h"
#include "Entity/UIBar.h"
#include "Entity/UICamera.h"
#include "Game/GameManager.h"
#include "GL/PostProcessor.h"
#include "Scene/SceneManager.h"
#include "Scene/GameOverScene.h"
#include "Scene/GamePauseScene.h"
#include "Scene/GamePlayScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GamePlayScene::GamePlayScene()
{
	sceneManager_->Register("GamePlayScene", this);

	gameManager_ = GameManager::GetPtr();

	Initialize();
}

GamePlayScene::~GamePlayScene()
{
	gameManager_ = nullptr;

	UnInitialize();
}

void GamePlayScene::Tick(float deltaSeconds)
{
	PreTick(deltaSeconds);

	for (auto& updateEntity : updateEntites_)
	{
		updateEntity.second->Tick(deltaSeconds);
	}
}

void GamePlayScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderTargetOption_.bIsClearBuffer = true;
		renderManager_->Begin(mainCamera_, frameBuffer_, renderTargetOption_);
		{
			for (auto& renderEntity : renderEntities_)
			{
				if (gameEntityRange_.first <= renderEntity.first && renderEntity.first <= gameEntityRange_.second)
				{
					renderEntity.second->Render();
				}
			}
		}
		renderManager_->End();

		renderTargetOption_.bIsClearBuffer = false;
		renderManager_->Begin(uiCamera_, frameBuffer_, renderTargetOption_);
		{
			for (auto& renderEntity : renderEntities_)
			{
				if (uiEntityRange_.first <= renderEntity.first && renderEntity.first <= uiEntityRange_.second)
				{
					renderEntity.second->Render();
				}
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
	for (const auto& windowPauseEvent : windowPauseEvents_)
	{
		GLFWManager::GetRef().SetActiveWindowEventAction(windowPauseEvent.second, true);
	}

	bIsEnter_ = true;
	bIsSwitched_ = false;
	if (bIsPause_)
	{
		bIsPause_ = false;
		return;
	}

	LoadEntity();

	fadeEffector_->StartIn(fadeInTime_);
}

void GamePlayScene::Exit()
{
	for (const auto& windowPauseEvent : windowPauseEvents_)
	{
		GLFWManager::GetRef().SetActiveWindowEventAction(windowPauseEvent.second, false);
	}

	if (bIsPause_)
	{
		bIsSwitched_ = false;
		bIsEnter_ = false;
		return;
	}

	gameManager_->AddGamePlayRecord(gamePlayRecorder_);
	fadeEffector_->Reset();

	UnloadEntity();
	
	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GamePlayScene::AddEntity(IEntity* entity, int32_t updateOrder)
{
	updateEntites_.insert({ updateOrder, entity });
}

void GamePlayScene::AddEntity(IEntity2D* entity, int32_t updateOrder, int32_t renderOrder)
{
	updateEntites_.insert({ updateOrder, entity });
	renderEntities_.insert({ renderOrder, entity });
}

void GamePlayScene::RemoveEntity(IEntity* entity)
{
	auto updateTargetEntity = std::find_if(updateEntites_.begin(), updateEntites_.end(), [&](const std::pair<int32_t, IEntity*>& pair) { return pair.second == entity; });
	if (updateTargetEntity == updateEntites_.end())
	{
		return;
	}
	updateEntites_.erase(updateTargetEntity);

	auto renderTargetEntity = std::find_if(renderEntities_.begin(), renderEntities_.end(), [&](const std::pair<int32_t, IEntity2D*>& pair) { return pair.second == entity; });
	if (renderTargetEntity == renderEntities_.end())
	{
		return;
	}
	renderEntities_.erase(renderTargetEntity);
}

void GamePlayScene::PreTick(float deltaSeconds)
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
		return;
	}

	if (fadeEffector_->GetState() == FadeEffector::EState::PROGRESS)
	{
		fadeEffector_->Tick(deltaSeconds);
	}
	else if (fadeEffector_->GetState() == FadeEffector::EState::DONE)
	{
		fadeEffector_->Reset();
	}
}

void GamePlayScene::Initialize()
{
	postProcessor_ = renderManager_->GetPostProcessor();
	frameBuffer_ = glManager_->GetByName<FrameBuffer>("FrameBuffer");
	renderTargetOption_ = RenderTargetOption{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), true };

	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	AddEntity(uiCamera_, 50);

	fadeEffector_ = entityManager_->GetByName<FadeEffector>("FadeEffector");
	AddEntity(fadeEffector_, 52);

	playground_ = entityManager_->Create<Playground>();
	AddEntity(playground_, 10, 2);

	gamePauseTrigger_ = entityManager_->Create<KeyEventTrigger>(EKey::KEY_ESCAPE, EPress::PRESSED, 
		[&]() 
		{
			if (fadeEffector_->GetState() == FadeEffector::EState::PROGRESS)
			{
				return;
			}

			bIsPause_ = true;
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GamePauseScene>("GamePauseScene");
		});
	AddEntity(gamePauseTrigger_, 99);

	entityManager_->Register("Playground", playground_);

	gameEntityRange_ = std::pair{ 0, 49 };
	uiEntityRange_ = std::pair{ 50, 99 };

	auto gamePauseEvent = [&]()
		{
			bIsPause_ = true;
			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GamePauseScene>("GamePauseScene");
		};
	windowPauseEvents_ =
	{
		{ EWindowEvent::MOVE_ENTER, GLFWManager::GetRef().AddWindowEventAction(EWindowEvent::MOVE_ENTER, gamePauseEvent, false) },
		{ EWindowEvent::FOCUS_LOST, GLFWManager::GetRef().AddWindowEventAction(EWindowEvent::FOCUS_LOST, gamePauseEvent, false) },
	};
}

void GamePlayScene::UnInitialize()
{
	if (playground_)
	{
		RemoveEntity(playground_);
		entityManager_->Unregister("Playground");
		entityManager_->Destroy(playground_);
		playground_ = nullptr;
	}

	if (gamePauseTrigger_)
	{
		RemoveEntity(gamePauseTrigger_);
		entityManager_->Destroy(gamePauseTrigger_);
		gamePauseTrigger_ = nullptr;
	}

	fadeEffector_ = nullptr;
	uiCamera_ = nullptr;
	frameBuffer_ = nullptr;
	postProcessor_ = nullptr;
}

void GamePlayScene::LoadEntity()
{
	gamePlayRecorder_ = entityManager_->Create<GamePlayRecorder>();
	entityManager_->Register("GamePlayRecorder", gamePlayRecorder_);

	player_ = entityManager_->Create<Player>();
	entityManager_->Register("Player", player_);

	mainCamera_ = entityManager_->Create<PlayerFollowCamera>();
	entityManager_->Register("PlayerFollowCamera", mainCamera_);
	
	background_ = entityManager_->Create<Background>();

	coinCollector_ = entityManager_->Create<CoinCollector>(glManager_->GetByName<TTFont>("Font24"));
	entityManager_->Register("CoinCollector", coinCollector_);

	static const uint32_t COUNT_RANDOM_CHEST = 8;
	std::array<RandomChest*, COUNT_RANDOM_CHEST> randomChests;
	for (uint32_t index = 0; index < randomChests.size(); ++index)
	{
		float radius = playground_->GetSafeBound()->radius;
		float theta = 2.0f * glm::pi<float>();
		theta *= static_cast<float>(index) / static_cast<float>(randomChests.size());

		glm::vec2 randomChestPos = glm::vec2(radius * glm::cos(theta), radius * glm::sin(theta));

		RandomChest* randomChest = entityManager_->Create<RandomChest>(randomChestPos);

		AddEntity(randomChest, 10, 3);
		randomChests[index] = randomChest;
	}

	KeyArrowPressViewer* keyArrowPressViewer = entityManager_->Create<KeyArrowPressViewer>();
	MiniMap* miniMap = entityManager_->Create<MiniMap>(uiCamera_, randomChests.data(), static_cast<uint32_t>(randomChests.size()));

	/** 인게임 엔티티입니다. */
	AddEntity(player_, 1, 6);
	AddEntity(mainCamera_, 2);
	AddEntity(background_, 10, 0);
	AddEntity(keyArrowPressViewer, 9, 4);
	AddEntity(coinCollector_, 15, 10);
	AddEntity(gamePlayRecorder_, 20);

	/** UI 및 기타 엔티티입니다. */
	AddEntity(miniMap, 51, 51);
}

void GamePlayScene::UnloadEntity()
{
	RemoveEntity(player_);
	entityManager_->Unregister("Player");
	entityManager_->Destroy(player_);
	player_ = nullptr;

	RemoveEntity(mainCamera_);
	entityManager_->Unregister("PlayerFollowCamera");
	entityManager_->Destroy(mainCamera_);
	mainCamera_ = nullptr;

	RemoveEntity(background_);
	entityManager_->Destroy(background_);
	background_ = nullptr;

	RemoveEntity(coinCollector_);
	entityManager_->Unregister("CoinCollector");
	entityManager_->Destroy(coinCollector_);
	coinCollector_ = nullptr;

	RemoveEntity(gamePlayRecorder_);
	entityManager_->Unregister("GamePlayRecorder");
	entityManager_->Destroy(gamePlayRecorder_);
	gamePlayRecorder_ = nullptr;

	std::list<IEntity*> removeEntities;
	for (auto& entity : updateEntites_)
	{
		if (entity.second != fadeEffector_ && entity.second != uiCamera_ && entity.second != playground_ && entity.second != gamePauseTrigger_)
		{
			removeEntities.push_back(entity.second);
		}
	}

	for (auto& removeEntity : removeEntities)
	{
		RemoveEntity(removeEntity);
		entityManager_->Destroy(removeEntity);
	}
}
