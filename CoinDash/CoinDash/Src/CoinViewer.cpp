#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "CoinViewer.h"
#include "Player.h"

CoinViewer::CoinViewer()
{
	player_ = EntityManager::Get().GetByName<Player>("Player");
	font_ = ResourceManager::Get().GetByName<TTFont>("Font64");

	numCoin_ = -1;
	textColor_ = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	textShadowColor_ = Vec4f(0.5f, 0.5f, 0.5f, 0.5f);
	textPos_ = Vec2f(-235.0f, 350.0f);
	textShadowPos_ = textPos_ + Vec2f(+3.0f, -3.0f);

	bIsInitialized_ = true;
}

CoinViewer::~CoinViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void CoinViewer::Tick(float deltaSeconds)
{
	int32_t numCoin = player_->GetNumCoin();
	if (numCoin_ != numCoin)
	{
		numCoin_ = numCoin;
		text_ = GameUtils::PrintF(L"%d", numCoin_);
	}
}

void CoinViewer::Render()
{
	RenderManager2D::Get().DrawString(font_, text_, textShadowPos_, textShadowColor_);
	RenderManager2D::Get().DrawString(font_, text_, textPos_, textColor_);
}

void CoinViewer::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}

void CoinViewer::Reset()
{
	numCoin_ = -1;
}
