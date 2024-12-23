#pragma once

#include <functional>

#include "Entity/IEntity.h"
#include "GLFW/GLFWManager.h"

/** 키 입력 감지 시 특정 이벤트를 수행하는 엔티티입니다. */
class KeyEventTrigger : public IEntity
{
public:
	KeyEventTrigger(const EKey& key, const EPress& press, const std::function<void()>& triggerEvent);
	virtual ~KeyEventTrigger();

	DISALLOW_COPY_AND_ASSIGN(KeyEventTrigger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

private:
	/** 입력을 감지할 키입니다. */
	EKey key_;

	/** 감지할 입력의 종류입니다. */
	EPress press_ = EPress::NONE;
	
	/** 지정한 키의 입력 감지 시 실행할 이벤트입니다. */
	std::function<void()> triggerEvent_ = nullptr;
};