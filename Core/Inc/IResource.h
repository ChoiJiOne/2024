#pragma once

#include "GameMacro.h"

/** �� Ŭ������ ���� ���� ���ҽ� �������̽���, ���� ���� ���ҽ�(�ؽ�ó, �޽�, ��Ʈ ���)�� �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�. */
class IResource
{
public:
	IResource() = default;
	virtual ~IResource() 
	{
		if (bIsInitialized_)
		{
			Release();
		}
	}

	DISALLOW_COPY_AND_ASSIGN(IResource);

	virtual void Release() = 0;
	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};