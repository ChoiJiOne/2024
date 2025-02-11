#pragma warning(push)
#pragma warning(disable: 26451)

#include <glad/glad.h>

#include "Assertion.h"
#include "ColorFrameBuffer.h"
#include "FrameRenderer.h"
#include "FrameBuffer.h"

FrameRenderer::FrameRenderer()
	: Shader("Resource/Shader/FrameRenderer.vert", "Resource/Shader/FrameRenderer.frag")
	, vertexBuffer_(VertexPosition2D::GetStride() * MAX_VERTEX_SIZE, VertexBuffer::EUsage::Static)
{
	std::array<VertexPosition2D, MAX_VERTEX_SIZE> vertices =
	{
		VertexPosition2D(-1.0, -1.0),
		VertexPosition2D(+1.0, -1.0),
		VertexPosition2D(-1.0, +1.0),
		VertexPosition2D(+1.0, +1.0),
		VertexPosition2D(-1.0, +1.0),
		VertexPosition2D(+1.0, -1.0),
	};
	vertexBuffer_.SetBufferData(vertices.data(), static_cast<uint32_t>(VertexPosition2D::GetStride() * MAX_VERTEX_SIZE));

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));

	vertexBuffer_.Bind();
	{
		GL_FAILED(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VertexPosition2D::GetStride(), (void*)(offsetof(VertexPosition2D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));
	}
	vertexBuffer_.Unbind();

	GL_FAILED(glBindVertexArray(0));
}

FrameRenderer::~FrameRenderer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void FrameRenderer::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	Shader::Release();
}

void FrameRenderer::DrawColorFrameBuffer(const ColorFrameBuffer* framebuffer)
{
	Shader::Bind();
	framebuffer->Active(0);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}

void FrameRenderer::DrawFrameBuffer(const FrameBuffer* framebuffer, uint32_t index)
{
	Shader::Bind();
	framebuffer->Active(index, 0);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}

#pragma warning(pop)