#include "Assertion.h"
#include "SceneManager.h"

SceneManager SceneManager::instance_;

SceneManager& SceneManager::GetRef()
{
	return instance_;
}

SceneManager* SceneManager::GetPtr()
{
	return &instance_;
}
