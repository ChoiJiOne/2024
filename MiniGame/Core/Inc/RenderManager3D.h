#pragma once

#include "IApp.h"

/** 3D ���� �Ŵ����� �̱����Դϴ�. */
class RenderManager3D
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager3D);

	static RenderManager3D& Get();

private:
	friend class IApp;

	RenderManager3D() = default;
	virtual ~RenderManager3D() {}

	void Startup(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */
	void Shutdown(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */

private:
	IApp* app_ = nullptr;
};