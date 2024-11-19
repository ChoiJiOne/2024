#include "Entity/EntityManager.h"
#include "Entity/Playground.h"
#include "GL/RenderManager2D.h"
#include "Utils/Assertion.h"

Playground::Playground()
{
	tickOrder_ = 3;
	renderOrder_ = 1;

	safeBound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1000.0f);
	warnBound_ = Circle2D(glm::vec2(0.0f, 0.0f), 1050.0f);

	outlineColor_ = glm::vec4(1.0f, 0.2f, 0.2f, 1.0f);

	bIsInitialized_ = true;
}

Playground::~Playground()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Playground::Tick(float deltaSeconds)
{
}

void Playground::Render()
{
	renderManager_->DrawCircleWireframe(safeBound_.center, safeBound_.radius, outlineColor_);
}

void Playground::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
