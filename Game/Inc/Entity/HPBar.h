#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class UICamera;

/** �÷��̾��� HP�� ǥ���ϴ� UI ��ƼƼ�Դϴ�. */
class HPBar : public IEntity2D
{
public:
	HPBar(UICamera* uiCamera);
	virtual ~HPBar();

	DISALLOW_COPY_AND_ASSIGN(HPBar);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** �÷��̾��� ���� HP�� ����ϴ�. */
	float GetHP() const { return hp_; }

	/** �÷��̾��� HP ���� �����մϴ�. */
	void SetHP(float hp);

private:
	/** HP�� �������� ������ �� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** HP���� ��׶��� ũ���Դϴ�. */
	Rect2D background_;

	/** HP���� �����Դϴ�. */
	Rect2D hpBound_;

	/** HP���� ��׶��� �����Դϴ�. */
	glm::vec4 backgroundColor_;

	/** HP���� ü�� �����Դϴ�. */
	glm::vec4 hpColor_;

	/** �÷��̾��� HP�Դϴ�. */
	float hp_ = 0.0f;

	/** �÷��̾��� HP ������ �� �ε巯�� ��ȯ�� ���� ��ũ�Դϴ�. */
	float hpMark_ = 0.0f;

	/** �÷��̾��� �ּ� HP�Դϴ�. */
	float minHp_ = 0.0f;

	/** �÷��̾��� �ִ� HP�Դϴ�. */
	float maxHp_ = 0.0f;

	/** �÷��̾��� HP ������ �� �ε巯�� ��ȯ�� ���� �ӵ��Դϴ�. */
	float hpSpeed_ = 0.0f;
};