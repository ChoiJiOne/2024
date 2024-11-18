#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/OrientedRect2D.h"

/** 클래스 전방 선언입니다. */
class SpriteAnimator2D;
class TextureAtlas2D;
class Player;
class Playground;

/** 플레이어가 피해야 할 불입니다. */
class Fire : public IEntity2D
{
public:
	/** 불의 상태입니다. */
	enum class EState
	{
		NONE      = 0x00, // 아무것도 아닌 상태.
		MOVE      = 0x01, // 움직이고 있는 상태.
		EXPLOSION = 0x02, // 불이 폭발하는 상태.
		DONE      = 0x03, // 더 이상 업데이트할 수 없는 상태.
	};

public:
	Fire(const glm::vec2& position, const glm::vec2& direction, float speed);
	virtual ~Fire();

	DISALLOW_COPY_AND_ASSIGN(Fire);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 불의 현재 상태를 얻습니다. */
	const EState& GetState() const { return state_; }

private:
	/** 불을 움직입니다. */
	void Move(float deltaSeconds);

private:
	/** 코인 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;
	
	/** 해당 코인을 획득했는지 확인할 플레이어입니다. */
	Player* player_ = nullptr;

	/** 불이 존재할 영역입니다. */
	Playground* playground_ = nullptr;

	/** 렌더링 영역입니다. */
	OrientedRect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 불의 이동 방향입니다. */
	glm::vec2 direction_ = glm::vec2(0.0f, 0.0f);

	/** 불의 이동 속도입니다. */
	float speed_ = 0.0f;

	/** 불의 라이프 타입입니다. */
	float lifeTime_ = 0.0f;

	/** 불의 현재 상태입니다. */
	EState state_ = EState::NONE;

	/** 불의 상태 별 애니메이션입니다. */
	std::map<EState, SpriteAnimator2D*> animations_;
};