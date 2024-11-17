#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class SpriteAnimator2D;
class TextureAtlas2D;
class Player;

/** 플레이어가 획득할 코인입니다. */
class Coin : public IEntity2D
{
public:
	/** 코인의 상태입니다. */
	enum class EState
	{
		NONE = 0x00, // 아무것도 아닌 상태.
		MOVE = 0x01, // 지정된 위치로 이동 중.
		WAIT = 0x02, // 대기중.
		GAIN = 0x03, // 플레이어가 획득한 상태.
	};

public:
	Coin(const glm::vec2& startPos, const glm::vec2& endPos);
	virtual ~Coin();

	DISALLOW_COPY_AND_ASSIGN(Coin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 코인의 현재 상태를 얻습니다. */
	const EState& GetState() const { return state_; }

private:
	/** 코인의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 코인 내의 경계 영역 요소들을 업데이트합니다. */
	void UpdateBounds(const glm::vec2& position);
	
private:
	/** 코인 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 코인의 애니메이션을 수행하는 스프라이트 애니메이터입니다. */
	SpriteAnimator2D* animator_ = nullptr;

	/** 해당 코인을 획득했는지 확인할 플레이어입니다. */
	Player* player_ = nullptr;

	/** 코인의 이동 시작 위치입니다. */
	glm::vec2 moveStartPos_ = glm::vec2(0.0f, 0.0f);
	
	/** 코인의 이동 끝 위치입니다. */
	glm::vec2 moveEndPos_ = glm::vec2(0.0f, 0.0f);
	
	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 코인의 그림자입니다. */
	Shadow shadow_;

	/** 코인의 현재 상태입니다. */
	EState state_ = EState::NONE;

	/** 코인의 이동 시간입니다. */
	float moveTime_ = 0.0f;

	/** 코인의 최대 이동 시간입니다. */
	float maxMoveTime_ = 0.0f;
};