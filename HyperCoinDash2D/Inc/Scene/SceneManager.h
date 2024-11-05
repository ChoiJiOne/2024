#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

#include "Scene/IGameScene.h"
#include "Macro.h"

/**
 * 씬 관리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class SceneManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(SceneManager);

	/** 씬 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static SceneManager& GetRef();

	/** 씬 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static SceneManager* GetPtr();

private:
	/** GameApp에서 SceneManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 씬 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	SceneManager() = default;
	virtual ~SceneManager() {}

	/** 씬 매니저의 해제는 GameApp 내부에서만 수행됩니다. */
	void Shutdown();

private:
	/** 씬 매니저의 싱글턴 객체입니다. */
	static SceneManager singleton_;
};