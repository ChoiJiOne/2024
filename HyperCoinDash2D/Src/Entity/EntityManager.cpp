#include "Entity/EntityManager.h"
#include "Assertion.h"

EntityManager EntityManager::singleton_;

EntityManager& EntityManager::GetRef()
{
	return singleton_;
}

EntityManager* EntityManager::GetPtr()
{
	return &singleton_;
}

void EntityManager::Shutdown()
{
}
