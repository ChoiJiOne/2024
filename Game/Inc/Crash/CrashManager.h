#pragma once

#include <functional>
#include <string>

#include "Utils/Macro.h"

/**
 * ���÷����̼��� ũ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class CrashManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(CrashManager);

	/** ũ���� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static CrashManager& GetRef();

	/** ũ���� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static CrashManager* GetPtr();

	/** ũ���� �߻� �� ȣ���� �ݹ� �Լ��� �����մϴ�. */
	void SetCrashCallbackEvent(const std::function<void()>& callback);
	
private:
	/** GameApp���� ũ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����.  */
	friend class GameApp;

	/**
	 * ũ���� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	CrashManager() = default;
	virtual ~CrashManager() {}

	/** ũ���� �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

private:
	/** ũ���� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static CrashManager instance_;
};
