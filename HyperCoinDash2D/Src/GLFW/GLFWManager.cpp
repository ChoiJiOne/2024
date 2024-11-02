#include <Windows.h>

#include "GLFW/GLFWAssertion.h"
#include "GLFW/GLFWManager.h"
#include "MemoryAlloc.h"

#define GL_MAJOR_VERSION 4
#define GL_MINOR_VERSION 6

GLFWManager GLFWManager::singleton_;

void GLFWErrorCallback(int32_t errorCode, const char* description)
{
	GLFWManager::GetRef().SetLsatError(errorCode, description);
}

GLFWManager& GLFWManager::GetRef()
{
	return singleton_;
}

GLFWManager* GLFWManager::GetPtr()
{
	return &singleton_;
}

void GLFWManager::SetLsatError(int32_t code, const char* description)
{
	bIsDetectError_ = true;
	errorCode_ = code;
	errorDescription_ = description;

	switch (errorCode_)
	{
	case GLFW_NO_ERROR:
		errorMessage_ = "No error has occurred.";
		break;

	case GLFW_NOT_INITIALIZED:
		errorMessage_ = "GLFW has not been initialized.";
		break;

	case GLFW_NO_CURRENT_CONTEXT:
		errorMessage_ = "No context is current for this thread.";
		break;

	case GLFW_INVALID_ENUM:
		errorMessage_ = "One of the arguments to the function was an invalid enum value.";
		break;

	case GLFW_INVALID_VALUE:
		errorMessage_ = "One of the arguments to the function was an invalid value.";
		break;

	case GLFW_OUT_OF_MEMORY:
		errorMessage_ = "A memory allocation failed.";
		break;

	case GLFW_API_UNAVAILABLE:
		errorMessage_ = "GLFW could not find support for the requested API on the system.";
		break;

	case GLFW_VERSION_UNAVAILABLE:
		errorMessage_ = "The requested OpenGL or OpenGL ES version is not available.";
		break;

	case GLFW_PLATFORM_ERROR:
		errorMessage_ = "A platform-specific error occurred that does not match any of the more specific categories.";
		break;

	case GLFW_FORMAT_UNAVAILABLE:
		errorMessage_ = "The requested format is not supported or available.";
		break;

	case GLFW_NO_WINDOW_CONTEXT:
		errorMessage_ = "The specified window does not have an OpenGL or OpenGL ES context.";
		break;

	default:
		errorMessage_ = "Undefined GLFW error.";
		break;
	}
}

GLFWwindow* GLFWManager::Startup(int32_t width, int32_t height, const char* title)
{
	glfwSetErrorCallback(GLFWErrorCallback);

	GLFWallocator allocator;
	allocator.allocate = MemoryAlloc;
	allocator.reallocate = MemoryRealloc;
	allocator.deallocate = MemoryFree;

	GLFW_API_CHECK(glfwInitAllocator(&allocator));
	GLFW_EXP_CHECK(glfwInit());

	GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
	GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR_VERSION));
	GLFW_API_CHECK(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));
	GLFW_API_CHECK(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

	mainWindow_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
	GLFW_EXP_CHECK(mainWindow_ != nullptr);

	return mainWindow_;
}

void GLFWManager::Shutdown()
{
	if (mainWindow_)
	{
		glfwDestroyWindow(mainWindow_);
		mainWindow_ = nullptr;
	}

	glfwTerminate();
}
