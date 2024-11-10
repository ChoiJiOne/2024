#pragma once

#include <array>
#include <memory>
#include <string>

#include <miniaudio.h>

#include "Audio/Sound.h"
#include "Utils/Macro.h"

/** 
 * ����� ���� �ʱ�ȭ/���� �� ���� ���ҽ��� �����ϴ� �Ŵ����Դϴ�. 
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class AudioManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(AudioManager);

	/** ����� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static AudioManager& GetRef();

	/** ����� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static AudioManager* GetPtr();

	/** ���带 �����մϴ�. */
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

	/** ���带 �ı��մϴ�. */
	void Destroy(const Sound* sound);

private:
	/** GameApp���� AudioManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * ����� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	AudioManager() = default;
	virtual ~AudioManager() {}

	/** ����� �Ŵ����� �ʱ�ȭ/������ GameApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

private:
	/** ����� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static AudioManager singleton_;

	/** ����� �����Դϴ�. */
	std::unique_ptr<ma_engine> audioEngine_ = nullptr;

	/** ����� �Ŵ������� �����ϴ� ������ �ִ� �����Դϴ�. */
	static const uint32_t MAX_SOUND_SIZE = 50;

	/** ���� �Ŵ����� ũ���Դϴ�. �ִ� MAX_SOUND_SIZE�� ���� �����մϴ�. */
	uint32_t soundSize_ = 0;

	/** ����� �Ŵ��� ������ �����ϴ� ����� �� ������ ��� �����Դϴ�. */
	std::array<std::unique_ptr<Sound>, MAX_SOUND_SIZE> sounds_;
	std::array<bool, MAX_SOUND_SIZE> usages_;
};