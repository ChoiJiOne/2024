#pragma warning(push)
#pragma warning(disable: 26451)

#include <glad/glad.h>

#include "Assertion.h"
#include "BloomEffector.h"
#include "ColorFrameBuffer.h"
#include "FrameBuffer.h"
#include "Vertex2D.h"

BloomEffector::BloomEffector()
	: Shader("Resource/Shader/FrameRenderer.vert", "Resource/Shader/Bloom.frag")
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

BloomEffector::~BloomEffector()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void BloomEffector::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	Shader::Release();
}

void BloomEffector::Execute(FrameBuffer* scene, ColorFrameBuffer* blur)
{
	Shader::Bind();

	scene->Active(0, 0);
	blur->Active(1);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}

#pragma warning(pop)