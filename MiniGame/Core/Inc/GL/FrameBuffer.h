#pragma once

#include "GL/ITexture.h"

/** ������ ������ ������ �����Դϴ�. */
class FrameBuffer : public ITexture
{
public:
	/** ������ ������ �ȼ� �����Դϴ�. */
	enum class EPixelFormat
	{
		RGB  = 0x1907,
		RGBA = 0x1908,
	};

public:
	FrameBuffer(int32_t width, int32_t height, const EPixelFormat& pixelFormat, const EFilter& filter);
	virtual ~FrameBuffer();

	virtual void Release() override;

	virtual void Active(uint32_t unit) const override;
	virtual int32_t GetWidth() const override { return width_; }
	virtual int32_t GetHeight() const override { return height_; }

	/** ������ ������ ���� ���۸� �ʱ�ȭ�մϴ�. */
	void Clear(float red, float green, float blue, float alpha);

	/** ������ ���۸� ������ ���������ο� ���ε��մϴ�. */
	void Bind();

	/** ������ ���۸� ������ ���������ο� ���ε� �����մϴ�. */
	void Unbind();

private:
	int32_t width_ = 0;
	int32_t height_ = 0;

	/** ������ ���� ID�Դϴ�. */
	uint32_t frameBufferID_ = 0;

	/** ���� ���� ID�Դϴ�. */
	uint32_t colorBufferID_ = 0;
};