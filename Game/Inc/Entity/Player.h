#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class GamePlayScene;
class SpriteAnimator2D;
class TextureAtlas2D;
class Playground;
class UIBar;
class UISkill;

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

	/** �÷��̾��� �߽� ��ġ�� ����ϴ�. */
	const glm::vec2 GetPosition() const;

	/** �÷��̾��� ��� �浹 ������ ����ϴ�. */
	const Circle2D* GetCollider() const { return &collisionBound_; }

	/** �÷��̾��� HP�� ����ϴ�. */
	float GetHP() const;

	/** �÷��̾��� HP�� �����մϴ�. */
	void SetHP(float hp);

	/** �÷��̾��� �ִ� HP�� ����ϴ�. */
	float GetMaxHP() const;

	/** �÷��̾��� �ִ� HP�� �����մϴ�. */
	void SetMaxHP(float maxHp);

	/** �÷��̾��� MP�� ����ϴ�. */
	float GetMP() const;

	/** �÷��̾��� MP�� �����մϴ�. */
	void SetMP(float mp);

	/** �÷��̾��� �ִ� MP�� ����ϴ�. */
	float GetMaxMP() const;

	/** �÷��̾��� �ִ� MP�� �����մϴ�. */
	void SetMaxMP(float maxMP);

	/** �÷��̾��� ���� ���� ����ϴ�. */
	int32_t GetCoin() const { return coin_; }

	/** �÷��̾��� ���� ���� �����մϴ�. */
	void SetCoin(int32_t coin) { coin_ = coin; }

private:
	/** �÷��̾��� �ִϸ��̼� �����Դϴ�. */
	enum class EAnimationState
	{
		IDLE = 0x00,
		RUN  = 0x01,
		HURT = 0x02,
	};

	/** �÷��̾��� �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

	/** �÷��̾��� �ִϸ��̼� ���¸� �ʱ�ȭ�մϴ�. */
	void LoadAnimations();

	/** �÷��̾��� �ִϸ��̼� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnloadAnimation();

	/** �÷��̾��� UI ��Ҹ� �ʱ�ȭ�մϴ�. */
	void LoadUIs();

	/** �÷��̾��� UI ��Ҹ� �ʱ�ȭ �����մϴ�. */
	void UnloadUIs();

	/** �÷��̾ �����Դϴ� */
	void Move(float deltaSeconds, float speed);

	/** �÷��̾��� ������/�浹/�׸��� ��ġ�� �����մϴ�. */
	void AdjustPosition(const glm::vec2& position);

private:
	/** �÷��̾� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** �÷��� �׶����Դϴ�. */
	Playground* playground_ = nullptr;

	/** ���� �÷��� ���Դϴ�. */
	GamePlayScene* gamePlayScene_ = nullptr;

	/** ������ �����Դϴ� */
	Rect2D renderBound_;

	/** �÷��̾��� ������ �ɼ��Դϴ�. */
	TextureDrawOption renderOption_;

	/** �浹 �����Դϴ�. */
	Circle2D collisionBound_;

	/** �÷��̾��� �׸����Դϴ�. */
	Shadow shadow_;

	/** �÷��̾��� �̵� �����Դϴ�. */
	glm::vec2 direction_;
	
	/** �÷��̾��� �ӵ��Դϴ�. */
	float speed_ = 0.0f;

	/** �÷��̾��� �뽬 �ӵ��Դϴ�. */
	float dashSpeed_ = 0.0f;
	
	/** ���� �ִϸ��̼��� �����Դϴ�. */
	EAnimationState animationState_ = EAnimationState::IDLE;

	/** �÷��̾��� �ִϸ��̼� ���� �� �ִϸ��̼� ���ҽ��Դϴ�. */
	std::map<EAnimationState, SpriteAnimator2D*> animations_;

	/** �÷��̾��� ���� ���Դϴ�. */
	int32_t coin_ = 0;

	/** �÷��̾��� ü���� ��Ÿ���� HP�Դϴ�. */
	UIBar* hpBar_ = nullptr;

	/** �÷��̾��� ������ ��Ÿ���� MP�Դϴ�. */
	UIBar* mpBar_ = nullptr;

	/** �÷��̾��� ���� ��ų�Դϴ�. */
	UISkill* dash_ = nullptr;

	/** �÷��̾��� ����(flash) ��ų�Դϴ�. */
	UISkill* flash_ = nullptr;

	/** �÷��̾��� ����(invincibility) ��ų�Դϴ�. */
	UISkill* invincibility_ = nullptr;

	/** �÷��̾� ���� ��� ������Ʈ�� �ð��� ������ �帣�� ��ų�Դϴ�. */
	UISkill* sandevistan_ = nullptr;

	/** ���� ���� ���� ��ų�Դϴ�. */
	UISkill* currentSkill_ = nullptr;
};
