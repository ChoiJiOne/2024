#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <miniaudio.h>

#include "IResource.h"


namespace GameMaker
{
class Sound : public IResource
{
public:
	explicit Sound(const std::string& path);
	virtual ~Sound();

	DISALLOW_COPY_AND_ASSIGN(Sound);

	virtual void Release() override;

	void SetVolume(float volume); /** 사운드의 크기 범위는 0.0 ~ 1.0 입니다. */
	float GetVolume(); /** 사운드의 크기 범위는 0.0 ~ 1.0 입니다. */
	void SetLooping(bool bIsLoop);
	bool IsLooping();
	void Play(); /** 이전에 중지한 적이 있다면 중지한 시점부터 플레이됩니다. */
	bool IsPlaying();
	bool IsDone();
	void Stop();
	bool IsStopping();
	void Reset();

private:
	std::unique_ptr<ma_sound> resource_ = nullptr;
};

}