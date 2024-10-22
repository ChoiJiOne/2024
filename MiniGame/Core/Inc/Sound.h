#pragma once

#include <string>

#include "IResource.h"

class Sound : public IResource
{
public:
	Sound(const std::string& path);
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
	static class AudioManager* audioMgr_;

	void* audioSourcePtr_ = nullptr;
};