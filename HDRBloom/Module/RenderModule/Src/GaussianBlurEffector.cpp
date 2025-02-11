#pragma warning(push)
#pragma warning(disable: 26451)

#include <glad/glad.h>

#include "Assertion.h"
#include "ColorFrameBuffer.h"
#include "FrameBuffer.h"
#include "GaussianBlurEffector.h"
#include "Vertex2D.h"

GaussianBlurEffector::GaussianBlurEffector()
	: Shader("Resource/Shader/FrameRenderer.vert", "Resource/Shader/GaussianBlur.frag")
	, vertexBuffer_(VertexPosition2D::GetStride()* MAX_VERTEX_SIZE, VertexBuffer::EUsage::Static)
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

GaussianBlurEffector::~GaussianBlurEffector()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GaussianBlurEffector::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	Shader::Release();
}

void GaussianBlurEffector::Execute(FrameBuffer* scene, ColorFrameBuffer* pingpong[2])
{
	Shader::Bind();

	bool bHorizontal = true;

	pingpong[0]->Bind();
	{
		Shader::SetUniform("bHorizontal", bHorizontal);

		scene->Active(1, 0);
		GL_FAILED(glBindVertexArray(vertexArrayObject_));
		GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE));
		GL_FAILED(glBindVertexArray(0));
	}
	pingpong[0]->Unbind();

	for (uint32_t count = 1; count <= COUNT_PING_PONG; ++count)
	{
		bHorizontal = !bHorizontal;
		Shader::SetUniform("bHorizontal", bHorizontal);
		
		pingpong[(count % 2)]->Bind();
		{
			pingpong[((count + 1) % 2)]->Active(0);
			GL_FAILED(glBindVertexArray(vertexArrayObject_));
			GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE));
			GL_FAILED(glBindVertexArray(0));
		}
		pingpong[(count % 2)]->Unbind();
	}

	Shader::Unbind();
}

#pragma warning(pop)