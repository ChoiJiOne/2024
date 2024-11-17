#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class Coin;
class Playground;
class SpriteAnimator2D;
class GamePlayScene;

/** 코인을 생성하는 엔티티입니다. */
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

	/** 코인 스포너의 상태입니다. */
	enum class EState
	{
		WAIT     = 0x00,
		GENERATE = 0x01,
	};

private:
	/** 코인 스포너 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 코인을 생성할 영역입니다. */
	Playground* playground_ = nullptr;

	/** 코인 스포너의 애니메이션을 수행하는 스프라이트 애니메이터입니다. */
	SpriteAnimator2D* animator_ = nullptr;

	/** 게임 플레이 씬입니다. */
	GamePlayScene* gamePlayScene_ = nullptr;
	
	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Rect2D collisionBound_;

	/** 코인 스포너의 그림자입니다. */
	Shadow shadow_;

	/** 코인 스포너의 상태입니다. */
	EState state_ = EState::WAIT;

	/** 현재 관리 중인 코인입니다. */
	std::list<Coin*> coins_;

	/** 코인 생성까지 대기 시간입니다. */
	float waitTime_ = 0.0f;

	/** 최대 대기 시간입니다 */
	float maxWaitTime_ = 0.0f;

	/** 코인 생성 여부를 확인합니다. */
	bool bIsGenerateCoin_ = false;
};