#pragma once

#include <string>
#include <vector>

#include "IObject.h"

class TTFont; // Ʈ�� Ÿ�� ��Ʈ ���ҽ��� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�Դϴ�.
 */
class PlayLogger : public IObject
{
public:
	/**
	 * @brief �÷��� �α��Դϴ�.
	 */
	struct PlayLog
	{
		std::string day;
		float time;
	};


public:
	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	PlayLogger() = default;


	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PlayLogger();


	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayLogger);


	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	void Render();


	/**
	 * @brief �÷��� �α׸� �����ϴ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �÷��� �α׸� ����մϴ�.
	 * 
	 * @param day �÷��� ��¥�Դϴ�.
	 * @param time �÷��� �ð��Դϴ�.
	 */
	void RecordPlayLog(const std::wstring& day, const float& time);


private:
	/**
	 * @brief �÷��� �α��� ���ڿ� �ִ� �����Դϴ�.
	 */
	static const int32_t MAX_LOG_SIZE = 20;


	/**
	 * @brief �÷��� �α� ûũ�Դϴ�.
	 *
	 * @note �� ����ü�� ������ �а� �� �� ����մϴ�.
	 */
	struct PlayLogChunk
	{
		char day[MAX_LOG_SIZE];
		float time;
	};


	/**
	 * @brief �α� ������ �н��ϴ�.
	 */
	void ReadLogFile();


	/**
	 * @brief �α� ������ ���ϴ�.
	 */
	void WriteLogFile();


private:
	/**
	 * @brief �α� ���� ����Դϴ�.
	 */
	std::wstring logFilePath_;


	/**
	 * @brief �÷��� �ΰŰ� ���� ���� ����Դϴ�.
	 */
	std::vector<PlayLog> playLog_;
};