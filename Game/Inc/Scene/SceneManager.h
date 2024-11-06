#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

#include "Scene/IGameScene.h"
#include "Utils/Macro.h"

/**
 * �� ������ �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class SceneManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(SceneManager);

	/** �� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static SceneManager& GetRef();

	/** �� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static SceneManager* GetPtr();

	/** ���� �����մϴ�. */
	template <typename TScene, typename... Args>
	TScene* Create(Args&&... args)
	{
		if (!(0 <= sceneSize_ && sceneSize_ < MAX_SCENE_SIZE))
		{
			return nullptr;
		}

		int32_t sceneID = -1;
		for (uint32_t index = 0; index < sceneSize_; ++index)
		{
			if (!scenes_[index] && !usages_[index])
			{
				sceneID = static_cast<int32_t>(index);
				break;
			}
		}

		if (sceneID == -1)
		{
			sceneID = sceneSize_++;
		}

		usages_[sceneID] = true;
		scenes_[sceneID] = std::make_unique<TScene>(args...);

		return reinterpret_cast<TScene*>(scenes_[sceneID].get());
	}

	/** ������ ���� �ı��մϴ�. */
	void Destroy(const IGameScene* scene);
	
	/** ���� �� �Ŵ����� ����մϴ�. */
	void Register(const std::string& name, IGameScene* scene);

	/** �� �̸��� ��� �Ǿ����� Ȯ���մϴ�. */
	bool IsRegistration(const std::string& name);

	/** �� �Ŵ����� ����� �����մϴ�. */
	void Unregister(const std::string& name);

	/** �̸��� �����ϴ� �� ����ϴ�. */
	template <typename TScene>
	TScene* GetByName(const std::string& name)
	{
		auto it = namedScenes_.find(name);
		if (it == namedScenes_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TScene*>(it->second);
	}

private:
	/** GameApp���� SceneManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * �� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	SceneManager() = default;
	virtual ~SceneManager() {}

	/** �� �Ŵ����� ������ GameApp ���ο����� ����˴ϴ�. */
	void Shutdown();

private:
	/** �� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static SceneManager singleton_;

	/** �� �Ŵ������� �����ϴ� ���� �ִ� �����Դϴ�. */
	static const uint32_t MAX_SCENE_SIZE = 10;

	/** �� �Ŵ����� �� ũ���Դϴ�. �ִ� MAX_SCENE_SIZE�� ���� �����մϴ�. */
	uint32_t sceneSize_ = 0;

	/** ���� �ش� ���� ��� �����Դϴ�. */
	std::array<std::unique_ptr<IGameScene>, MAX_SCENE_SIZE> scenes_;
	std::array<bool, MAX_SCENE_SIZE> usages_;

	/** �̸��� ���� ���Դϴ�. */
	std::map<std::string, IGameScene*> namedScenes_;
};