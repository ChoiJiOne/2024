#pragma once

#include "Macro.h"

/** �� Ŭ������ ��ƼƼ �������̽���, ��ƼƼ�� �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�. */
class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity()
	{
		if (bIsInitialized_)
		{
			Release();
		}
	}

	DISALLOW_COPY_AND_ASSIGN(IEntity);

	virtual void Release() = 0;
	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};