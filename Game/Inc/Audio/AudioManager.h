#pragma once

#include <array>
#include <map>
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
			if (!sounds_[index].first && !sounds_[index].second)
			{
				soundID = static_cast<int32_t>(index);
				break;
			}
		}

		if (soundID == -1)
		{
			soundID = soundSize_++;
		}

		sounds_[soundID].second = true;
		sounds_[soundID].first = std::make_unique<TSound>(args...);

		return reinterpret_cast<TSound*>(sounds_[soundID].get());
	}

	/** ���带 �ı��մϴ�. */
	void Destroy(const Sound* sound);

	/** ���带 ���� �Ŵ����� ����մϴ�. */
	void Register(const std::string& name, Sound* sound);

	/** ���� �̸��� ��� �Ǿ����� Ȯ���մϴ�. */
	bool IsRegistration(const std::string& name);

	/** ���� �Ŵ����� ����� �����մϴ�. */
	void Unregister(const std::string& name);

	/** �̸��� �����ϴ� ���带 ����ϴ�. */
	template <typename TSound>
	TSound* GetByName(const std::string& name)
	{
		auto it = nameSounds_.find(name);
		if (it == nameSounds_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TSound*>(it->second);
	}

private:
	/** IApp���� ����� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class IApp;

	/**
	 * ����� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	AudioManager() = default;
	virtual ~AudioManager() {}

	/** ����� �Ŵ����� �ʱ�ȭ/������ IApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

private:
	/** ����� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static AudioManager singleton_;

	/** ����� �����Դϴ�. */
	std::unique_ptr<ma_engine> audioEngine_ = nullptr;

	/** ����� �Ŵ������� �����ϴ� ������ �ִ� �����Դϴ�. */
	static const uint32_t MAX_SOUND_SIZE = 10;

	/** ���� �Ŵ����� ũ���Դϴ�. �ִ� MAX_SOUND_SIZE�� ���� �����մϴ�. */
	uint32_t soundSize_ = 0;

	/** ����� �Ŵ��� ������ �����ϴ� ����� �� ������ ��� �����Դϴ�. */
	std::array<std::pair<std::unique_ptr<Sound>, bool>, MAX_SOUND_SIZE> sounds_;

	/** �̸��� ���� �����Դϴ�. */
	std::map<std::string, Sound*> nameSounds_;
};