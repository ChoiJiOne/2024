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
	ma_engine_uninit(gAudioEnginePtr);
	audioEngine_.reset();
	gAudioEnginePtr = nullptr;
}