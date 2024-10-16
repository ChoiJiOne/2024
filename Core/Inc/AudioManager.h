#pragma once

#include <array>
#include <memory>
#include <string>

#include "Macro.h"

/** ����� �Ŵ����� �̱����Դϴ�. */
class AudioManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(AudioManager);

	static AudioManager& GetRef();
	static AudioManager* GetPtr();

private:
	friend class IApp;
	friend class Sound;

	AudioManager() = default;
	virtual ~AudioManager() {}

	void Startup(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */
	void Shutdown(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */

	void* CreateSound(const std::string& path);
	void DestroySound(void* sound);

private:
	static AudioManager instance_;
};