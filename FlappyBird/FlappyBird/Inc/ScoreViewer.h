#pragma once

#include <array>

#include "Vec2.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ���ھ ǥ���ϴ� ��ƼƼ�Դϴ�.
 */
class ScoreViewer : public IEntity
{
public:
	/**
	 * @brief ���ھ ǥ���ϴ� ��ƼƼ�� �������Դϴ�.
	 */
	explicit ScoreViewer();


	/**
	 * @brief ���ھ ǥ���ϴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ScoreViewer();


	/**
	 * @brief ���ھ ǥ���ϴ� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ScoreViewer);


	/**
	 * @brief ���ھ ǥ���ϴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���ھ ǥ���ϴ� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���ھ ǥ���ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �� ��ƼƼ�� ID ���� �����մϴ�.
	 * 
	 * @param birdID �� ��ƼƼ�� ID ���Դϴ�.
	 */
	void SetBirdID(const EUID& birdID) { birdID_ = birdID; }


private:
	/**
	 * @brief ���ھ ǥ���� �� ����� ���� �ؽ�ó�Դϴ�.
	 */
	std::array<RUID, 10> numberIDs_;


	/**
	 * @brief ���ھ ǥ���� �� ������ �� ��ƼƼ�� ID ���Դϴ�.
	 */
	EUID birdID_ = -1;


	/**
	 * @brief ���ھ��� �߽� ��ġ�Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief ���� �ϳ��� ���� ũ���Դϴ�.
	 */
	float numberWidth_ = 0.0f;


	/**
	 * @brief ���� �ϳ��� ���� ũ���Դϴ�.
	 */
	float numberHeight_ = 0.0f;


	/**
	 * @brief ���� ���� ���� ũ���Դϴ�.
	 */
	float numberGap_ = 0.0f;


	/**
	 * @brief ���ھ� ĳ�� ���Դϴ�.
	 */
	int32_t scoreCache_ = -1;

	
	/**
	 * @brief ���� �迭�Դϴ�.
	 */
	std::vector<int32_t> number_;
};