#pragma once

#include "IEntity.h"

class GameApp;

class GameAppStatusController : public IEntity 
{
public:
	GameAppStatusController();
	virtual ~GameAppStatusController();

	DISALLOW_COPY_AND_ASSIGN(GameAppStatusController);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	GameApp* app_ = nullptr;
};