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
		return; // �ش� ���� �̹� �Ҵ� ���� �Ǿ��ų�, �� �Ŵ����� ���� �Ҵ� ������ ��ƼƼ�Դϴ�.
	}

	if (scenes_[sceneID])
	{
		scenes_[sceneID].reset();
		usages_[sceneID] = false;
	}
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
