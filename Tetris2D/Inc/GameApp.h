#pragma once

#include <map>
#include <memory>

#include "IApp.h"

class IEntity;
class IEntity2D;
class IEntityUI;
class IGameScene;

class GameApp : public IApp 
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	void LoadResource();

private:
	std::unique_ptr<class TitleScene2D> titleScene_ = nullptr;
	std::unique_ptr<class GamePlayScene2D> gamePlayScene_ = nullptr;
};