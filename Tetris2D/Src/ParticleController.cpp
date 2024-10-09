#include "Assertion.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"

#include "Board.h"
#include "ParticleController.h"

ParticleController::ParticleController()
{
	camera_ = EntityManager::Get().GetByName<Camera2D>("MainCamera");

	bIsInitialized_ = true;
}

ParticleController::~ParticleController()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ParticleController::Tick(float deltaSeconds)
{
}

void ParticleController::Render()
{
}

void ParticleController::Release()
{
	CHECK(bIsInitialized_);

	camera_ = nullptr;

	bIsInitialized_ = false;
}