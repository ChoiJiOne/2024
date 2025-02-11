#pragma once

#include "Macro.h"


namespace GameMaker
{ 
/**
 * �� Ŭ������ ���� ���� ���ҽ� �������̽���, ���� ���� ���ҽ� (�ؽ�ó, �޽�, ������, ��Ʈ ���)�� �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�.
 */
class IResource
{
public:
	IResource() = default;
	virtual ~IResource() {}

	DISALLOW_COPY_AND_ASSIGN(IResource);

	virtual void Release() = 0;

	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};

}