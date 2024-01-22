#pragma once

#include <string>
#include <vector>

#include "IObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // Ʈ�� Ÿ�� ��Ʈ ���ҽ��� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief �÷��� �α׸� �����ϴ� ������Ʈ�Դϴ�.
 */
class PlayLogger : public IObject
{
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
	static const int32_t MAX_LOG_SIZE = 40;


	/**
	 * @brief �÷��� �α��Դϴ�.
	 */
	struct PlayLog
	{
		std::wstring day;
		float time;
	};


	/**
	 * @brief �÷��� �α� ûũ�Դϴ�.
	 *
	 * @note �� ����ü�� ������ �а� �� �� ����մϴ�.
	 */
	struct PlayLogChunk
	{
		wchar_t day[MAX_LOG_SIZE];
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


	/**
	 * @brief �ֱٿ� ��ϵ� ����Դϴ�.
	 */
	PlayLog recentPlayLog;


	/**
	 * @brief �÷��� �ΰŰ� ǥ���� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief �÷��� �ΰŰ� ǥ���� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font64_ = nullptr;


	/**
	 * @brief ��ũ Ÿ��Ʋ ��ġ�Դϴ�.
	 */
	Vector2f rankCenter_;


	/**
	 * @brief ��ũ Ÿ��Ʋ �����Դϴ�.
	 */
	Vector4f rankColor_;


	/**
	 * @brief �α� ���� ��ġ�Դϴ�.
	 */
	Vector2f logCenter_;


	/**
	 * @brief �α� �����Դϴ�.
	 */
	Vector4f logColor_;


	/**
	 * @brief �α��� �ֱ� �����Դϴ�.
	 */
	Vector4f logRecentColor_;


	/**
	 * @brief �α� ���� �����Դϴ�.
	 */
	float logStride_ = 0.0f;


	/**
	 * @brief ȭ�鿡 ǥ���� �ִ� �α� ���Դϴ�.
	 */
	int32_t maxLogCount_ = 0;
};