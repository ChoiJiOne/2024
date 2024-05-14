#include <glad/glad.h>

#include "GLAssertion.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* bufferPtr, uint32_t indexCount)
	: indexCount_(indexCount)
{
	uint32_t indexBufferSize = indexCount_ * static_cast<uint32_t>(sizeof(uint32_t));

	GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
	GL_FAILED(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, bufferPtr, GL_STATIC_DRAW));

	bIsInitialized_ = true;
}

IndexBuffer::~IndexBuffer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void IndexBuffer::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteBuffers(1, &indexBufferID_));

	bIsInitialized_ = false;
}

void IndexBuffer::Bind()
{
	GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
}

void IndexBuffer::Unbind()
{
	GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}