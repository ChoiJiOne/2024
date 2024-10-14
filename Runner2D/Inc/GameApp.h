#pragma once

#include <map>

#include "IApp.h"
#include "IEntity.h"

class Camera2D;
class Entity2D;

class GameApp : public IApp
{
public:
	enum class EStatus
	{
		READY = 0x00,
		PLAY  = 0x01,
		PAUSE = 0x02,
		DONE  = 0x03,
	};

public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void Run() override;

	const EStatus& GetStatus() const { return status_; }
	void SetStatus(const EStatus& status) { status_ = status; }

private:
	struct StatusEntities
	{
		std::vector<IEntity*> updateEntities;
		std::vector<Entity2D*> renderEntities;
	};

	void LoadResource();

private:
	std::string resourceRootPath_;

	Camera2D* camera_ = nullptr;

	EStatus status_ = EStatus::READY;
	std::map<EStatus, StatusEntities> statusEntities_;

	int32_t playerStatus_ = 0;
};