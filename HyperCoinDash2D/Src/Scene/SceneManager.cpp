#include "Scene/SceneManager.h"
#include "Assertion.h"

SceneManager SceneManager::singleton_;

SceneManager& SceneManager::GetRef()
{
	return singleton_;
}

SceneManager* SceneManager::GetPtr()
{
	return &singleton_;
}

void SceneManager::Shutdown()
{
}
