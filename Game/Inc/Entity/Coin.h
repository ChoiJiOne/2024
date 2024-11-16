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
	Coin(const glm::vec2& position);
	virtual ~Coin();

	DISALLOW_COPY_AND_ASSIGN(Coin);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이어가 코인을 획득했는지 확인합니다. */
	bool IsGain() const { return bIsGain_; }

	/** 코인의 상태를 초기화합니다. */
	void Reset(const glm::vec2& position);

private:
	/** 코인의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

private:
	/** 코인 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 코인의 애니메이션을 수행하는 스프라이트 애니메이터입니다. */
	SpriteAnimator2D* animator_ = nullptr;

	/** 해당 코인을 획득했는지 확인할 플레이어입니다. */
	Player* player_ = nullptr;

	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 코인의 그림자입니다. */
	Shadow shadow_;

	/** 코인을 플레이어가 획득했는지 확인합니다. */
	bool bIsGain_ = false;
};