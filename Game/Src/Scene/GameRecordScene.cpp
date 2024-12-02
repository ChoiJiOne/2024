#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/ResultViewer.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Entity/UIPanel.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Scene/GameRecordScene.h"
#include "Scene/GameTitleScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

GameRecordScene::GameRecordScene()
{
	sceneManager_->Register("GameRecordScene", this);

	Initailize();
}

GameRecordScene::~GameRecordScene()
{
	UnInitailize();
}

void GameRecordScene::Tick(float deltaSeconds)
{
	for (auto& uiEntity : updateUiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GameRecordScene::Render()
{
	glManager_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
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

void GameRecordScene::Enter()
{
	bIsEnter_ = true;
	bIsSwitched_ = false;

	int32_t totalPlayTime = static_cast<int32_t>(gameManager_->GetTotalPlayTime());
	playTimeResultViewer_->Start(totalPlayTime);
	
	int32_t totalCoin = gameManager_->GetTotalCoin();
	getCoinResultViewer_->Start(totalCoin);

	int32_t totalUseSkill = gameManager_->GetTotalUseSkill();
	useSkillResultViewer_->Start(totalUseSkill);

	int32_t totalHealHp = static_cast<int32_t>(gameManager_->GetTotalHealHp());
	totalHealHpResultViewer_->Start(totalHealHp);

	int32_t totalLostHp = static_cast<int32_t>(gameManager_->GetTotalLostHp());
	totalLostHpResultViewer_->Start(totalLostHp);

	int32_t totalHealMp = static_cast<int32_t>(gameManager_->GetTotalHealMp());
	totalHealMpResultViewer_->Start(totalHealMp);

	int32_t totalLostMp = static_cast<int32_t>(gameManager_->GetTotalLostMp());
	totalLostMpResultViewer_->Start(totalLostMp);
}

void GameRecordScene::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}

void GameRecordScene::Initailize()
{
	uiCamera_ = entityManager_->GetByName<UICamera>("UICamera");
	updateUiEntities_.push_back(uiCamera_);

	Backdrop* backdrop = entityManager_->GetByName<Backdrop>("Backdrop");
	updateUiEntities_.push_back(backdrop);
	renderUiEntities_.push_back(backdrop);

	TTFont* font48 = glManager_->GetByName<TTFont>("Font48");

	UIPanel* recordPanel = entityManager_->Create<UIPanel>("Resource\\UI\\Record.panel", glManager_->GetByName<TextureAtlas2D>("TextureAtlas"));
	updateUiEntities_.push_back(recordPanel);
	renderUiEntities_.push_back(recordPanel);

	playRecordViewTime_ = 5.0f;

	glm::vec2 basePos = glm::vec2(0.0f, +90.0f);
	float stride = 50.0f;

	playTimeResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"PLAY TIME", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(playTimeResultViewer_);
	renderUiEntities_.push_back(playTimeResultViewer_);
	
	basePos.y -= stride;
	getCoinResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"GET COIN", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(getCoinResultViewer_);
	renderUiEntities_.push_back(getCoinResultViewer_);

	basePos.y -= stride;
	useSkillResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"USE SKILL", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(useSkillResultViewer_);
	renderUiEntities_.push_back(useSkillResultViewer_);

	basePos.y -= stride;
	totalHealHpResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"HEAL HP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalHealHpResultViewer_);
	renderUiEntities_.push_back(totalHealHpResultViewer_);

	basePos.y -= stride;
	totalLostHpResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"LOST HP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalLostHpResultViewer_);
	renderUiEntities_.push_back(totalLostHpResultViewer_);

	basePos.y -= stride;
	totalHealMpResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"HEAL MP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalHealMpResultViewer_);
	renderUiEntities_.push_back(totalHealMpResultViewer_);

	basePos.y -= stride;
	totalLostMpResultViewer_ = entityManager_->Create<ResultViewer>(font48, basePos, L"LOST MP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalLostMpResultViewer_);
	renderUiEntities_.push_back(totalLostMpResultViewer_);

	UIButton* backBtn = entityManager_->Create<UIButton>("Resource\\UI\\Back.button", uiCamera_, font48, EMouse::LEFT,
		[&]()
		{
			AudioManager::GetRef().GetByName<Sound>("Click")->Start();

			bIsSwitched_ = true;
			switchScene_ = sceneManager_->GetByName<GameTitleScene>("GameTitleScene");
		}
	);
	updateUiEntities_.push_back(backBtn);
	renderUiEntities_.push_back(backBtn);
}

void GameRecordScene::UnInitailize()
{	
	/** 외부에서 생성된 엔티티나 리소스는 초기화 해제하지 않습니다. */
	for (auto& updateUiEntity : updateUiEntities_)
	{
		if (updateUiEntity == uiCamera_)
		{
			// UI 카메라는 외부에서 생성했으므로, 정리 대상에서 제외.
			continue;
		}

		if (updateUiEntity && updateUiEntity->IsInitialized())
		{
			entityManager_->Destroy(updateUiEntity);
			updateUiEntity = nullptr;
		}
	}
}
