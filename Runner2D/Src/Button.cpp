#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Button.h"

Button::Button()
{
	app_ = IApp::Get();

	bIsInitialized_ = true;
}

Button::~Button()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Button::Tick(float deltaSeconds)
{
}

void Button::Render()
{
}

void Button::Release()
{
	CHECK(bIsInitialized_);

	app_ = nullptr;

	bIsInitialized_ = false;
}