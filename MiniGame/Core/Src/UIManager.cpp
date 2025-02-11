#include "Assertion.h"
#include "UIManager.h"

UIManager UIManager::instance_;

UIManager& UIManager::GetRef()
{
	return instance_;
}

UIManager* UIManager::GetPtr()
{
	return &instance_;
}

void UIManager::Startup()
{
}

void UIManager::Shutdown()
{
}