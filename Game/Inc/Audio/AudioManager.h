#pragma once

#include <array>
#include <memory>
#include <string>

#include <miniaudio.h>

#include "Audio/Sound.h"
#include "Utils/Macro.h"

/** 
 * 오디오 엔진 초기화/해제 및 사운드 리소스를 관리하는 매니저입니다. 
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class AudioManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(AudioManager);

	/** 오디오 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static AudioManager& GetRef();

	/** 오디오 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static AudioManager* GetPtr();

	/** 사운드를 생성합니다. */
	template <typename TSound, typename... Args>
	TSound* Create(Args&&... args)
	{
		if (!(0 <= soundSize_ && soundSize_ < MAX_SOUND_SIZE))
		{
			return nullptr;
		}

		int32_t soundID = -1;
		for (uint32_t index = 0; index < soundSize_; ++index)
		{
			if (!sounds_[index] && !usages_[index])
			{
				soundID = static_cast<int32_t>(index);
				break;
			}
		}

		if (soundID == -1)
		{
			soundID = soundSize_++;
		}

		usages_[soundID] = true;
		sounds_[soundID] = std::make_unique<TSound>(args...);

		return reinterpret_cast<TSound*>(sounds_[soundID].get());
	}

	/** 사운드를 파괴합니다. */
	void Destroy(const Sound* sound);

private:
	/** GameApp에서 AudioManager의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 오디오 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	AudioManager() = default;
	virtual ~AudioManager() {}

	/** 오디오 매니저의 초기화/해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** 오디오 매니저의 싱글턴 객체입니다. */
	static AudioManager singleton_;

	/** 오디오 엔진입니다. */
	std::unique_ptr<ma_engine> audioEngine_ = nullptr;

	/** 오디오 매니저에서 관리하는 사운드의 최대 개수입니다. */
	static const uint32_t MAX_SOUND_SIZE = 50;

	/** 사운드 매니저의 크기입니다. 최대 MAX_SOUND_SIZE개 까지 지원합니다. */
	uint32_t soundSize_ = 0;

	/** 오디오 매니저 내에서 관리하는 사운드와 그 사운드의 사용 여부입니다. */
	std::array<std::unique_ptr<Sound>, MAX_SOUND_SIZE> sounds_;
	std::array<bool, MAX_SOUND_SIZE> usages_;
};