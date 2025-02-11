#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class IObject;
class Playground;
class SpriteAnimator2D;
class GamePlayScene;

/** ������ ������Ʈ�� �����ϴ� ���� ��ƼƼ�Դϴ�. */
class RandomChest : public IEntity2D
{
public:
	RandomChest(const glm::vec2& position);
	virtual ~RandomChest();

	DISALLOW_COPY_AND_ASSIGN(RandomChest);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ���� ���� ��ƼƼ�� �����ϴ� ������Ʈ ����� ����ϴ�. */
	const std::list<IObject*>& GetObjects() const { return objects_; }

private:
	/** ���� ������ �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

	/** ���� ������ �����Դϴ�. */
	enum class EState
	{
		WAIT     = 0x00,
		GENERATE = 0x01,
	};

	/**
	 * Ư�� ���ڰ� ���� ���� �ִ��� Ȯ���մϴ�.
	 * �̶�, ������ [minNum, maxNum]�Դϴ�.
	 */
	bool IsRange(int32_t num, int32_t minNum, int32_t maxNum);

	/** ������ ������Ʈ�� �����մϴ�. */
	IObject* GenerateRandomObject();

	/** ������Ʈ ��Ҹ� �����մϴ�. */
	void CleanupObjects();

private:
	/** ���� ���� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ���� ������ ��Ҹ� ȹ���ϰų� ���ؾ� �� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** ���� ��Ҹ� ������ �����Դϴ�. */
	Playground* playground_ = nullptr;

	/** ���� ������ �ִϸ��̼��� �����ϴ� ��������Ʈ �ִϸ������Դϴ�. */
	SpriteAnimator2D* animator_ = nullptr;

	/** ���� �÷��� ���Դϴ�. */
	GamePlayScene* gamePlayScene_ = nullptr;
	
	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Rect2D collisionBound_;

	/** ���� ������ �׸����Դϴ�. */
	Shadow shadow_;

	/** ���� ������ �����Դϴ�. */
	EState state_ = EState::WAIT;
	
	/** �������� ��� �ð��Դϴ�. */
	float waitTime_ = 0.0f;

	/** �ִ� ��� �ð��Դϴ� */
	float maxWaitTime_ = 0.0f;

	/** ���� ���θ� Ȯ���մϴ�. */
	bool bIsGenerateObject_ = false;
		
	/** ���� �ּ� �ӵ��Դϴ�. */
	float minFireSpeed_ = 0.0f;

	/** ���� �ִ� �ӵ��Դϴ�. */
	float maxFireSpeed_ = 0.0f;

	/** ���� �ּ� ���� �ð��Դϴ�. */
	float minFireLifeTime_ = 0.0f;

	/** ���� �ִ�  ���� �ð��Դϴ�. */
	float maxFireLifeTime_ = 0.0f;
	
	/** ���� ���� ���� ������Ʈ���Դϴ�. */
	std::list<IObject*> objects_;

	/** ���� �̱⸦ ���� �ּ� ���Դϴ�. */
	static const int32_t MIN_RANDOM_SELECT = 1;

	/** ���� �̱⸦ ���� �ִ� ���Դϴ�. */
	static const int32_t MAX_RANDOM_SELECT = 100;
};