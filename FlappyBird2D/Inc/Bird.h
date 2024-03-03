#pragma once

#include <array>

#include "BoundCircle2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief �� ��ƼƼ�Դϴ�.
 */
class Bird : public IEntity
{
public:
	/**
	 * @brief ���� ���¸� ��Ÿ���� �������Դϴ�.
	 */
	enum class EStatus : int32_t
	{
		Ready = 0x00,
		Fly   = 0x01,
		Dead  = 0x02,
	};


public:
	/**
	 * @brief �� ��ƼƼ�� �������Դϴ�.
	 */
	explicit Bird();


	/**
	 * @brief �� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Bird();


	/**
	 * @brief �� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Bird);


	/**
	 * @brief ���� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �� ��ƼƼ�� ���¸� ����ϴ�.
	 * 
	 * @return �� ��ƼƼ�� ���¸� ��ȯ�մϴ�.
	 */
	EStatus GetStatus() const { return status_; }


	/**
	 * @brief ���� ���� ��ġ�� �����մϴ�.
	 * 
	 * @param startLocation ������ ���� ��ġ�Դϴ�.
	 */
	static void SetStartLocation(const Vec2f& startLocation) { startLocation_ = startLocation; }


private:
	/**
	 * @brief ���� ���� �����Դϴ�.
	 */
	EStatus status_ = EStatus::Ready;


	/**
	 * @brief ���� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ���� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ���� ȸ�� �����Դϴ�.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief ���� �ӵ��Դϴ�.
	 */
	float speed_ = 0.0f;


	/**
	 * @brief ���� ��� �����Դϴ�.
	 */
	BoundCircle2D bound_;


	/**
	 * @brief ���� �ִϸ��̼� �ð��Դϴ�.
	 */
	float animationTime_ = 0.0f;


	/**
	 * @brief ���� �ִ� �ִϸ��̼� �ð��Դϴ�.
	 */
	float maxAnimationTime_ = 0.0f;


	/**
	 * @brief ���� ���� �ؽ�ó ���ҽ� �ε����Դϴ�.
	 */
	std::size_t index_ = 0;


	/**
	 * @brief ���� �ؽ�ó�Դϴ�.
	 */
	std::array<RUID, 4> textureIDs_;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�Դϴ�.
	 */
	RUID infoID_ = -1;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�� ��ġ�Դϴ�.
	 */
	Vec2f infoLocation_;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float infoWidth_ = 0.0f;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float infoHeight_ = 0.0f;


	/**
	 * @brief Get Ready �ؽ�ó�Դϴ�.
	 */
	RUID getReadyID_ = -1;


	/**
	 * @brief Get Ready �ؽ�ó�� ��ġ�Դϴ�.
	 */
	Vec2f getReadyLocation_;


	/**
	 * @brief Get Ready �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float getReadyWidth_ = 0.0f;


	/**
	 * @brief Get Ready �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float getReadyHeight_ = 0.0f;


	/**
	 * @brief ���� ���� ��ġ�Դϴ�.
	 */
	static Vec2f startLocation_;
};