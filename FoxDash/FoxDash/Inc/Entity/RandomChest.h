#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class IObject;
class Playground;
class SpriteAnimator2D;
class GamePlayScene;

/** 임의의 오브젝트를 생성하는 상자 엔티티입니다. */
class RandomChest : public IEntity2D
{
public:
	RandomChest(const glm::vec2& position);
	virtual ~RandomChest();

	DISALLOW_COPY_AND_ASSIGN(RandomChest);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 렌덤 상자 엔티티가 관리하는 오브젝트 목록을 얻습니다. */
	const std::list<IObject*>& GetObjects() const { return objects_; }

private:
	/** 렌덤 상자의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 렌덤 상자의 상태입니다. */
	enum class EState
	{
		WAIT     = 0x00,
		GENERATE = 0x01,
	};

	/**
	 * 특정 숫자가 범위 내에 있는지 확인합니다.
	 * 이때, 범위는 [minNum, maxNum]입니다.
	 */
	bool IsRange(int32_t num, int32_t minNum, int32_t maxNum);

	/** 임의의 오브젝트를 생성합니다. */
	IObject* GenerateRandomObject();

	/** 오브젝트 요소를 정리합니다. */
	void CleanupObjects();

private:
	/** 렌덤 상자 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 렌덤 상자의 요소를 획득하거나 피해야 할 플레이어입니다. */
	Player* player_ = nullptr;

	/** 렌덤 요소를 생성할 영역입니다. */
	Playground* playground_ = nullptr;

	/** 렌덤 상자의 애니메이션을 수행하는 스프라이트 애니메이터입니다. */
	SpriteAnimator2D* animator_ = nullptr;

	/** 게임 플레이 씬입니다. */
	GamePlayScene* gamePlayScene_ = nullptr;
	
	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Rect2D collisionBound_;

	/** 렌덤 상자의 그림자입니다. */
	Shadow shadow_;

	/** 렌덤 상자의 상태입니다. */
	EState state_ = EState::WAIT;
	
	/** 생성까지 대기 시간입니다. */
	float waitTime_ = 0.0f;

	/** 최대 대기 시간입니다 */
	float maxWaitTime_ = 0.0f;

	/** 생성 여부를 확인합니다. */
	bool bIsGenerateObject_ = false;
		
	/** 불의 최소 속도입니다. */
	float minFireSpeed_ = 0.0f;

	/** 불의 최대 속도입니다. */
	float maxFireSpeed_ = 0.0f;

	/** 불의 최소 지속 시간입니다. */
	float minFireLifeTime_ = 0.0f;

	/** 불의 최대  지속 시간입니다. */
	float maxFireLifeTime_ = 0.0f;
	
	/** 현재 관리 중인 오브젝트들입니다. */
	std::list<IObject*> objects_;

	/** 렌덤 뽑기를 위한 최소 값입니다. */
	static const int32_t MIN_RANDOM_SELECT = 1;

	/** 렌더 뽑기를 위한 최댓 값입니다. */
	static const int32_t MAX_RANDOM_SELECT = 100;
};