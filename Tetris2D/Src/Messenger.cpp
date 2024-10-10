#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Messenger.h"

Messenger::Messenger()
{
	bIsInitialized_ = true;
}

Messenger::~Messenger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Messenger::Tick(float deltaSeconds)
{
}

void Messenger::Render()
{
}

void Messenger::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}

void Messenger::Send()
{
}
