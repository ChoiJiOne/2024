#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

#include "Scene/IGameScene.h"
#include "Macro.h"

/**
 * 씬 관리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class SceneManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(SceneManager);

	/** 씬 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static SceneManager& GetRef();

	/** 씬 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static SceneManager* GetPtr();

	/** 씬을 생성합니다. */
	template <typename TScene, typename... Args>
	TScene* Create(Args&&... args)
	{
		if (!(0 <= sceneSize_ && sceneSize_ < MAX_ENTITY_SIZE))
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

	/** 생성된 씬을 파괴합니다. */
	void Destroy(const IGameScene* scene);

private:
	/** GameApp에서 SceneManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 씬 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	SceneManager() = default;
	virtual ~SceneManager() {}

	/** 씬 매니저의 해제는 GameApp 내부에서만 수행됩니다. */
	void Shutdown();

private:
	/** 씬 매니저의 싱글턴 객체입니다. */
	static SceneManager singleton_;

	/** 씬 매니저에서 관리하는 씬의 최대 개수입니다. */
	static const uint32_t MAX_SCENE_SIZE = 10;

	/** 씬 매니저의 씬 크기입니다. 최대 MAX_SCENE_SIZE개 까지 지원합니다. */
	uint32_t sceneSize_ = 0;

	/** 씬과 해당 씬의 사용 여부입니다. */
	std::array<std::unique_ptr<IGameScene>, MAX_SCENE_SIZE> scenes_;
	std::array<bool, MAX_SCENE_SIZE> usages_;
};