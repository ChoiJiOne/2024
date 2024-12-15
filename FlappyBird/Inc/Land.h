#pragma once

#include "BoundBox2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief �� ��ƼƼ�Դϴ�.
 */
class Land : public IEntity
{
public:
	/**
	 * @brief �� ��ƼƼ�� �������Դϴ�.
	 *
	 * @param scrollSpeed ���� ��ũ�� �ӵ��Դϴ�.
	 */
	explicit Land(float scrollSpeed);


	/**
	 * @brief �� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Land();


	/**
	 * @brief �� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Land);


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
	 * @brief �� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ������ �� �ִ��� Ȯ���մϴ�.
	 *
	 * @return ���� ������ �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CanMove() const { return bCanMove_; }


	/**
	 * @brief ���� ������ ���θ� �����մϴ�.
	 *
	 * @param bCanMove ������ �� ������ �����Դϴ�.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief ���� ��� ���� �����͸� ����ϴ�.
	 * 
	 * @return ���� ��� ���� ������ ���� ��ȯ�մϴ�.
	 */
	const IBound2D* GetBound() const { return &bound_; }


private:
	/**
	 * @brief ���� ������ �� �ִ��� Ȯ���մϴ�.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief ���� ��� �����Դϴ�.
	 */
	BoundBox2D bound_;


	/**
	 * @brief ���� ��ũ�� ��ġ�Դϴ�.
	 */
	float scrollX_ = 0.0f;


	/**
	 * @brief ���� �ִ� ��ũ�� ��ġ�Դϴ�.
	 */
	float maxScrollX_ = 0.0f;


	/**
	 * @brief ���� ��ũ�� �ӵ��Դϴ�.
	 * 
	 * @note �ӵ��� ������ �ȼ�/�� �Դϴ�.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief ���� �ؽ�ó ���ҽ��Դϴ�.
	 */
	RUID textureID_ = -1;
};