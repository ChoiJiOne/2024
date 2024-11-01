#include "GLFWAssertion.h"
#include "GLFWManager.h"
#include "GLManager.h"

GLManager GLManager::singleton_;

GLManager& GLManager::GetRef()
{
	return singleton_;
}

GLManager* GLManager::GetPtr()
{
	return &singleton_;
}

void GLManager::Startup(GLFWwindow* renderTargetWindow)
{
	renderTargetWindow_ = renderTargetWindow;

	GLFW_API_CHECK(glfwMakeContextCurrent(renderTargetWindow_));
}

void GLManager::Shutdown()
{
	renderTargetWindow_ = nullptr;
}
