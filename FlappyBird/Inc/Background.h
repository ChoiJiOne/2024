#pragma once

#include "BoundBox2D.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ��׶��� ��ƼƼ�Դϴ�.
 */
class Background : public IEntity
{
public:
	/**
	 * @brief ��׶��� ��ƼƼ�� �������Դϴ�.
	 */
	explicit Background();


	/**
	 * @brief ��׶��� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param scrollSpeed ��׶����� ��ũ�� �ӵ��Դϴ�.
	 */
	explicit Background(float scrollSpeed);


	/**
	 * @brief ��׶��� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Background();


	/**
	 * @brief ��׶��� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief ��׶��带 ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ��׶��带 ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ��׶��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ��׶��尡 ������ �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return ��׶��尡 ������ �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CanMove() const { return bCanMove_; }


	/**
	 * @brief ��׶����� ������ ���θ� �����մϴ�.
	 * 
	 * @param bCanMove ������ ��׶��� ������ �����Դϴ�.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief ��׶����� ��� ������ ����ϴ�.
	 * 
	 * @return ��׶����� ��� ���� �����͸� ��ȯ�մϴ�.
	 */
	const IBound2D* GetBound() const { return &bound_; }


private:
	/**
	 * @brief ��׶��尡 ������ �� �ִ��� Ȯ���մϴ�.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief ��׶����� ��ũ�� ��ġ�Դϴ�.
	 */
	float scrollX_ = 0.0f;


	/**
	 * @brief ��׶����� �ִ� ��ũ�� ��ġ�Դϴ�.
	 */
	float maxScrollX_ = 0.0f;


	/**
	 * @brief ��׶����� ��ũ�� �ӵ��Դϴ�.
	 * 
	 * @note �ӵ��� ������ �ȼ�/�� �Դϴ�.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief ��׶��� �ؽ�ó ���ҽ��� ID�Դϴ�.
	 */
	RUID textureID_ = -1;


	/**
	 * @brief ��׶����� ��� �����Դϴ�.
	 */
	BoundBox2D bound_;
};