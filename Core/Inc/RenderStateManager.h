#pragma once

#include "Macro.h"

/** ������ ���� �Ŵ����� �̱����Դϴ�. */
class RenderStateManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderStateManager);

	static RenderStateManager& GetRef();
	static RenderStateManager* GetPtr();

private:
	friend class IApp;

	RenderStateManager() = default;
	virtual ~RenderStateManager() {}

private:
	static RenderStateManager instance_;
};