#pragma once

#include <string>

#include <miniaudio.h>

#include "Utils/Macro.h"

/** ���� ���ҽ��Դϴ�. �� ���ҽ��� �ݵ�� AudioManager�� �̿��ؼ� �����ؾ� �մϴ�. */
class Sound
{
public:
	Sound(const std::string& path);
	virtual ~Sound();

	DISALLOW_COPY_AND_ASSIGN(Sound);

	/** ������ �ʱ�ȭ�� �����մϴ�. */
	virtual void Release();

	/** ���尡 �ʱ�ȭ �Ǿ����� Ȯ���մϴ�. */
	bool IsInitialized() const { return bIsInitialized_; }

	/** ������ ũ�⸦ �����մϴ�. �̶�, ������ ũ�� ������ 0.0 ~ 1.0 �Դϴ�. */
	virtual void SetVolume(float volume);

	/** ������ ũ�⸦ ����ϴ�. �̶�, ������ ũ�� ������ 0.0 ~ 1.0 �Դϴ�. */
	virtual float GetVolume();

	/** ���� �ݺ� ���θ� �����մϴ�. */
	virtual void SetLooping(bool bIsLoop);

	/** ������ �ݺ� ���θ� ����ϴ�. */
	virtual bool IsLooping();

	/** ���带 �÷����մϴ�. ������ ������ ���� �ִٸ� ������ �������� �÷��̵˴ϴ�. */
	virtual void Play();

	/** ���尡 �÷��� �ǰ� �ִ��� Ȯ���մϴ�. */
	virtual bool IsPlaying();

	/** ���尡 ����Ǿ����� Ȯ���մϴ�. */
	virtual bool IsDone();

	/** ���� �÷��̸� �����մϴ�. */
	virtual void Stop();

	/** ���� �÷��̰� �ߴܵǾ����� Ȯ���մϴ�. */
	virtual bool IsStopping();

	/** ������ ���¸� �ʱ�ȭ�մϴ�. */
	virtual void Reset();

private:
	/** ���尡 �ʱ�ȭ �Ǿ����� Ȯ���մϴ�. */
	bool bIsInitialized_ = false;

	/** ���� ���ҽ� ���� �������Դϴ�. */
	ma_sound* soundPtr_ = nullptr;
};