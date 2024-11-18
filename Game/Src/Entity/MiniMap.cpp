#include "Entity/UICamera.h"
#include "Entity/MiniMap.h"
#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

MiniMap::MiniMap()
{
	tickOrder_ = 0;
	renderOrder_ = 0;

	bIsInitialized_ = true;
}

MiniMap::~MiniMap()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MiniMap::Tick(float deltaSeconds)
{
}

void MiniMap::Render()
{
}

void MiniMap::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
