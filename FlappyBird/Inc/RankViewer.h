#pragma once

#include "Vec2.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ�Դϴ�.
 */
class RankViewer : public IEntity
{
public:
	/**
	 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param fontID �ؽ�Ʈ�� �������� �� ������ ��Ʈ ID�Դϴ�.
	 */
	explicit RankViewer(const RUID& fontID);


	/**
	 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~RankViewer();


	/**
	 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(RankViewer);


	/**
	 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ��ŷ�� ǥ���ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief GameOver �ؽ�ó�Դϴ�.
	 */
	RUID gameOverID_ = -1;


	/**
	 * @brief GameOver �ؽ�ó�� ��ġ�Դϴ�.
	 */
	Vec2f gameOverLocation_;


	/**
	 * @brief GameOver �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float gameOverWidth_ = 0.0f;


	/**
	 * @brief GameOver �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float gameOverHeight_ = 0.0f;
	

	/**
	 * @brief ���� �ð����Դϴ�.
	 */
	float accumulateTime_ = 0.0f;


	/**
	 * @brief �ؽ�Ʈ ǥ�ÿ� ����� ��Ʈ ���ҽ��Դϴ�.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief ���� �����Դϴ�.
	 */
	std::wstring currentLevel_;


	/**
	 * @brief ���� ������ ǥ���� ��ġ�Դϴ�.
	 */
	Vec2f currentLevelLocation_;


	/**
	 * @brief ���� ���ھ��Դϴ�.
	 */
	std::wstring currentScore_;


	/**
	 * @brief ���� ���ھ ǥ���� ��ġ�Դϴ�.
	 */
	Vec2f currentScoreLocation_;


	/**
	 * @brief �ְ� ���ھ��Դϴ�.
	 */
	std::wstring bestScore_;


	/**
	 * @brief �ְ� ���ھ ǥ���� ��ġ�Դϴ�.
	 */
	Vec2f bestScoreLocation_;


	/**
	 * @brief �ְ� ����� ���ŵǾ����� Ȯ���մϴ�.
	 */
	bool bIsUpdateBest_ = false;
};