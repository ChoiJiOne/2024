#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "Macro.h"

/**
 * 2D �������� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class RenderManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager);

	/** ���� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static RenderManager& GetRef();

	/** ���� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static RenderManager* GetPtr();

private:
	/** GameApp���� ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * ���� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	RenderManager() = default;
	virtual ~RenderManager() {}

	/** ���� �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();
	
private:
	/** ���� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static RenderManager singleton_;
};