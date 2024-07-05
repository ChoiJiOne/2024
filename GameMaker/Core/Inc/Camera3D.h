#pragma once

#include "GameMath.h"
#include "IEntity.h"


namespace GameMaker
{
/**
 * @brief 3D ī�޶� ��ƼƼ�� �������̽��Դϴ�.
 */
class Camera3D : public IEntity
{
public:
	/**
	 * @brief 3D ī�޶��� �⺻ �������Դϴ�.
	 */
	Camera3D() = default;


	/**
	 * @brief ī�޶� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Camera3D() {}


	/**
	 * @brief 3D ī�޶��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Camera3D);


	/**
	 * @brief ī�޶� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;


	/**
	 * @brief ī�޶� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() = 0;

	
	/**
	 * @brief ī�޶��� ���� �� ��ġ�� ����ϴ�.
	 * 
	 * @return ī�޶��� ���� �� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vec3f& GetPosition() const { return position_; }


	/**
	 * @brief ī�޶��� ������ ����ϴ�.
	 * 
	 * @return ī�޶��� ������ ��ȯ�մϴ�.
	 */
	const Vec3f& GetDirection() const { return direction_; }


	/**
	 * @brief ī�޶��� �� ������ ����ϴ�.
	 * 
	 * @return ī�޶��� �� ������ ��ȯ�մϴ�.
	 */
	const Vec3f& GetUpDirection() const { return upDirection_; }


	/**
	 * @brief ī�޶��� ������ ������ ����ϴ�.
	 * 
	 * @return ī�޶��� ������ ������ ��ȯ�մϴ�.
	 */
	const Vec3f& GetRightDirection() const { return rightDirection_; }
	

	/**
	 * @brief ���� ���� ī�޶� �� ������ ����ϴ�.
	 * 
	 * @return ���� ���� ī�޶� �� ������ ��ȯ�մϴ�.
	 */
	const Vec3f& GetWorldupDirection() const { return worldUpDirection_; }


	/**
	 * @breif ����� ���� �ʵ� ����(����)�� ����ϴ�.
	 * 
	 * @return ����� ���� �ʵ� ����(����)�� ��ȯ�մϴ�.
	 */
	const float& GetFov() const { return fov_; }


	/**
	 * @brief �� ���� X:Y�� ���� ���� ������ ����ϴ�.
	 * 
	 * @return �� ���� X:Y�� ���� ���� ������ ��ȯ�մϴ�.
	 */
	const float& GetAspectRatio() const { return aspectRatio_; }


	/**
	 * @brief ����� Ŭ���� �������� �Ÿ��� ����ϴ�.
	 * 
	 * @return ����� Ŭ���� �������� �Ÿ��� ��ȯ�մϴ�.
	 */
	const float& GetNearZ() const { return nearZ_; }


	/**
	 * @brief ���Ÿ� Ŭ���� �������� �Ÿ��� ����ϴ�.
	 * 
	 * @return ���Ÿ� Ŭ���� �������� �Ÿ��� ��ȯ�մϴ�.
	 */
	const float& GetFarZ() const { return farZ_; }


	/**
	 * @brief ī�޶��� �� ����� ����ϴ�.
	 * 
	 * @return ī�޶��� �� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetView() const { return view_; }


	/**
	 * @brief ī�޶��� ���� ����� ����ϴ�.
	 *
	 * @return ī�޶��� ���� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetProjection() const { return projection_; }


protected:
	/**
	 * @brief ī�޶��� ���� �� ��ġ�Դϴ�.
	 */
	Vec3f position_;


	/**
	 * @brief ī�޶��� �����Դϴ�.
	 */
	Vec3f direction_;


	/**
	 * @brief ī�޶��� �� �����Դϴ�.
	 */
	Vec3f upDirection_;


	/**
	 * @brief ī�޶��� ������ �����Դϴ�.
	 */
	Vec3f rightDirection_;


	/**
	 * @brief ���� ���� ī�޶� �� �����Դϴ�.
	 */
	Vec3f worldUpDirection_ = Vec3f(0.0f, 1.0f, 0.0f);


	/**
	 * @brief ����� ���� �ʵ� ����(����)�Դϴ�.
	 */
	float fov_ = 0.0f;


	/**
	 * @brief �� ���� X:Y�� ���� ���� �����Դϴ�.
	 */
	float aspectRatio_ = 0.0f;


	/**
	 * @brief ����� Ŭ���� �������� �Ÿ��Դϴ�. 0���� Ŀ�� �մϴ�.
	 */
	float nearZ_ = 0.0f;


	/**
	 * @brief ���Ÿ� Ŭ���� �������� �Ÿ��Դϴ�. 0���� Ŀ�� �մϴ�.
	 */
	float farZ_ = 0.0f;


	/**
	 * @brief �� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief ���� ����Դϴ�.
	 */
	Mat4x4 projection_;
};

}