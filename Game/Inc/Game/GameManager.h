#pragma once

#include "Utils/Macro.h"

/** 
 * ��ü���� ������ �Ӽ��� �����ϴ� ��ƼƼ�Դϴ�. 
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GameManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GameManager);

	/** ���� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GameManager& GetRef();

	/** ���� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GameManager* GetPtr();

private:
	/** IApp���� ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class IApp;

	/**
	 * ���� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GameManager() = default;
	virtual ~GameManager() {}

	/** ���� �Ŵ����� �ʱ�ȭ/������ IApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

private:
	/** ���� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GameManager singleton_;
};
