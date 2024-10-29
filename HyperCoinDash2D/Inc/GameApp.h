#pragma once

#include "IApp.h"

class GameApp : public IApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<class GameScene> gameScene_ = nullptr;
};