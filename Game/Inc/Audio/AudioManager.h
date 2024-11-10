#pragma once

#include <array>
#include <memory>
#include <string>

#include <miniaudio.h>

#include "Utils/Macro.h"

/** 
 * ����� ���� �ʱ�ȭ/���� �� ���� ���ҽ��� �����ϴ� �Ŵ����Դϴ�. 
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class AudioManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(AudioManager);

	/** ����� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static AudioManager& GetRef();

	/** ����� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static AudioManager* GetPtr();

private:
	/** GameApp���� AudioManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * ����� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	AudioManager() = default;
	virtual ~AudioManager() {}

	/** ����� �Ŵ����� �ʱ�ȭ/������ GameApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

private:
	/** ����� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static AudioManager singleton_;
};