#pragma once

#include "Mat.h"
#include "Vec.h"

#include "IEntity.h"


/**
 * @brief ����Ʈ ��ƼƼ�Դϴ�.
 *
 * @note �� ����Ʈ�� ��ġ�� ��������, �������Դϴ�.
 */
class Light : public IEntity
{
public:
	/**
	 * @brief ����Ʈ ��ƼƼ�� �������Դϴ�.
	 */
	Light();


	/**
	 * @brief ����Ʈ ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Light();


	/**
	 * @brief ����Ʈ ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Light);


	/**
	 * @brief ����Ʈ ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ����Ʈ ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief ����Ʈ�� ��ġ�� ����ϴ�.
	 *
	 * @return ����Ʈ�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vec3f& GetPosition() const { return position_; }


	/**
	 * @brief ����Ʈ�� ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� ������ ����ϴ�.
	 */
	const Vec3f& GetDirection() const { return direction_; }


	/**
	 * @brief ����Ʈ�� ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� ������ ��ȯ�մϴ�.
	 */
	const Vec3f& GetColor() const { return color_; }


	/**
	 * @brief ����Ʈ�� �� ����� ����ϴ�.
	 *
	 * @return ����Ʈ�� �� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetView() const { return view_; }


	/**
	 * @brief ����Ʈ�� ���� ����� ����ϴ�.
	 *
	 * @return ����Ʈ�� ���� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetProjection() const { return projection_; }


private:
	/**
	 * @brief ����Ʈ�� ��ġ�Դϴ�.
	 */
	Vec3f position_ = Vec3f(0.0f, 0.0f, 0.0f);


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vec3f direction_ = Vec3f(0.0f, 0.0f, 0.0f);


	/**
	 * @brief ����Ʈ�� ���� �� �����Դϴ�.
	 */
	Vec3f worldUp_ = Vec3f(0.0f, 1.0f, 0.0f);


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vec3f color_ = Vec3f(1.0f, 1.0f, 1.0f);


	/**
	 * @brief ����Ʈ�� �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief ����Ʈ�� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;
};