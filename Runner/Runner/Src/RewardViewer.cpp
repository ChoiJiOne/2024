#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"

#include "Player.h"
#include "RewardViewer.h"

RewardViewer::RewardViewer()
	: player_(EntityManager::Get().GetByName<Player>("Player"))
{
	atlas_ = ResourceManager::Get().GetByName<Atlas2D>("Atlas");
	font_ = ResourceManager::Get().GetByName<TTFont>("Font32");

	spriteSize_ = Vec2f(40.0f, 40.0f);
	cherrySpritePos_ = Vec2f(300.0f, 260.0f);
	gemSpritePos_ = Vec2f(300.0f, 220.0f);

	pickupCherryTextPos_ = cherrySpritePos_ + spriteSize_ * 0.5f + Vec2f(0.0f, -10.0f);
	pickupGemTextPos_ = gemSpritePos_ + spriteSize_ * 0.5f + Vec2f(0.0f, -10.0f);

	backgroundPos_ = Vec2f(330.0f, 240.0f);
	backgroundSize_ = Vec2f(120.0f, 100.0f);
	backgroundColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.3f);
	backgroundSide_ = 10.0f;

	bIsInitialized_ = true;
}

RewardViewer::~RewardViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void RewardViewer::Tick(float deltaSeconds)
{
	int32_t numPickupCherry = player_->GetNumPickupCherry();
	if (numPickupCherry_ != numPickupCherry)
	{
		numPickupCherry_ = numPickupCherry;
		pickupCherryText_ = GameUtils::PrintF(L":%d", numPickupCherry_);
	}

	int32_t numPickupGem = player_->GetNumPickupGem();
	if (numPickupGem_ != numPickupGem)
	{
		numPickupGem_ = numPickupGem;
		pickupGemText_ = GameUtils::PrintF(L":%d", numPickupGem_);
	}
}

void RewardViewer::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();

	renderMgr.DrawRoundRect(backgroundPos_, backgroundSize_.x, backgroundSize_.y, backgroundSide_, backgroundColor_, 0.0f);

	static RenderManager2D::SpriteRenderOptions option;
	renderMgr.DrawSprite(atlas_, "Cherry_3", cherrySpritePos_, spriteSize_.x, spriteSize_.y, 0.0f, option);
	renderMgr.DrawSprite(atlas_, "Gem_1", gemSpritePos_, spriteSize_.x, spriteSize_.y, 0.0f, option);

	renderMgr.DrawString(font_, pickupCherryText_, pickupCherryTextPos_, textColor_);
	renderMgr.DrawString(font_, pickupGemText_, pickupGemTextPos_, textColor_);
}

void RewardViewer::Release()
{
	CHECK(bIsInitialized_);

	atlas_ = nullptr;
	font_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}
