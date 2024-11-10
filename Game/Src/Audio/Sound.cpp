#include <glm/glm.hpp>

#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Utils/Assertion.h"

extern ma_engine* gAudioEnginePtr;

Sound::Sound(const std::string& path)
{
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

	bIsInitialized_ = false;
}

void Sound::SetVolume(float volume)
{
	volume = glm::clamp<float>(volume, 0.0f, 1.0f);
	ma_sound_set_volume(soundPtr_, volume);
}

float Sound::GetVolume()
{
	return ma_sound_get_volume(soundPtr_);
}

void Sound::SetLooping(bool bIsLoop)
{
	ma_sound_set_looping(soundPtr_, static_cast<ma_bool32>(bIsLoop));
}

bool Sound::IsLooping()
{
	return ma_sound_is_looping(soundPtr_) == MA_TRUE;
}

void Sound::Play()
{
	ma_sound_start(soundPtr_);
}

bool Sound::IsPlaying()
{
	return ma_sound_is_playing(soundPtr_) == MA_TRUE;
}

bool Sound::IsDone()
{
	return ma_sound_at_end(soundPtr_) == MA_TRUE;
}

void Sound::Stop()
{
	ma_sound_stop(soundPtr_);
}

bool Sound::IsStopping()
{
	return ma_sound_at_end(soundPtr_) != MA_TRUE && ma_sound_is_playing(soundPtr_) != MA_TRUE;
}

void Sound::Reset()
{
	ma_sound_seek_to_pcm_frame(soundPtr_, 0);
}