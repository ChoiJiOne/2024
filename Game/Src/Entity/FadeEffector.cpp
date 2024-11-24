#include "Entity/EntityManager.h"
#include "Entity/FadeEffector.h"
#include "Utils/Assertion.h"

FadeEffector::FadeEffector()
{
	tickOrder_ = 15;

	bIsInitialized_ = true;
}

FadeEffector::~FadeEffector()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void FadeEffector::Tick(float deltaSeconds)
{
}

void FadeEffector::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
