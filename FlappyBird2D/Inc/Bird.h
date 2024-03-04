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
		Done  = 0x03,
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
	 * @brief ������ ��Ʈ�ѷ� ID�� �����մϴ�.
	 * 
	 * @param pipeControllerID ������ ������ ��Ʈ�ѷ� ID�Դϴ�.
	 */
	void SetPipeControllerID(const EUID& pipeControllerID) { pipeControllerID_ = pipeControllerID; }


	/**
	 * @brief �ٴ� ID�� �����մϴ�.
	 * 
	 * @param landID ������ �ٴ� ID�Դϴ�.
	 */
	void SetLandID(const EUID& landID) { landID_ = landID; }


	/**
	 * @brief ��׶��� ID�� �����մϴ�.
	 * 
	 * @param backgroundID ������ ��׶��� ID�Դϴ�.
	 */
	void SetBackgroundID(const EUID& backgroundID) { backgroundID_ = backgroundID; }


	/**
	 * @brief ���� ���ھ ����ϴ�.
	 * 
	 * @return ���� ���ھ ��ȯ�մϴ�.
	 */
	int32_t GetScore() const { return score_; }


	/**
	 * @brief ���� ���� ��ġ�� �����մϴ�.
	 * 
	 * @param startLocation ������ ���� ��ġ�Դϴ�.
	 */
	static void SetStartLocation(const Vec2f& startLocation) { startLocation_ = startLocation; }


private:
	/**
	 * @brief ���� Ready ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void TickReadyStatus(float deltaSeconds);


	/**
	 * @brief ���� Fly ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void TickFlyStatus(float deltaSeconds);


	/**
	 * @brief ���� Dead ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void TickDeadStatus(float deltaSeconds);


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
	 * @brief ���� �ּ� ȸ�� �����Դϴ�.
	 */
	float minRotate_ = 0.0f;


	/**
	 * @brief ���� �ִ� ȸ�� �����Դϴ�.
	 */
	float maxRotate_ = 0.0f;


	/**
	 * @brief ���� ȸ�� �����Դϴ�.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief ���� �ִ� �ӵ��Դϴ�.
	 */
	float maxSpeed_ = 0.0f;


	/**
	 * @brief ���� ���� �ӵ��Դϴ�.
	 */
	float currentSpeed_ = 0.0f;


	/**
	 * @brief ���� ���� �ӵ��Դϴ�.
	 */
	float dampingSpeed_ = 0.0f;


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
	 * @brief ���� ���ھ��Դϴ�.
	 */
	int32_t score_ = 0;


	/**
	 * @brief ������ ��Ʈ�ѷ��� ID�Դϴ�.
	 */
	EUID pipeControllerID_ = -1;


	/**
	 * @brief �ٴ��� ID �Դϴ�.
	 */
	EUID landID_ = -1;


	/**
	 * @brief ��׶����� ID�Դϴ�.
	 */
	EUID backgroundID_ = -1;
	

	/**
	 * @brief ���� ���� ��ġ�Դϴ�.
	 */
	static Vec2f startLocation_;
};