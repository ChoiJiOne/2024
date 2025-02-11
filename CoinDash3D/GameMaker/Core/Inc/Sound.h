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

	void SetVolume(float volume); /** ������ ũ�� ������ 0.0 ~ 1.0 �Դϴ�. */
	float GetVolume(); /** ������ ũ�� ������ 0.0 ~ 1.0 �Դϴ�. */
	void SetLooping(bool bIsLoop);
	bool IsLooping();
	void Play(); /** ������ ������ ���� �ִٸ� ������ �������� �÷��̵˴ϴ�. */
	bool IsPlaying();
	bool IsDone();
	void Stop();
	bool IsStopping();
	void Reset();

private:
	std::unique_ptr<ma_sound> resource_ = nullptr;
};

}