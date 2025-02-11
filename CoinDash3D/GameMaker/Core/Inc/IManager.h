#pragma once

#include "Macro.h"


namespace GameMaker
{
/**
 * �� Ŭ������ �Ŵ��� �������̽� Ŭ������, ���̻�� �Ŵ���(Manager)��� ���� Ŭ������ �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�.
 * ����, �� Ŭ������ ��ӹ��� �Ŵ��� Ŭ������ �̱���(Singleton)���� �����Ǿ�� �մϴ�.
 */
class IManager
{
	DISALLOW_COPY_AND_ASSIGN(IManager);

	virtual void Startup() = 0;
	virtual void Shutdown() = 0;
	
protected:
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(IManager);

protected:
	bool bIsStartup_ = false;
};

}