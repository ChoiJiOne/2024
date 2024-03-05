#pragma once

#include <map>

#include "IManager.h"
#include "IResource.h"


/**
 * @brief ��ü ������ �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ConfigManager : public IManager
{
public:
	/**
	 * @brief ������ ��׶��� �����Դϴ�.
	 */
	enum class EBackground : int32_t
	{
		Day   = 0x00,
		Night = 0x01,
	};


	/**
	 * @brief ������ �����Դϴ�.
	 */
	enum class ELevel : int32_t
	{
		Easy   = 0x00,
		Normal = 0x01,
		Hard   = 0x02,
	};


	/**
	 * @brief �� �����Դϴ�.
	 */
	enum class EBird : int32_t
	{
		Blue   = 0x01,
		Red    = 0x02,
		Yellow = 0x03,
	};


public:
	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ConfigManager);


	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return ��ü ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static ConfigManager& Get();


	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���θ� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� ��� ���ҽ��� ID ���� ����ϴ�.
	 * 
	 * @return ���� ��� ���ҽ��� ID ���� ��ȯ�մϴ�.
	 */
	RUID GetCurrentBackgroundID() const { return currentBackgroundID_; }


	/**
	 * @brief ���� ����� �����մϴ�.
	 * 
	 * @param background ������ ��׶����Դϴ�.
	 */
	void SetCurrentBackgroundID(const EBackground& background);


	/**
	 * @brief ���� ���� ���̵��� ����ϴ�.
	 * 
	 * @return ���� ���� ���̵��� ��ȯ�մϴ�.
	 */
	ELevel GetCurrentLevel() const { return currentLevel_; }


	/**
	 * @brief ���� ���� ���̵��� �����մϴ�.
	 * 
	 * @param level ������ ���� ���̵��Դϴ�.
	 */
	void SetCurrentLevel(const ELevel& level);


	/**
	 * @brief ���� ���� ����ϴ�.
	 * 
	 * @return ���� ���� ��ȯ�մϴ�.
	 */
	EBird GetCurrentBird() const { return currentBird_; }


	/**
	 * @brief ���� ���� �����մϴ�.
	 * 
	 * @param brid ������ ���Դϴ�.
	 */
	void SetCurrentBird(const EBird& bird);


	/**
	 * @brief ������ ����մϴ�.
	 * 
	 * @param score ����� �����Դϴ�.
	 */
	void RecordScore(int32_t score);


	/**
	 * @brief ���� ������ �ֱ� ������ ����ϴ�.
	 * 
	 * @return ���� ������ �ֱ� ������ ��ȯ�մϴ�.
	 */
	int32_t GetRecentScore();


private:
	/**
	 * @brief ��ü ������ �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ConfigManager);


private:
	/**
	 * @brief ���� ��� ���ҽ��� ID ���Դϴ�.
	 */
	RUID currentBackgroundID_ = -1;

	
	/**
	 * @brief �� ��� ���ҽ��� ID ���Դϴ�.
	 */
	RUID dayBackgroundID_ = -1;


	/**
	 * @brief �� ��� ���ҽ��� ID ���Դϴ�.
	 */
	RUID nightBackgroundID_ = -1;


	/**
	 * @brief ���� ���� ���̵��Դϴ�.
	 */
	ELevel currentLevel_ = ELevel::Easy;


	/**
	 * @brief ���� �� �����Դϴ�.
	 */
	EBird currentBird_ = EBird::Yellow;


	/**
	 * @brief �ֱ� ��ϵ� ������ ���� ���ھ��Դϴ�.
	 */
	std::map<ELevel, int32_t> recentScore_;
};