#include <Windows.h>

#include "Audio/AudioManager.h"
#include "Utils/Assertion.h"
#include "Utils/MemoryAlloc.h"

ma_engine* gAudioEnginePtr = nullptr;

AudioManager AudioManager::singleton_;

AudioManager& AudioManager::GetRef()
{
	return singleton_;
}

AudioManager* AudioManager::GetPtr()
{
	return &singleton_;
}

void AudioManager::Destroy(const Sound* sound)
{
	int32_t soundID = -1;
	for (uint32_t index = 0; index < soundSize_; ++index)
	{
		Sound* soundPtr = sounds_[index].first.get();
		if (sound == soundPtr)
		{
			soundID = static_cast<int32_t>(index);
			break;
		}
	}

	if (soundID == -1)
	{
		return; // 해당 사운드는 이미 할당 해제 되었거나, 오디오 매니저에 의해 할당 해제된 사운드 입니다.
	}

	if (sounds_[soundID].first)
	{
		if (sounds_[soundID].first->IsInitialized())
		{
			sounds_[soundID].first->Release();
		}

		sounds_[soundID].first.reset();
		sounds_[soundID].second = false;
	}
}

void AudioManager::Register(const std::string& name, Sound* sound)
{
	auto it = nameSounds_.find(name);
	ASSERTION(it == nameSounds_.end(), "Already register '%s'", name.c_str());

	nameSounds_.insert({ name, sound });
}

bool AudioManager::IsRegistration(const std::string& name)
{
	return nameSounds_.find(name) != nameSounds_.end();
}

void AudioManager::Unregister(const std::string& name)
{
	auto it = nameSounds_.find(name);
	ASSERTION(it != nameSounds_.end(), "Can't find '%s' in AudioManager.", name.c_str());

	nameSounds_.erase(it);
}

void AudioManager::Startup()
{
	audioEngine_ = std::make_unique<ma_engine>();
	gAudioEnginePtr = audioEngine_.get();

	ma_allocation_callbacks allocationCallbacks;
	allocationCallbacks.pUserData = nullptr;
	allocationCallbacks.onMalloc = MemoryAlloc;
	allocationCallbacks.onRealloc = MemoryRealloc;
	allocationCallbacks.onFree = MemoryFree;

	ma_engine_config config;
	ZeroMemory(&config, sizeof(ma_engine_config));

	config.allocationCallbacks = allocationCallbacks;

	ma_result result = ma_engine_init(&config, gAudioEnginePtr);
	ASSERTION(result == MA_SUCCESS, "Failed to initialize miniaudio engine.");
}

void AudioManager::Shutdown()
{
	for (uint32_t index = 0; index < soundSize_; ++index)
	{
		if (sounds_[index].first)
		{
			if (sounds_[index].first->IsInitialized())
			{
				sounds_[index].first->Release();
			}

			sounds_[index].first.reset();
			sounds_[index].second = false;
		}
	}

	ma_engine_uninit(gAudioEnginePtr);
	audioEngine_.reset();
	gAudioEnginePtr = nullptr;
}