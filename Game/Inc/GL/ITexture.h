#pragma once

#include <cstdint>

#include "GLResource.h"

/** OpenGL �ؽ�ó ���ҽ��� �������̽��Դϴ�. */
class ITexture : public GLResource
{
public:
	ITexture() = default;
	virtual ~ITexture() {}

	virtual void Release() = 0;

	/** �ؽ�ó�� ������ ���������ο� ���ε��ϰ� Ȱ��ȭ�մϴ�. */
	virtual void Active(uint32_t unit) const = 0;
};