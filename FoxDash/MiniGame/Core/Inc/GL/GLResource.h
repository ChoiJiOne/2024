#pragma once

#include "Utils/Macro.h"

/** 이 클래스는 OpenGL 리소스 (버텍스 버퍼, 인덱스 버퍼, 셰이더, 텍스처, 프레임 버퍼 등등)들이 반드시 상속 받아야 하는 인터페이스입니다. */
class GLResource
{
public:
	GLResource() = default;
	virtual ~GLResource() {}

	DISALLOW_COPY_AND_ASSIGN(GLResource);

	virtual void Release() = 0;

	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};