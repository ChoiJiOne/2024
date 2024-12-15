#pragma once

#include <vector>

#include "Panel.h"


/**
 * @brief ���� Ÿ��Ʋ ��ƼƼ�Դϴ�.
 */
class MainTitle : public Panel
{
public:
	/**
	 * @brief ���� Ÿ��Ʋ�� �������Դϴ�.
	 * 
	 * @param fontID ���� Ÿ��Ʋ�� ��Ʈ ���ҽ� ID�Դϴ�.
	 */
	explicit MainTitle(const RUID& fontID);

	
	/**
	 * @brief ���� Ÿ��Ʋ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~MainTitle();


	/**
	 * @brief ���� Ÿ��Ʋ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MainTitle);


	/**
	 * @brief ���� Ÿ��Ʋ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� Ÿ��Ʋ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���� Ÿ��Ʋ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;
	

private:
	/**
	 * @brief ���� Ÿ��Ʋ�� ���� ���� ����Դϴ�.
	 */
	std::vector<Vec4f> colors_;


	/**
	 * @brief ���� ��ġ�Դϴ�.
	 */
	Vec2f birdPosition_;


	/**
	 * @brief ���� ���� ũ���Դϴ�.
	 */
	float birdWidth_ = 0.0f;


	/**
	 * @brief ���� ���� ũ���Դϴ�.
	 */
	float birdHeight_ = 0.0f;


	/**
	 * @brief ���� ������ �ð��Դϴ�.
	 */
	float flyTime_ = 0.09f;


	/**
	 * @brief ���� �������� ���� ���� �ð��Դϴ�.
	 */
	float accumulateFlyTime_ = 0.0f;


	/**
	 * @brief ���� �� ���ҽ� �ε����Դϴ�.
	 */
	std::size_t birdIndex_ = 0;


	/**
	 * @brief ���� Ÿ��Ʋ���� ����� �� ���ҽ� ����Դϴ�.
	 */
	std::vector<RUID> birds_;


	/**
	 * @brief �ؽ�Ʈ �׸��� ȿ���� ���� ���̾�Դϴ�.
	 */
	float bias_ = 5.0f;


	/**
	 * @brief ��ü ���� �ð����Դϴ�.
	 */
	float accumulateTime_ = 0.0f;


	/**
	 * @brief ���� �ð����Դϴ�.
	 */
	float updateAccumulateTime_ = 0.0f;


	/**
	 * @brief �ִ� ���� �ð����Դϴ�.
	 */
	float maxAccumulateTime_ = 1.0f;
};