#pragma once

#include "IEntity.h"

class GeometryRenderer3D;


/**
 * @brief ���� ���� ���� ��ƼƼ�Դϴ�.
 */
class Grid : public IEntity
{
public:
	/**
	 * @brief ����(Grid) ��ƼƼ�� �������Դϴ�.
	 *
	 * @param renderer ���� �������� �� ������ �������Դϴ�.
	 */
	Grid(GeometryRenderer3D* renderer);


	/**
	 * @brief ����(Grid) ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Grid();


	/**
	 * @brief ����(Grid) ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Grid);


	/**
	 * @brief ����(Grid) ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ����(Grid) ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ����(Grid) ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ���ڸ� �׸� �� ������ �������Դϴ�.
	 */
	GeometryRenderer3D* renderer_ = nullptr;


	/**
	 * @brief ������ ũ���Դϴ�.
	 */
	Vec3f size_ = Vec3f(1.0f, 1.0f, 1.0f);


	/**
	 * @brief ������ �����Դϴ�.
	 */
	float stride_ = 1.0f;
};