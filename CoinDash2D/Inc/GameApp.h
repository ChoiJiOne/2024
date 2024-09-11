#pragma once

#include <map>
#include <vector>

#include "IApp.h"
#include "IEntity.h"

class Camera;
class Entity2D;

class GameApp : public IApp
{
public:
	enum class Status
	{
		READY = 0x00,
		PLAY  = 0x01,
		PAUSE = 0x02,
		DONE  = 0x03
	};

public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void Run() override;

private:
	void LoadResource();

private:
	Camera* camera_ = nullptr;

	std::vector<IEntity*> updateEntities_;
	std::vector<Entity2D*> renderEntities_;
};