#pragma once

#include "BoundBox2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ������ ��ƼƼ�Դϴ�.
 */
class Pipe : public IEntity
{
public:
	/**
	 * @brief �������� ���¸� ��Ÿ���� �������Դϴ�.
	 */
	enum class EStatus : int32_t
	{
		Wait   = 0x00, // ��� �����Դϴ�.
		Active = 0x01, // �����̰� �ִ� �����Դϴ�.
	};


public:
	/**
	 * @brief ������ ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param speed �������� ������ �ӵ��Դϴ�.
	 */
	explicit Pipe(float speed);


	/**
	 * @brief ������ ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Pipe();


	/**
	 * @brief ������ ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Pipe);


	/**
	 * @brief �������� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �������� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �������� ������ �� �ִ��� Ȯ���մϴ�.
	 *
	 * @return �������� ������ �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CanMove() const { return bCanMove_; }


	/**
	 * @brief �������� ������ ���θ� �����մϴ�.
	 *
	 * @param bCanMove ������ ������ ������ �����Դϴ�.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief �������� ���¸� ����ϴ�.
	 * 
	 * @return �������� ���°��� ��ȯ�մϴ�.
	 */
	EStatus GetStatus() const { return status_; }


	/**
	 * @brief �������� ���¸� �����մϴ�.
	 * 
	 * @param status �������� ���¸� �����մϴ�.
	 */
	void SetStatus(const EStatus& status) { status_ = status; }


	/**
	 * @brief �������� ��ġ�� �缳���մϴ�.
	 */
	void ResetLocation();


	/**
	 * @brief �ٸ� ���������� ������ ����ϴ�.
	 */
	float GetGapPipe(const Pipe* pipe);


	/**
	 * @brief �������� ��� ��� ������ ����ϴ�.
	 * 
	 * @return �������� ��� ��� ���� �����͸� ��ȯ�մϴ�.
	 */
	const IBound2D* GetTopBound() const { return &topBound_; }


	/**
	 * @brief �������� �ϴ� ��� ������ ����ϴ�.
	 * 
	 * @return �������� �ϴ� ��� ���� �����͸� ��ȯ�մϴ�.
	 */
	const IBound2D* GetBottomBound() const { return &bottomBound_; }


	/**
	 * @brief �������� ���� ��ġ�� �����մϴ�.
	 * 
	 * @param startLocation ������ �������� ���� ��ġ�Դϴ�.
	 */
	static void SetStartLocation(const Vec2f& startLocation) { startLocation_ = startLocation; }


	/**
	 * @brief �������� �� ��ġ�� �����մϴ�.
	 * 
	 * @param endLocation ������ �������� �� ��ġ�Դϴ�.
	 */
	static void SetEndLocation(const Vec2f& endLocation) { endLocation_ = endLocation; }
	

private:
	/**
	 * @brief �������� ������ �� �ִ��� Ȯ���մϴ�.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief �������� ������ �ӵ��Դϴ�.
	 */
	float speed_ = 0.0f;


	/**
	 * @brief ���� �������� �����Դϴ�.
	 */
	EStatus status_ = EStatus::Wait;


	/**
	 * @brief ��� �������� ��� �����Դϴ�.
	 */
	BoundBox2D topBound_;


	/**
	 * @brief �ϴ� �������� ��� �����Դϴ�.
	 */
	BoundBox2D bottomBound_;


	/**
	 * @brief �������� �ؽ�ó ���ҽ��Դϴ�.
	 */
	RUID textureID_ = -1;

	
	/**
	 * @brief �������� ���� ��ġ�Դϴ�.
	 */
	static Vec2f startLocation_;


	/**
	 * @brief �������� �� ��ġ�Դϴ�.
	 */
	static Vec2f endLocation_;
};