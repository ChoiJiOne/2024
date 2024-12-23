#include "Entity/EntityManager.h"
#include "Entity/IObject.h"
#include "Entity/Player.h"
#include "Utils/Assertion.h"

IObject::IObject(const EType& type)
	: type_(type)
{
	player_ = EntityManager::GetRef().GetByName<Player>("Player");

	bIsInitialized_ = true;
}

IObject::~IObject()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void IObject::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;

	bIsInitialized_ = false;
}
