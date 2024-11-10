#pragma once

#include <array>
#include <memory>
#include <string>

#include <miniaudio.h>

#include "Utils/Macro.h"

/** 
 * 오디오 엔진 초기화/해제 및 사운드 리소스를 관리하는 매니저입니다. 
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class AudioManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(AudioManager);

	/** 오디오 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static AudioManager& GetRef();

	/** 오디오 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static AudioManager* GetPtr();

private:
	/** GameApp에서 AudioManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 오디오 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	AudioManager() = default;
	virtual ~AudioManager() {}

	/** 오디오 매니저의 초기화/해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** 오디오 매니저의 싱글턴 객체입니다. */
	static AudioManager singleton_;
};