#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class Coin;
class Playground;
class SpriteAnimator2D;
class GamePlayScene;

/** ������ �����ϴ� ��ƼƼ�Դϴ�. */
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
	/** ���� �������� �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

	/** ���� �������� �����Դϴ�. */
	enum class EState
	{
		WAIT     = 0x00,
		GENERATE = 0x01,
	};

private:
	/** ���� ������ ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ������ ������ �����Դϴ�. */
	Playground* playground_ = nullptr;

	/** ���� �������� �ִϸ��̼��� �����ϴ� ��������Ʈ �ִϸ������Դϴ�. */
	SpriteAnimator2D* animator_ = nullptr;

	/** ���� �÷��� ���Դϴ�. */
	GamePlayScene* gamePlayScene_ = nullptr;
	
	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Rect2D collisionBound_;

	/** ���� �������� �׸����Դϴ�. */
	Shadow shadow_;

	/** ���� �������� �����Դϴ�. */
	EState state_ = EState::WAIT;

	/** ���� ���� ���� �����Դϴ�. */
	std::list<Coin*> coins_;

	/** ���� �������� ��� �ð��Դϴ�. */
	float waitTime_ = 0.0f;

	/** �ִ� ��� �ð��Դϴ� */
	float maxWaitTime_ = 0.0f;

	/** ���� ���� ���θ� Ȯ���մϴ�. */
	bool bIsGenerateCoin_ = false;
};