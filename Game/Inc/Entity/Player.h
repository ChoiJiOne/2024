#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** �÷��̾ ������ ��ƼƼ�Դϴ�. */
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
	/** �÷��̾� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** ������ �����Դϴ� */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Circle2D collisionBound_;
};
