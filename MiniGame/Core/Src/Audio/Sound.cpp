#include <glm/glm.hpp>

#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Utils/Assertion.h"

extern ma_engine* gAudioEnginePtr;

Sound::Sound(const std::string& path)
{
	ma_result result = ma_sound_init_from_file(gAudioEnginePtr, path.c_str(), 0, nullptr, nullptr, &sound_);
	ASSERTION(result == MA_SUCCESS, "Failed to load %s sound file.", path.c_str());

	bIsInitialized_ = true;
}

Sound::~Sound()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Sound::Release()
{
	CHECK(bIsInitialized_);

	ma_sound_uninit(&sound_);

	bIsInitialized_ = false;
}

void Sound::SetVolume(float volume)
{
	volume = glm::clamp<float>(volume, 0.0f, 1.0f);
	ma_sound_set_volume(&sound_, volume);
}

float Sound::GetVolume()
{
	return ma_sound_get_volume(&sound_);
}

void Sound::SetLooping(bool bIsLoop)
{
	ma_sound_set_looping(&sound_, static_cast<ma_bool32>(bIsLoop));
}

bool Sound::IsLooping()
{
	return ma_sound_is_looping(&sound_) == MA_TRUE;
}

void Sound::Start()
{
	ma_sound_seek_to_pcm_frame(&sound_, 0);
	ma_sound_start(&sound_);
}

void Sound::Play()
{
	ma_sound_start(&sound_);
}

bool Sound::IsPlaying()
{
	return ma_sound_is_playing(&sound_) == MA_TRUE;
}

bool Sound::IsDone()
{
	return ma_sound_at_end(&sound_) == MA_TRUE;
}

void Sound::Stop()
{
	ma_sound_stop(&sound_);
}

bool Sound::IsStopping()
{
	return ma_sound_at_end(&sound_) != MA_TRUE && ma_sound_is_playing(&sound_) != MA_TRUE;
}

void Sound::Reset()
{
	ma_sound_seek_to_pcm_frame(&sound_, 0);
}