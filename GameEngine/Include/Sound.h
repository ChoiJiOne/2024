#pragma once

#include <memory>
#include <string>

#include "IResource.h"

#include <miniaudio.h>


/**
 * @brief �÷��� ������ ���� ���ҽ��Դϴ�.
 */
class Sound : public IResource
{
public:
	/**
	 * @brief ������ ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Sound() = default;


	/**
	 * @brief ������ ���� �Ҹ����Դϴ�.
	 * 
	 * @note ���� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Sound();


	/**
	 * @brief ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sound);


	/**
	 * @brief ���� ������ �ε��ϰ� �ʱ�ȭ�մϴ�.
	 * 
	 * @param path ���� ������ ����Դϴ�.
	 */
	void Initialize(const std::wstring& path);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ ũ�⸦ �����մϴ�.
	 *
	 * @param volume ������ ũ���Դϴ�. ������ 0.0 ~ 1.0 �Դϴ�.
	 */
	void SetVolume(float volume);


	/**
	 * @brief ���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @note ���� ũ���� ������ 0.0 ~ 1.0 �Դϴ�.
	 *
	 * @return ���� ������ ũ�⸦ ����ϴ�.
	 */
	float GetVolume();


	/**
	 * @brief ������ �ݺ� ���θ� �����մϴ�.
	 *
	 * @param bIsLoop ���� �ݺ� �����Դϴ�.
	 */
	void SetLooping(bool bIsLoop);


	/**
	 * @brief ������ �ݺ� ���θ� ����ϴ�.
	 *
	 * @return ���尡 �ݺ��Ѵٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsLooping();


	/**
	 * @brief ���带 �÷����մϴ�.
	 *
	 * @note ������ ������ ���� �ִٸ� ������ �������� �÷��̵˴ϴ�.
	 */
	void Play();


	/**
	 * @brief ���尡 �÷��������� Ȯ���մϴ�.
	 *
	 * @return ���尡 �÷��� ���̶�� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsPlaying();


	/**
	 * @brief ���� �÷��̰� �������� Ȯ���մϴ�.
	 *
	 * @return ���� �÷��̰� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsDone();


	/**
	 * @brief ���� �÷��̸� �����մϴ�.
	 */
	void Stop();


	/**
	 * @brief ���� �÷��̰� ���� �Ǿ����� Ȯ���մϴ�.
	 *
	 * @return ���� �÷��̰� ���� �Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsStopping();


	/**
	 * @brief ���带 �ʱ�ȭ�մϴ�.
	 */
	void Reset();


private:
	/**
	 * @brief miniaudio ���� ���ҽ��Դϴ�.
	 */
	std::unique_ptr<ma_sound> sound_ = nullptr;
};