#pragma once

#include "GL/ITexture.h"

/** 렌더링 가능한 프레임 버퍼입니다. */
class FrameBuffer : public ITexture
{
public:
	/** 프레임 버퍼의 픽셀 포멧입니다. */
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

	/** 프레임 버퍼의 색상 버퍼를 초기화합니다. */
	void Clear(float red, float green, float blue, float alpha);

	/** 프레임 버퍼를 렌더링 파이프라인에 바인딩합니다. */
	void Bind();

	/** 프레임 버퍼를 렌더링 파이프라인에 바인딩 해제합니다. */
	void Unbind();

private:
	int32_t width_ = 0;
	int32_t height_ = 0;

	/** 프레임 버퍼 ID입니다. */
	uint32_t frameBufferID_ = 0;

	/** 색상 버퍼 ID입니다. */
	uint32_t colorBufferID_ = 0;
};