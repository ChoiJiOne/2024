#pragma once

#include <cstdint>

#include "GLResource.h"

/** ������ ���������ο� ���ε� ������ ���ؽ� �����Դϴ�. */
class VertexBuffer : public GLResource
{
public:
	/** ���ؽ� ������ ��� �����Դϴ�. */
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