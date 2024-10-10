#pragma once

#include <map>

#include "IApp.h"

class MainCamera2D;
class IEntity;
class IEntity2D;

class GameApp : public IApp 
{
public:
	enum class Status
	{
		TITLE    = 0x00,
		READY    = 0x01,
		GAMEPLAY = 0x01,
		PAUSE    = 0x02,
		GAMEOVER = 0x03,
	};

public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void Run() override;

private:
	friend class GameAppStatusController;

	struct StatusEntities
	{
		std::vector<IEntity*> updateEntities_;
		std::vector<IEntity2D*> renderEntities_;
	};

	void LoadResource();
	void LoadTitleStatusEntities();

private:
	MainCamera2D* mainCamera_ = nullptr;
	GameAppStatusController* gameAppStatusController_ = nullptr;

	Status status_ = Status::TITLE;
	std::map<Status, StatusEntities> statusEntities_;
};