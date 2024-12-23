#include "Entity/KeyEventTrigger.h"
#include "Utils/Assertion.h"

KeyEventTrigger::KeyEventTrigger(const EKey& key, const EPress& press, const std::function<void()>& triggerEvent)
	: key_(key)
	, press_(press)
	, triggerEvent_(triggerEvent)
{
	bIsInitialized_ = true;
}

KeyEventTrigger::~KeyEventTrigger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void KeyEventTrigger::Tick(float deltaSeconds)
{
	GLFWManager& glfwManager = GLFWManager::GetRef();
	if (glfwManager.GetKeyPress(key_) == press_)
	{
		triggerEvent_();
	}
}

void KeyEventTrigger::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}