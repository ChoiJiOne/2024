#include <glad/glad.h>

#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager.h"
#include "GL/Shader.h"
#include "GL/UniformBuffer.h"
#include "GL/VertexBuffer.h"
#include "Assertion.h"

RenderManager RenderManager::singleton_;

RenderManager& RenderManager::GetRef()
{
	return singleton_;
}

RenderManager* RenderManager::GetPtr()
{
	return &singleton_;
}

void RenderManager::Startup()
{
}

void RenderManager::Shutdown()
{
}
