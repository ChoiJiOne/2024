#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class Coin;

/** 필드의 코인을 관리하는 엔티티입니다. */
class CoinSpawner : public IEntity2D
{
public:
	CoinSpawner(const glm::vec2& position);
	virtual ~CoinSpawner();

	DISALLOW_COPY_AND_ASSIGN(CoinSpawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 코인 스포너의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

private:
	/** 코인 스포너 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 코인 스포너의 애니메이션을 수행하는 스프라이트 애니메이터입니다. */
	SpriteAnimator2D* animator_ = nullptr;

	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Rect2D collisionBound_;

	/** 코인 스포너의 그림자입니다. */
	Shadow shadow_;
};