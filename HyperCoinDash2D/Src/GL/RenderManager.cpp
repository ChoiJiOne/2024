#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26819)
#pragma warning(disable: 26451)
#pragma warning(disable: 6031)

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
	glManager_ = GLManager::GetPtr();

	uint32_t byteSize = static_cast<uint32_t>(Vertex::GetStride() * vertices_.size());
	VertexBuffer::EUsage usage = VertexBuffer::EUsage::DYNAMIC;
	vertexBuffer_ = glManager_->Create<VertexBuffer>(byteSize, usage);

	GL_API_CHECK(glGenVertexArrays(1, &vertexArrayObject_));
	GL_API_CHECK(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_->Bind();

		GL_API_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, position))));
		GL_API_CHECK(glEnableVertexAttribArray(0));

		GL_API_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, uv))));
		GL_API_CHECK(glEnableVertexAttribArray(1));

		GL_API_CHECK(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, color))));
		GL_API_CHECK(glEnableVertexAttribArray(2));

		GL_API_CHECK(glVertexAttribIPointer(3, 1, GL_INT, Vertex::GetStride(), (void*)(offsetof(Vertex, unit))));
		GL_API_CHECK(glEnableVertexAttribArray(3));

		GL_API_CHECK(glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, transparent))));
		GL_API_CHECK(glEnableVertexAttribArray(4));

		vertexBuffer_->Unbind();
	}
	GL_API_CHECK(glBindVertexArray(0));

}

void RenderManager::Shutdown()
{
	if (vertexBuffer_)
	{
		glManager_->Destroy(vertexBuffer_);
		vertexBuffer_ = nullptr;
	}

	GL_API_CHECK(glDeleteVertexArrays(1, &vertexArrayObject_));

	glManager_ = nullptr;
}

#pragma warning(pop)