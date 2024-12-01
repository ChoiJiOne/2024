#pragma once

#include <string>

#include <miniaudio.h>

#include "Utils/Macro.h"

/** 사운드 리소스입니다. 이 리소스는 반드시 AudioManager를 이용해서 생성해야 합니다. */
class Sound
{
public:
	Sound(const std::string& path);
	virtual ~Sound();

	DISALLOW_COPY_AND_ASSIGN(Sound);

	/** 사운드의 초기화를 해제합니다. */
	virtual void Release();

	/** 사운드가 초기화 되었는지 확인합니다. */
	bool IsInitialized() const { return bIsInitialized_; }

	/** 사운드의 크기를 설정합니다. 이때, 사운드의 크기 범위는 0.0 ~ 1.0 입니다. */
	virtual void SetVolume(float volume);

	/** 사운드의 크기를 얻습니다. 이때, 사운드의 크기 범위는 0.0 ~ 1.0 입니다. */
	virtual float GetVolume();

	/** 사운드 반복 여부를 설정합니다. */
	virtual void SetLooping(bool bIsLoop);

	/** 사운드의 반복 여부를 얻습니다. */
	virtual bool IsLooping();

	/** 사운드 플레이를 시작합니다. */
	virtual void Start();

	/** 사운드를 플레이합니다. 이전에 중지한 적이 있다면 중지한 시점부터 플레이됩니다. */
	virtual void Play();

	/** 사운드가 플레이 되고 있는지 확인합니다. */
	virtual bool IsPlaying();

	/** 사운드가 종료되었는지 확인합니다. */
	virtual bool IsDone();

	/** 사운드 플레이를 중지합니다. */
	virtual void Stop();

	/** 사운드 플레이가 중단되었는지 확인합니다. */
	virtual bool IsStopping();

	/** 사운드의 상태를 초기화합니다. */
	virtual void Reset();

private:
	/** 사운드가 초기화 되었는지 확인합니다. */
	bool bIsInitialized_ = false;

	/** 사운드 리소스 원본입니다. */
	ma_sound sound_;
};