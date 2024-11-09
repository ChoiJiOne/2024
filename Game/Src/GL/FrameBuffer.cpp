#include <glad/glad.h>

#include "GL/FrameBuffer.h"
#include "GL/GLAssertion.h"
#include "Utils/Assertion.h"

FrameBuffer::FrameBuffer(int32_t width, int32_t height, const EPixelFormat& pixelFormat, const EFilter& filter)
	: width_(width)
	, height_(height)
{
	GL_API_CHECK(glGenFramebuffers(1, &frameBufferID_));
	GL_API_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID_));

	float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	GL_API_CHECK(glGenTextures(1, &colorBufferID_));
	GL_API_CHECK(glBindTexture(GL_TEXTURE_2D, colorBufferID_));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	GL_API_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter)));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter)));
	GL_API_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pixelFormat), width_, height_, 0, static_cast<GLenum>(pixelFormat), GL_UNSIGNED_BYTE, nullptr));
	GL_API_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferID_, 0));

	uint32_t attachment = GL_COLOR_ATTACHMENT0;
	GL_API_CHECK(glDrawBuffers(1, &attachment));

	GLenum state = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GL_EXP_CHECK(state == GL_FRAMEBUFFER_COMPLETE);

	GL_API_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	bIsInitialized_ = true;
}

FrameBuffer::~FrameBuffer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void FrameBuffer::Release()
{
	CHECK(bIsInitialized_);

	GL_API_CHECK(glDeleteTextures(1, &colorBufferID_));
	GL_API_CHECK(glDeleteFramebuffers(1, &frameBufferID_));

	bIsInitialized_ = false;
}

void FrameBuffer::Active(uint32_t unit) const
{
	GL_API_CHECK(glActiveTexture(GL_TEXTURE0 + unit));
	GL_API_CHECK(glBindTexture(GL_TEXTURE_2D, colorBufferID_));
}

void FrameBuffer::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	GL_API_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void FrameBuffer::Bind()
{
	GL_API_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID_));
}

void FrameBuffer::Unbind()
{
	GL_API_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}