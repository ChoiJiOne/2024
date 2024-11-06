#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26819)
#pragma warning(disable: 26451)
#pragma warning(disable: 6031)

#include <glad/glad.h>

#include "Entity/Camera2D.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Shader.h"
#include "GL/UniformBuffer.h"
#include "GL/VertexBuffer.h"
#include "Utils/Assertion.h"

RenderManager2D RenderManager2D::singleton_;

RenderManager2D& RenderManager2D::GetRef()
{
	return singleton_;
}

RenderManager2D* RenderManager2D::GetPtr()
{
	return &singleton_;
}

void RenderManager2D::Startup()
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

		vertexBuffer_->Unbind();
	}
	GL_API_CHECK(glBindVertexArray(0));

}

void RenderManager2D::Shutdown()
{
	glManager_->Destroy(vertexBuffer_);
	vertexBuffer_ = nullptr;
	
	GL_API_CHECK(glDeleteVertexArrays(1, &vertexArrayObject_));

	glManager_ = nullptr;
}

#pragma warning(pop)