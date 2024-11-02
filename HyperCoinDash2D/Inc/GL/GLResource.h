#pragma once

#include "Macro.h"

/** �� Ŭ������ OpenGL ���ҽ� (���ؽ� ����, �ε��� ����, ���̴�, �ؽ�ó, ������ ���� ���)���� �ݵ�� ��� �޾ƾ� �ϴ� �������̽��Դϴ�. */
class GLResource
{
public:
	GLResource() = default;
	virtual ~GLResource() {}

	DISALLOW_COPY_AND_ASSIGN(GLResource);

	virtual void Release() = 0;

	virtual void Release() = 0;
	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};