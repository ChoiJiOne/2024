#pragma once

#include <string>
#include <list>

#include "Entity/IEntity.h"
#include "Entity/IEntity2D.h"
#include "Utils/Macro.h"

/** ���� �� �������̽��Դϴ�. */
class IGameScene
{
public:
	IGameScene();
	virtual ~IGameScene();

	DISALLOW_COPY_AND_ASSIGN(IGameScene);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	/** ���� ���� �����ߴ��� Ȯ���մϴ�. */
	bool IsEnter() { return bIsEnter_; }

	/** �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�. */
	bool IsSceneSwitched() { return bIsSwitched_; }

	/** ��ȯ�� ���� ������ ���� ����ϴ�. */
	IGameScene* GetSwitchScene() { return switchScene_; }
	
protected:
	/** ���� ���� �����ߴ��� Ȯ���մϴ�. */
	bool bIsEnter_ = false;

	/** �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�. */
	bool bIsSwitched_ = false;

	/** ��ȯ�� ���� �������Դϴ�. */
	IGameScene* switchScene_ = nullptr;

	/** �� ������ ��� ������ �Ŵ������� �������Դϴ�. */
	class AudioManager* audioManager_ = nullptr;
	class CrashManager* crashManager_ = nullptr;
	class EntityManager* entityManager_ = nullptr;
	class GLManager* glManager_ = nullptr;
	class RenderManager2D* renderManager_ = nullptr;
	class GLFWManager* glfwManager_ = nullptr;
	class SceneManager* sceneManager_ = nullptr;
};