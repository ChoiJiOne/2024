#include <glad/glad.h>

#include "GL/GLManager.h"
#include "GLFW/GLFWAssertion.h"
#include "GLFW/GLFWManager.h"

GLManager GLManager::singleton_;

GLManager& GLManager::GetRef()
{
	return singleton_;
}

GLManager* GLManager::GetPtr()
{
	return &singleton_;
}

void GLManager::BeginFrame(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLManager::EndFrame()
{
	GLFW_API_CHECK(glfwSwapBuffers(renderTargetWindow_));
}

void GLManager::Startup(GLFWwindow* renderTargetWindow)
{
	renderTargetWindow_ = renderTargetWindow;

	GLFW_API_CHECK(glfwMakeContextCurrent(renderTargetWindow_));


	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GLManager::Shutdown()
{
	renderTargetWindow_ = nullptr;
}
