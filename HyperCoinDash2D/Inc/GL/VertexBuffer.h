#pragma once

#include <cstdint>

#include "GLResource.h"

/** 렌더링 파이프라인에 바인딩 가능한 버텍스 버퍼입니다. */
class VertexBuffer : public GLResource
{
public:
	/** 버텍스 버퍼의 사용 형식입니다. */
	enum class EUsage
	{
		NONE    = 0x0000,
		STREAM  = 0x88E0,
		STATIC  = 0x88E4,
		DYNAMIC = 0x88E8,
	};

public:
	VertexBuffer(uint32_t byteSize, const EUsage& usage);
	VertexBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage);
	virtual ~VertexBuffer();

	DISALLOW_COPY_AND_ASSIGN(VertexBuffer);

	virtual void Release() override;

	void Bind();
	void Unbind();

	void SetBufferData(const void* bufferPtr, uint32_t bufferSize);

private:
	uint32_t vertexBufferID_ = 0;
	uint32_t byteSize_ = 0;
	EUsage usage_ = EUsage::NONE;
};