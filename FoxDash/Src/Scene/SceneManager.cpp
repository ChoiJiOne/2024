#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"

SceneManager SceneManager::singleton_;

SceneManager& SceneManager::GetRef()
{
	return singleton_;
}

SceneManager* SceneManager::GetPtr()
{
	return &singleton_;
}

void SceneManager::Destroy(const IGameScene* scene)
{
	int32_t sceneID = -1;
	for (uint32_t index = 0; index < sceneSize_; ++index)
	{
		IGameScene* scenePtr = scenes_[index].get();
		if (scene == scenePtr)
		{
			sceneID = static_cast<int32_t>(index);
			break;
		}
	}

	if (sceneID == -1)
	{
		return; // 해당 씬은 이미 할당 해제 되었거나, 씬 매니저에 의해 할당 해제된 씬입니다.
	}

	if (scenes_[sceneID])
	{
		scenes_[sceneID].reset();
		usages_[sceneID] = false;
	}
}

void SceneManager::Register(const std::string& name, IGameScene* scene)
{
	auto it = namedScenes_.find(name);
	ASSERTION(it == namedScenes_.end(), "Already register '%s'", name.c_str());

	namedScenes_.insert({ name, scene });
}

bool SceneManager::IsRegistration(const std::string& name)
{
	return namedScenes_.find(name) != namedScenes_.end();
}

void SceneManager::Unregister(const std::string& name)
{
	auto it = namedScenes_.find(name);
	ASSERTION(it != namedScenes_.end(), "Can't find '%s' in SceneManager.", name.c_str());

	namedScenes_.erase(it);
}

void SceneManager::Shutdown()
{
	for (std::size_t index = 0; index < sceneSize_; ++index)
	{
		if (scenes_[index])
		{
			scenes_[index].reset();
			usages_[index] = false;
		}
	}

	sceneSize_ = 0;
}