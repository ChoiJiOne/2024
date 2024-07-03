#pragma once

#include <array>
#include <memory>
#include <string>

#include <miniaudio.h>

#include "IManager.h"


namespace GameMaker
{
/**
 * @brief ����� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class AudioManager : public IManager
{
public:
	/**
	 * @brief ����� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(AudioManager);


	/**
	 * @brief ����� �Ŵ����� �����ڸ� ����ϴ�.
	 *
	 * @return ����� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static AudioManager& Get();


	/**
	 * @brief ����� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ����� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ����� ������ �����͸� ����ϴ�.
	 * 
	 * @return ����� ������ �����͸� ��ȯ�մϴ�.
	 */
	ma_engine* GetEngine() { return engine_.get(); }


private:
	/**
	 * @brief ����� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(AudioManager);


private:
	/**
	 * @brief ����� �����Դϴ�.
	 */
	std::unique_ptr<ma_engine> engine_ = nullptr;
};

}