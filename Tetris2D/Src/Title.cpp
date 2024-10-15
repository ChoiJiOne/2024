#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Title.h"

Title::Title()
{
	font_ = ResourceManager::Get().GetByName<TTFont>("Font64");

	bIsInitialized_ = true;
}

Title::~Title()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Title::Tick(float deltaSeconds)
{
}

void Title::Render()
{
}

void Title::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}
