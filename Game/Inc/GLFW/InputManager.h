#pragma once

#include <array>

#include "Utils/Macro.h"

/**
 * 키보드, 마우스, 윈도우 이벤트 등 입력 처리를 관리하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class InputManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(InputManager);

	/** 입력 처리 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static InputManager& GetRef();

	/** 입력 처리 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static InputManager* GetPtr();

private:
	/** GameApp에서 InputManager의 내부에 접근할 수 있도록 설정.  */
	friend class GameApp;

	/** 
	 * 입력 처리 매니저의 기본 생성자와 가상 소멸자입니다. 
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	InputManager() = default;
	virtual ~InputManager() {}

private:
	/** 입력 처리 매니저의 싱글턴 객체입니다. */
	static InputManager singleton_;
};