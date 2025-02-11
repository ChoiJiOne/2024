#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/Backdrop.h"
#include "Entity/EntityManager.h"
#include "Entity/ResultViewer.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "Entity/UIPanel.h"
#include "Entity/UIText.h"
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

	gameManager_ = GameManager::GetPtr();

	Initailize();
}

GameRecordScene::~GameRecordScene()
{
	gameManager_ = nullptr;

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

	UpdateTotalResultViewers();
	UpdateAverageResultViewers();
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

	UIPanel* recordPanel = entityManager_->Create<UIPanel>("Resource\\UI\\GameRecordScene\\Record.panel", glManager_->GetByName<TextureAtlas2D>("TextureAtlas"));
	updateUiEntities_.push_back(recordPanel);
	renderUiEntities_.push_back(recordPanel);

	UIText* totalText = entityManager_->Create<UIText>("Resource\\UI\\GameRecordScene\\Total.text", font48);
	updateUiEntities_.push_back(totalText);
	renderUiEntities_.push_back(totalText);

	UIText* averageText = entityManager_->Create<UIText>("Resource\\UI\\GameRecordScene\\Average.text", font48);
	updateUiEntities_.push_back(averageText);
	renderUiEntities_.push_back(averageText);
	
	playRecordViewTime_ = 5.0f;

	InitTotalResultViewers();
	InitAverageResultViewers();

	UIButton* backBtn = entityManager_->Create<UIButton>("Resource\\UI\\GameRecordScene\\Back.button", uiCamera_, font48, EMouse::LEFT,
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

void GameRecordScene::InitTotalResultViewers()
{
	TTFont* font24 = glManager_->GetByName<TTFont>("Font24");

	glm::vec2 basePos = glm::vec2(-205.0f, +30.0f);
	float stride = 30.0f;

	totalPlayTime_ = entityManager_->Create<ResultViewer>(font24, basePos, L"PLAY TIME (S)", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalPlayTime_);
	renderUiEntities_.push_back(totalPlayTime_);

	basePos.y -= stride;
	totalGetCoin_ = entityManager_->Create<ResultViewer>(font24, basePos, L"GET COIN", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalGetCoin_);
	renderUiEntities_.push_back(totalGetCoin_);

	basePos.y -= stride;
	totalUseSkill_ = entityManager_->Create<ResultViewer>(font24, basePos, L"USE SKILL", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalUseSkill_);
	renderUiEntities_.push_back(totalUseSkill_);

	basePos.y -= stride;
	totalHealHp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"HEAL HP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalHealHp_);
	renderUiEntities_.push_back(totalHealHp_);

	basePos.y -= stride;
	totalLostHp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"LOST HP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalLostHp_);
	renderUiEntities_.push_back(totalLostHp_);

	basePos.y -= stride;
	totalHealMp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"HEAL MP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalHealMp_);
	renderUiEntities_.push_back(totalHealMp_);

	basePos.y -= stride;
	totalLostMp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"LOST MP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(totalLostMp_);
	renderUiEntities_.push_back(totalLostMp_);
}

void GameRecordScene::InitAverageResultViewers()
{
	TTFont* font24 = glManager_->GetByName<TTFont>("Font24");

	glm::vec2 basePos = glm::vec2(+70.0f, +30.0f);
	float stride = 30.0f;

	avgPlayTime_ = entityManager_->Create<ResultViewer>(font24, basePos, L"PLAY TIME (S)", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgPlayTime_);
	renderUiEntities_.push_back(avgPlayTime_);

	basePos.y -= stride;
	avgGetCoin_ = entityManager_->Create<ResultViewer>(font24, basePos, L"GET COIN", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgGetCoin_);
	renderUiEntities_.push_back(avgGetCoin_);

	basePos.y -= stride;
	avgUseSkill_ = entityManager_->Create<ResultViewer>(font24, basePos, L"USE SKILL", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgUseSkill_);
	renderUiEntities_.push_back(avgUseSkill_);

	basePos.y -= stride;
	avgHealHp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"HEAL HP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgHealHp_);
	renderUiEntities_.push_back(avgHealHp_);

	basePos.y -= stride;
	avgLostHp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"LOST HP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgLostHp_);
	renderUiEntities_.push_back(avgLostHp_);

	basePos.y -= stride;
	avgHealMp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"HEAL MP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgHealMp_);
	renderUiEntities_.push_back(avgHealMp_);

	basePos.y -= stride;
	avgLostMp_ = entityManager_->Create<ResultViewer>(font24, basePos, L"LOST MP", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), playRecordViewTime_);
	updateUiEntities_.push_back(avgLostMp_);
	renderUiEntities_.push_back(avgLostMp_);
}

void GameRecordScene::UpdateTotalResultViewers()
{
	int32_t totalPlayTime = static_cast<int32_t>(gameManager_->GetTotalPlayTime());
	totalPlayTime_->Start(totalPlayTime);

	int32_t totalCoin = gameManager_->GetTotalCoin();
	totalGetCoin_->Start(totalCoin);

	int32_t totalUseSkill = gameManager_->GetTotalUseSkill();
	totalUseSkill_->Start(totalUseSkill);

	int32_t totalHealHp = static_cast<int32_t>(gameManager_->GetTotalHealHp());
	totalHealHp_->Start(totalHealHp);

	int32_t totalLostHp = static_cast<int32_t>(gameManager_->GetTotalLostHp());
	totalLostHp_->Start(totalLostHp);

	int32_t totalHealMp = static_cast<int32_t>(gameManager_->GetTotalHealMp());
	totalHealMp_->Start(totalHealMp);

	int32_t totalLostMp = static_cast<int32_t>(gameManager_->GetTotalLostMp());
	totalLostMp_->Start(totalLostMp);
}

void GameRecordScene::UpdateAverageResultViewers()
{
	uint32_t countGamePlayRecord = static_cast<uint32_t>(gameManager_->GetGamePlayRecords().size());
	if (!countGamePlayRecord) /** 플레이 기록이 없다면. */
	{
		avgPlayTime_->Start(0);
		avgGetCoin_->Start(0);
		avgUseSkill_->Start(0);
		avgHealHp_->Start(0);
		avgLostHp_->Start(0);
		avgHealMp_->Start(0);
		avgLostMp_->Start(0);
		return;
	}

	int32_t totalPlayTime = static_cast<int32_t>(gameManager_->GetTotalPlayTime());
	int32_t avgPlayTime = totalPlayTime / countGamePlayRecord;
	avgPlayTime_->Start(avgPlayTime);

	int32_t totalCoin = gameManager_->GetTotalCoin();
	int32_t avgCoin = totalCoin / countGamePlayRecord;
	avgGetCoin_->Start(avgCoin);

	int32_t totalUseSkill = gameManager_->GetTotalUseSkill();
	int32_t avgUseSkill = totalUseSkill / countGamePlayRecord;
	avgUseSkill_->Start(avgUseSkill);

	int32_t totalHealHp = static_cast<int32_t>(gameManager_->GetTotalHealHp());
	int32_t avgHealHp = totalHealHp / countGamePlayRecord;
	avgHealHp_->Start(avgHealHp);

	int32_t totalLostHp = static_cast<int32_t>(gameManager_->GetTotalLostHp());
	int32_t avgLostHp = totalLostHp / countGamePlayRecord;
	avgLostHp_->Start(avgLostHp);

	int32_t totalHealMp = static_cast<int32_t>(gameManager_->GetTotalHealMp());
	int32_t avgHealMp = totalHealMp / countGamePlayRecord;
	avgHealMp_->Start(avgHealMp);

	int32_t totalLostMp = static_cast<int32_t>(gameManager_->GetTotalLostMp());
	int32_t avgLostMp = totalLostMp / countGamePlayRecord;
	avgLostMp_->Start(avgLostMp);
}
