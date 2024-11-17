#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class Coin;
class Playground;
class SpriteAnimator2D;
class GamePlayScene;

/** ���� �����ϴ� ��ƼƼ�Դϴ�. */
class FireSpawner : public IEntity2D
{
public:
	FireSpawner(const glm::vec2& position);
	virtual ~FireSpawner();

	DISALLOW_COPY_AND_ASSIGN(FireSpawner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** ���� �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

private:
	/** �� ������ ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ���� ������ �����Դϴ�. */
	Playground* playground_ = nullptr;

	/** �� �������� �ִϸ��̼��� �����ϴ� ��������Ʈ �ִϸ������Դϴ�. */
	SpriteAnimator2D* animator_ = nullptr;

	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Rect2D collisionBound_;

	/** �� �������� �׸����Դϴ�. */
	Shadow shadow_;
};