#pragma once

#include <array>
#include <memory>

#include "Macro.h"

/** ����� �Ŵ����� �̱����Դϴ�. */
class AudioManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(AudioManager);

	static AudioManager& Get();

private:
	friend class IApp;

	AudioManager() = default;
	virtual ~AudioManager() {}

	void Startup(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */
	void Shutdown(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */
};