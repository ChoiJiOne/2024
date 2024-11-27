#include "Entity/CoinCollector.h"
#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/PlayerFollowCamera.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"
#include "Utils/Utils.h"

CoinCollector::CoinCollector(TTFont* font)
	: font_(font)
{
	player_ = EntityManager::GetRef().GetByName<Player>("Player");
	playerFollowCamera_ = EntityManager::GetRef().GetByName<PlayerFollowCamera>("PlayerFollowCamera");
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

	offset_ = glm::vec2(10.0f, 10.0f);
	background_.size = glm::vec2(150.0f, 50.0f);
	background_.center = playerFollowCamera_->GetCenter() + playerFollowCamera_->GetSize() * 0.5f;
	background_.center -= background_.size * 0.5f;
	background_.center -= offset_;

	coin_.size = glm::vec2(32.0f, 32.0f);
	coin_.center = background_.center;
	coin_.center.x += (-background_.size.x * 0.25f);

	countCoin_ = 0;
	textBasePos_ = background_.center;
	textBasePos_.x += (background_.size.x * 0.25f);

	coinText_ = PrintF(L"X %d", countCoin_);
	textColor_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.3f);

	bIsInitialized_ = true;
}

CoinCollector::~CoinCollector()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void CoinCollector::Tick(float deltaSeconds)
{
	background_.center = playerFollowCamera_->GetCenter() + playerFollowCamera_->GetSize() * 0.5f;
	background_.center -= background_.size * 0.5f;
	background_.center -= offset_;

	coin_.center = background_.center;
	coin_.center.x += (-background_.size.x * 0.25f);

	textBasePos_ = background_.center;
	textBasePos_.x += (+background_.size.x * 0.25f);

	int32_t coin = player_->GetCoin();
	if (coin != countCoin_)
	{
		countCoin_ = coin;
		coinText_ = PrintF(L"X %d", countCoin_);
	}
}

void CoinCollector::Render()
{
	renderManager_->DrawRect(background_.center, background_.size.x, background_.size.y, backgroundColor_, 0.0f);
	renderManager_->DrawTextureAtlas(textureAtlas_, "Coin_1", coin_.center, coin_.size.x, coin_.size.y, 0.0f);

	glm::vec2 basePos = font_->MeasureBasePos(coinText_, textBasePos_);
	renderManager_->DrawString(font_, coinText_, basePos, textColor_);
}

void CoinCollector::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;
	playerFollowCamera_ = nullptr;
	player_ = nullptr;
	font_ = nullptr;

	bIsInitialized_ = false;
}
