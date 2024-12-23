#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GL/FrameBuffer.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/PostProcessor.h"
#include "GL/UniformBuffer.h"
#include "GL/VertexBuffer.h"

PostProcessor::PostProcessor(const std::string& vsSource, const std::string& fsSource)
	: Shader(vsSource, fsSource)
{
	std::array<Vertex, MAX_VERTEX_SIZE> vertices =
	{
		Vertex{ glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		Vertex{ glm::vec2(+1.0f, +1.0f), glm::vec2(1.0f, 1.0f) },
		Vertex{ glm::vec2(-1.0f, +1.0f), glm::vec2(0.0f, 1.0f) },

		Vertex{ glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		Vertex{ glm::vec2(+1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		Vertex{ glm::vec2(+1.0f, +1.0f), glm::vec2(1.0f, 1.0f) },
	};

	uint32_t vertexBufferByteSize = static_cast<uint32_t>(Vertex::GetStride() * vertices.size());
	VertexBuffer::EUsage vertexBufferUsage = VertexBuffer::EUsage::STATIC;
	vertexBuffer_ = GLManager::GetRef().Create<VertexBuffer>(vertices.data(), vertexBufferByteSize, vertexBufferUsage);

	GL_API_CHECK(glGenVertexArrays(1, &vertexArrayObject_));
	GL_API_CHECK(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_->Bind();

		GL_API_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, position))));
		GL_API_CHECK(glEnableVertexAttribArray(0));

		GL_API_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, uv))));
		GL_API_CHECK(glEnableVertexAttribArray(1));

		vertexBuffer_->Unbind();
	}
	GL_API_CHECK(glBindVertexArray(0));

	uint32_t uniformBufferByteSize = static_cast<uint32_t>(sizeof(PerFrameUBO));
	UniformBuffer::EUsage uniformBufferUsage = UniformBuffer::EUsage::DYNAMIC;
	uniformBuffer_ = GLManager::GetRef().Create<UniformBuffer>(uniformBufferByteSize, uniformBufferUsage);
}

PostProcessor::~PostProcessor()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PostProcessor::Release()
{
	if (uniformBuffer_)
	{
		GLManager::GetRef().Destroy(uniformBuffer_);
		uniformBuffer_ = nullptr;
	}

	if (vertexArrayObject_)
	{
		GL_API_CHECK(glDeleteVertexArrays(1, &vertexArrayObject_));
		vertexArrayObject_ = 0;
	}

	if (vertexBuffer_)
	{
		GLManager::GetRef().Destroy(vertexBuffer_);
		vertexBuffer_ = nullptr;
	}
	
	Shader::Release();
}

void PostProcessor::SetBlendColor(const glm::vec3& color, float factor)
{
	bIsNeedUpdate_ = true;
	perFrameUBO_.color = glm::vec4(color, factor);
}

void PostProcessor::Blit(const EType& type, FrameBuffer* frameBuffer)
{
	if (static_cast<int32_t>(type) != perFrameUBO_.type)
	{
		bIsNeedUpdate_ = true;
		perFrameUBO_.type = static_cast<int32_t>(type);
	}

	if (bIsNeedUpdate_)
	{
		uniformBuffer_->SetBufferData(&perFrameUBO_, static_cast<uint32_t>(sizeof(PerFrameUBO)));
		bIsNeedUpdate_ = false;
	}

	Bind();
	{
		uniformBuffer_->BindSlot(UNIFORM_BUFFER_BIND_SLOT);
		frameBuffer->Active(FRAME_BUFFER_BIND_SLOT);

		GL_API_CHECK(glBindVertexArray(vertexArrayObject_));
		GL_API_CHECK(glDrawArrays(static_cast<GLenum>(GL_TRIANGLES), 0, MAX_VERTEX_SIZE));
		GL_API_CHECK(glBindVertexArray(0));
	}
	Unbind();
}