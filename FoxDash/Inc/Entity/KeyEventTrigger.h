#pragma once

#include <functional>

#include "Entity/IEntity.h"
#include "GLFW/GLFWManager.h"

/** Ű �Է� ���� �� Ư�� �̺�Ʈ�� �����ϴ� ��ƼƼ�Դϴ�. */
class KeyEventTrigger : public IEntity
{
public:
	KeyEventTrigger(const EKey& key, const EPress& press, const std::function<void()>& triggerEvent);
	virtual ~KeyEventTrigger();

	DISALLOW_COPY_AND_ASSIGN(KeyEventTrigger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	/** �Է��� ������ Ű�Դϴ�. */
	EKey key_;

	/** ������ �Է��� �����Դϴ�. */
	EPress press_ = EPress::NONE;
	
	/** ������ Ű�� �Է� ���� �� ������ �̺�Ʈ�Դϴ�. */
	std::function<void()> triggerEvent_ = nullptr;
};