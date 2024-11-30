#include "Entity/PlayRecordViewer.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

PlayRecordViewer::PlayRecordViewer()
{
	background_ = Rect2D(glm::vec2(0.0f, -65.0f), glm::vec2(520.0f, 360.0f));
	backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.3f);

	font_ = GLManager::GetRef().GetByName<TTFont>("Font48");
	basePos_ = glm::vec2(-170.0f, +70.0f);
	outlineColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	stride_ = 50.0f;

	std::array< EType, MAX_COUNT_PLAY_RECORD> types =
	{
		EType::TOTAL_PLAY_TIME,
		EType::TOTAL_COIN,
		EType::TOTAL_USE_SKILL,
		EType::TOTAL_HEAL_HP,
		EType::TOTAL_LOST_HP,
		EType::TOTAL_HEAL_MP,
		EType::TOTAL_LOST_MP,
	};

	for (uint32_t index = 0; index < types.size(); ++index)
	{
		playRecords_[index].type = types[index];
		playRecords_[index].basePos = basePos_ - static_cast<float>(index) * glm::vec2(0.0f, stride_);
	}

	playRecords_[static_cast<uint32_t>(EType::TOTAL_PLAY_TIME)].textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	playRecords_[static_cast<uint32_t>(EType::TOTAL_COIN)].textColor = glm::vec4(1.0f, 1.0f, 0.2f, 1.0f);
	playRecords_[static_cast<uint32_t>(EType::TOTAL_USE_SKILL)].textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	playRecords_[static_cast<uint32_t>(EType::TOTAL_HEAL_HP)].textColor = glm::vec4(1.0f, 0.2f, 0.2f, 1.0f);
	playRecords_[static_cast<uint32_t>(EType::TOTAL_LOST_HP)].textColor = glm::vec4(1.0f, 0.2f, 0.2f, 1.0f);
	playRecords_[static_cast<uint32_t>(EType::TOTAL_HEAL_MP)].textColor = glm::vec4(0.2f, 0.2f, 1.0f, 1.0f);
	playRecords_[static_cast<uint32_t>(EType::TOTAL_LOST_MP)].textColor = glm::vec4(0.2f, 0.2f, 1.0f, 1.0f);

	bIsInitialized_ = true;
}

PlayRecordViewer::~PlayRecordViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PlayRecordViewer::Tick(float deltaSeconds)
{
}

void PlayRecordViewer::Render()
{
	renderManager_->DrawRect(background_.center, background_.size.x, background_.size.y, backgroundColor_, 0.0f);
	for (const auto& playRecord : playRecords_)
	{
		renderManager_->DrawString(font_, playRecord.text, playRecord.basePos, playRecord.textColor, outlineColor_);
	}
}

void PlayRecordViewer::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void PlayRecordViewer::Update()
{
	GameManager& gameManager = GameManager::GetRef();
	
	int32_t totalPlayTime = static_cast<int32_t>(gameManager.GetTotalPlayTime());
	playRecords_[static_cast<uint32_t>(EType::TOTAL_PLAY_TIME)].text = PrintF(L"PLAY TIME: %d (s)", totalPlayTime);

	int32_t totalCoin = gameManager.GetTotalCoin();
	playRecords_[static_cast<uint32_t>(EType::TOTAL_COIN)].text = PrintF(L"GET COIN: %d", totalCoin);

	int32_t totalUseSkill = gameManager.GetTotalUseSkill();
	playRecords_[static_cast<uint32_t>(EType::TOTAL_USE_SKILL)].text = PrintF(L"USE SKILL: %d", totalUseSkill);

	int32_t totalHealHp = static_cast<int32_t>(gameManager.GetTotalHealHp());
	playRecords_[static_cast<uint32_t>(EType::TOTAL_HEAL_HP)].text = PrintF(L"HEAL HP: %d", totalHealHp);

	int32_t totalLostHp = static_cast<int32_t>(gameManager.GetTotalLostHp());
	playRecords_[static_cast<uint32_t>(EType::TOTAL_LOST_HP)].text = PrintF(L"LOST HP: %d", totalLostHp);

	int32_t totalHealMp = static_cast<int32_t>(gameManager.GetTotalHealMp());
	playRecords_[static_cast<uint32_t>(EType::TOTAL_HEAL_MP)].text = PrintF(L"HEAL MP: %d", totalHealMp);

	int32_t totalLostMp = static_cast<int32_t>(gameManager.GetTotalLostMp());
	playRecords_[static_cast<uint32_t>(EType::TOTAL_LOST_MP)].text = PrintF(L"LOST MP: %d", totalLostMp);
}
