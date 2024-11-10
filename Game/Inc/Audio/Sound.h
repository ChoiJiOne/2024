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
	void SetVolume(float volume);

	/** ������ ũ�⸦ ����ϴ�. �̶�, ������ ũ�� ������ 0.0 ~ 1.0 �Դϴ�. */
	float GetVolume();

	/** ���� �ݺ� ���θ� �����մϴ�. */
	void SetLooping(bool bIsLoop);

	/** ������ �ݺ� ���θ� ����ϴ�. */
	bool IsLooping();

	/** ���带 �÷����մϴ�. ������ ������ ���� �ִٸ� ������ �������� �÷��̵˴ϴ�. */
	void Play();

	/** ���尡 �÷��� �ǰ� �ִ��� Ȯ���մϴ�. */
	bool IsPlaying();

	/** ���尡 ����Ǿ����� Ȯ���մϴ�. */
	bool IsDone();

	/** ���� �÷��̸� �����մϴ�. */
	void Stop();

	/** ���� �÷��̰� �ߴܵǾ����� Ȯ���մϴ�. */
	bool IsStopping();

	/** ������ ���¸� �ʱ�ȭ�մϴ�. */
	void Reset();

private:
	/** ���尡 �ʱ�ȭ �Ǿ����� Ȯ���մϴ�. */
	bool bIsInitialized_ = false;

	/** ���� ���ҽ� ���� �������Դϴ�. */
	ma_sound* soundPtr_ = nullptr;
};