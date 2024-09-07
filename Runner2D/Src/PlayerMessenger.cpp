#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Player.h"
#include "PlayerMessenger.h"

PlayerMessenger::PlayerMessenger()
	: player_(EntityManager::Get().GetByName<Player>("Player"))
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font24");

	bIsInitialized_ = true;
}

PlayerMessenger::~PlayerMessenger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PlayerMessenger::Tick(float deltaSeconds)
{
	if (!bIsDetectMessage_)
	{
		return;
	}
}

void PlayerMessenger::Render()
{
	if (!bIsDetectMessage_)
	{
		return;
	}
}

void PlayerMessenger::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}
