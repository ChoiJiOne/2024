#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

#include "Scene/IGameScene.h"
#include "Macro.h"

/**
 * �� ������ �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class SceneManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(SceneManager);

	/** �� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static SceneManager& GetRef();

	/** �� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static SceneManager* GetPtr();

private:
	/** GameApp���� SceneManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * �� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	SceneManager() = default;
	virtual ~SceneManager() {}

	/** �� �Ŵ����� ������ GameApp ���ο����� ����˴ϴ�. */
	void Shutdown();

private:
	/** �� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static SceneManager singleton_;
};