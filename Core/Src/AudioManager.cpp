#include <array>

#include <mimalloc.h>
#include <miniaudio.h>

#include "Assertion.h"
#include "AudioManager.h"

std::unique_ptr<ma_engine> audioEngine_ = nullptr;
ma_engine* audioEnginePtr_ = nullptr;

AudioManager AudioManager::instance_;

struct AudioResource
{
	ma_sound sound;
	bool bUsage;
};

static const uint32_t MAX_AUDIO_POOL_SIZE = 30;
static int32_t audioPoolSize_ = 0;
static std::array<AudioResource, MAX_AUDIO_POOL_SIZE> audioPool_;

void* AudioMalloc(size_t sz, void* pUserData)
{
	(void)(pUserData); /** 무시. 사용하지 않음 */
	return mi_malloc(sz);
}

void* AudioRealloc(void* p, size_t sz, void* pUserData)
{
	(void)(pUserData); /** 무시. 사용하지 않음 */
	return mi_realloc(p, sz);
}

void AudioFree(void* p, void* pUserData)
{
	(void)(pUserData); /** 무시. 사용하지 않음 */
	return mi_free(p);
}

AudioManager& AudioManager::GetRef()
{
	return instance_;
}

AudioManager* AudioManager::GetPtr()
{
	return &instance_;
}

void AudioManager::Startup()
{
	audioEngine_ = std::make_unique<ma_engine>();
	audioEnginePtr_ = audioEngine_.get();

	ma_allocation_callbacks allocationCallbacks;
	allocationCallbacks.pUserData = nullptr;
	allocationCallbacks.onMalloc = AudioMalloc;
	allocationCallbacks.onRealloc = AudioRealloc;
	allocationCallbacks.onFree = AudioFree;

	ma_engine_config config;
	ZeroMemory(&config, sizeof(ma_engine_config));

	config.allocationCallbacks = allocationCallbacks;

	ma_result result = ma_engine_init(&config, audioEnginePtr_);
	ASSERT(result == MA_SUCCESS, "Failed to initialize miniaudio engine.");

	audioPoolSize_ = 0;
}

void AudioManager::Shutdown()
{
	for (uint32_t index = 0; index < audioPoolSize_; ++index)
	{
		if (audioPool_[index].bUsage)
		{
			ma_sound_uninit(&audioPool_[index].sound);
			audioPool_[index].bUsage = false;
		}
	}

	audioPoolSize_ = 0;

	ma_engine_uninit(audioEngine_.get());
	audioEngine_.reset();
}

void* AudioManager::CreateSound(const std::string& path)
{
	if (!(0 <= audioPoolSize_ && audioPoolSize_ < MAX_AUDIO_POOL_SIZE))
	{
		return nullptr;
	}

	int32_t soundID = -1;
	for (uint32_t index = 0; index < audioPoolSize_; ++index)
	{
		if (!audioPool_[index].bUsage)
		{
			soundID = static_cast<int32_t>(index);
			break;
		}
	}

	if (soundID == -1)
	{
		soundID = audioPoolSize_++;
	}

	audioPool_[soundID].bUsage = true;

	ma_sound* sound = &audioPool_[soundID].sound;
	ma_result result = ma_sound_init_from_file(audioEnginePtr_, path.c_str(), 0, nullptr, nullptr, sound);
	
	if (result != MA_SUCCESS)
	{
		audioPool_[soundID].bUsage = false;
		sound = nullptr;
	}
	
	return reinterpret_cast<void*>(sound);
}

void AudioManager::DestroySound(void* sound)
{
	ASSERT(sound != nullptr, "Invalid sound resource pointer.");

	int32_t soundID = -1;
	for (uint32_t index = 0; index < audioPoolSize_; ++index)
	{
		if (sound == &audioPool_[index].sound)
		{
			soundID = static_cast<int32_t>(index);
			break;
		}
	}

	if ((0 <= soundID && soundID < MAX_AUDIO_POOL_SIZE) && audioPool_[soundID].bUsage)
	{
		ma_sound_uninit(&audioPool_[soundID].sound);
		audioPool_[soundID].bUsage = false;
	}
}
