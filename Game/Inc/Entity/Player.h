#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 플레이어가 조종할 엔티티입니다. */
class Player : public IEntity2D
{
public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 플레이어 렌더링 시 참조할 텍스처 아틀라스입니다. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** 렌더링 영역입니다 */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;
};
