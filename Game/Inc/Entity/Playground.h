#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"

/** �÷��̾��� �÷��� ������ ��Ÿ���� ��ƼƼ�Դϴ�. */
class Playground : public IEntity2D
{
public:
	Playground();
	virtual ~Playground();

	DISALLOW_COPY_AND_ASSIGN(Playground);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ������ ������ ����ϴ�. */
	Circle2D* GetSafeBound() { return &safeBound_; }

	/** ������ ������ ����ϴ�. */
	Circle2D* GetWarnBound() { return &warnBound_; }

private:
	/** ���� �����Դϴ�. */
	Circle2D safeBound_;

	/** ������ �����Դϴ�. */
	Circle2D warnBound_;

	/** �÷��� ������ ��Ȯ�ϰ� ǥ���ϱ� ���� �����Դϴ�. */
	glm::vec4 outlineColor_;
};