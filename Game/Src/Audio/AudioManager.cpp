#include "Audio/AudioManager.h"
#include "Utils/Assertion.h"
#include "Utils/MemoryAlloc.h"

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
}

void AudioManager::Shutdown()
{
}
