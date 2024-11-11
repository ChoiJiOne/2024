#include <glfw/glfw3.h>

#include "GLFW/InputManager.h"

InputManager InputManager::singleton_;

InputManager& InputManager::GetRef()
{
	return singleton_;
}

InputManager* InputManager::GetPtr()
{
	return &singleton_;
}
