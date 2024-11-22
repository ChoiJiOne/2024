#pragma once

#include "Utils/Macro.h"

/** 
 * 전체적인 게임의 속성을 관리하는 엔티티입니다. 
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GameManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GameManager);

	/** 게임 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GameManager& GetRef();

	/** 게임 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GameManager* GetPtr();

private:
	/** IApp에서 게임 매니저의 내부에 접근할 수 있도록 설정. */
	friend class IApp;

	/**
	 * 게임 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GameManager() = default;
	virtual ~GameManager() {}

	/** 게임 매니저의 초기화/해제는 IApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** 게임 매니저의 싱글턴 객체입니다. */
	static GameManager singleton_;
};
