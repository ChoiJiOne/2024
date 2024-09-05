#pragma once

#include "IApp.h"

class Camera;
class Entity2D;

class GameApp : public IApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;
	virtual void Run() override;

private:
	void LoadTextures();

private:
	std::string resourceRootPath_;

	Camera* camera_ = nullptr;

	std::vector<Entity2D*> entities_;
};