#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GLFW/GLFWAssertion.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

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
	SetViewport(0, 0, renderTargetWindowWidth_, renderTargetWindowHeight_);

	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	GL_API_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void GLManager::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	GLFW_API_CHECK(glfwSwapBuffers(renderTargetWindow_));
}

void GLManager::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	GL_API_CHECK(glViewport(x, y, width, height));
}

void GLManager::SetVsyncMode(bool bIsEnable)
{
	GLFW_API_CHECK(glfwSwapInterval(static_cast<int32_t>(bIsEnable)));
}

void GLManager::SetDepthMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_API_CHECK(glEnable(GL_DEPTH_TEST));
	}
	else
	{
		GL_API_CHECK(glDisable(GL_DEPTH_TEST));
	}
}

void GLManager::SetStencilMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_API_CHECK(glEnable(GL_STENCIL_TEST));
	}
	else
	{
		GL_API_CHECK(glDisable(GL_STENCIL_TEST));
	}
}

void GLManager::SetAlphaBlendMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_API_CHECK(glEnable(GL_BLEND));
		GL_API_CHECK(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO));
	}
	else
	{
		GL_API_CHECK(glDisable(GL_BLEND));
	}
}

void GLManager::SetCullFaceMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_API_CHECK(glEnable(GL_CULL_FACE));
	}
	else
	{
		GL_API_CHECK(glDisable(GL_CULL_FACE));
	}
}

const char* GLManager::GetErrorMessage(uint32_t code) const
{
	return errorMessages_.at(code).c_str();
}

void GLManager::Destroy(const GLResource* resource)
{
	int32_t resourceID = -1;
	for (uint32_t index = 0; index < resourceSize_; ++index)
	{
		GLResource* resourcePtr = resources_[index].get();
		if (resource == resourcePtr)
		{
			resourceID = static_cast<int32_t>(index);
			break;
		}
	}

	if (resourceID == -1)
	{
		return; // �ش� ���ҽ��� �̹� �Ҵ� ���� �Ǿ��ų�, GLManager�� ���ؼ� ������ ���ҽ��� �ƴ�.
	}

	if (resources_[resourceID])
	{
		if (resources_[resourceID]->IsInitialized())
		{
			resources_[resourceID]->Release();
		}

		resources_[resourceID].reset();
		usages_[resourceID] = false;
	}
}

void GLManager::Startup()
{
	errorMessages_ =
	{
		{ GL_NO_ERROR,                      "No error has been recorded. (GL_NO_ERROR)"                                                                              },
		{ GL_INVALID_ENUM,                  "An unacceptable value is specified for an enumerated argument. (GL_INVALID_ENUM)"                                       },
		{ GL_INVALID_VALUE,                 "A numeric argument is out of range. (GL_INVALID_VALUE)"                                                                 },
		{ GL_INVALID_OPERATION,             "The specified operation is not allowed in the current state. (GL_INVALID_OPERATION)"                                    },
		{ GL_INVALID_FRAMEBUFFER_OPERATION, "The framebuffer object is not complete. (GL_INVALID_FRAMEBUFFER_OPERATION)"                                             },
		{ GL_OUT_OF_MEMORY,                 "There is not enough memory left to execute the command. (GL_OUT_OF_MEMORY)"                                             },
		{ GL_STACK_UNDERFLOW,               "An attempt has been made to perform an operation that would cause an internal stack to underflow. (GL_STACK_UNDERFLOW)" },
		{ GL_STACK_OVERFLOW,                "An attempt has been made to perform an operation that would cause an internal stack to overflow. (GL_STACK_OVERFLOW)"   },
		{ GL_CONTEXT_LOST,                  "This occurs when the OpenGL context becomes lost due to a graphics card reset. (GL_CONTEXT_LOST)"                       },
		{ GL_NONE,                          "Undefined error message."                                                                                               },
	};

	renderTargetWindow_ = GLFWManager::GetRef().mainWindow_;
	renderTargetWindowWidth_ = GLFWManager::GetRef().mainWindowWidth_;
	renderTargetWindowHeight_ = GLFWManager::GetRef().mainWindowHeight_;

	GLFW_API_CHECK(glfwMakeContextCurrent(renderTargetWindow_));

	ASSERTION(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize OpenGL function.");
	ASSERTION(ImGui_ImplOpenGL3_Init(), "Failed to initialize ImGui for OpenGL.");
}

void GLManager::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();

	for (uint32_t index = 0; index < resourceSize_; ++index)
	{
		if (resources_[index])
		{
			if (resources_[index]->IsInitialized())
			{
				resources_[index]->Release();
			}

			resources_[index].reset();
			usages_[index] = false;
		}
	}

	renderTargetWindow_ = nullptr;
}
