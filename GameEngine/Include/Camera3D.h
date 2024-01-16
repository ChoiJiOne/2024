#pragma once

#include "IObject.h"
#include "Matrix4x4.h"
#include "Vector3.h"


/**
 * @brief 3D ī�޶� ������Ʈ�Դϴ�.
 */
class Camera3D : public IObject
{
public:
	/**
	 * @brief 3D ī�޶� ������Ʈ�� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Camera3D() = default;


	/**
	 * @brief 3D ī�޶� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note 3D ī�޶� ������Ʈ�� ���� ���ҽ��� �Ҵ� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Camera3D();


	/**
	 * @brief 3D ī�޶� ������Ʈ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Camera3D);


	/**
	 * @brief 3D ī�޶� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 *
	 * @param eyePosition ī�޶��� ���� �� ��ġ�Դϴ�.
	 * @param eyeDirection ī�޶��� �����Դϴ�.
	 * @param upDirection ī�޶��� �� �����Դϴ�.
	 * @param fovRadians ����� ���� �ʵ� ����(����)�Դϴ�.
	 * @param aspectRatio �� ������ X:Y �����Դϴ�.
	 * @param nearZ ����� Ŭ���� �������� �Ÿ��Դϴ�. 0���� Ŀ�� �մϴ�.
	 * @param farZ ���Ÿ� Ŭ���� �������� �Ÿ��Դϴ�. 0���� Ŀ�� �մϴ�.
	 */
	virtual void Initialize(
		const Vector3f& eyePosition,
		const Vector3f& eyeDirection,
		const Vector3f& upDirection,
		float fovRadians,
		float aspectRatio,
		float nearZ,
		float farZ
	);


	/**
	 * @brief 3D ī�޶� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 3D ī�޶� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;

	
	/**
	 * @brief ī�޶��� ���� �� ��ġ�� ����ϴ�.
	 *
	 * @return ī�޶��� ���� �� ��ġ�� ��ȯ�մϴ�.
	 */
	Vector3f GetEyePosition() { return eyePosition_; }


	/**
	 * @brief ī�޶��� ���� �� ��ġ�� ����ϴ�.
	 *
	 * @return ī�޶��� ���� �� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetEyePosition() const { return eyePosition_; }


	/**
	 * @brief ī�޶� �ٶ󺸰� �ִ� ������ ����ϴ�.
	 *
	 * @return ī�޶� �ٶ󺸰� �ִ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetEyeDirection() { return eyeDirection_; }


	/**
	 * @brief ī�޶� �ٶ󺸰� �ִ� ������ ����ϴ�.
	 *
	 * @return ī�޶� �ٶ󺸰� �ִ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetEyeDirection() const { return eyeDirection_; }


	/**
	 * @brief ī�޶��� �� ������ ����ϴ�.
	 *
	 * @return ī�޶��� �� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetUpDirection() { return upDirection_; }


	/**
	 * @brief ī�޶��� �� ������ ����ϴ�.
	 *
	 * @return ī�޶��� �� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetUpDirection() const { return upDirection_; }


	/**
	 * @brief ����� ���� �ʵ� ����(����) ���� ����ϴ�.
	 *
	 * @return ����� ���� �ʵ� ����(����) ���� ��ȯ�մϴ�.
	 */
	float GetFovRadians() { return fov_; }


	/**
	 * @brief ����� ���� �ʵ� ����(����) ���� ����ϴ�.
	 *
	 * @return ����� ���� �ʵ� ����(����) ���� ��ȯ�մϴ�.
	 */
	const float& GetFovRadians() const { return fov_; }


	/**
	 * @brief �� ���� X:Y�� ���� ���� ���� ���� ����ϴ�.
	 *
	 * @return �� ���� X:Y�� ���� ���� ���� ���� ��ȯ�մϴ�.
	 */
	float GetAspectRatio() { return aspectRatio_; }


	/**
	 * @brief �� ���� X:Y�� ���� ���� ���� ���� ����ϴ�.
	 *
	 * @return �� ���� X:Y�� ���� ���� ���� ���� ��ȯ�մϴ�.
	 */
	const float& GetAspectRatio() const { return aspectRatio_; }


	/**
	 * @brief ����� Ŭ���� �������� �Ÿ� ���� ����ϴ�.
	 *
	 * @return ����� Ŭ���� �������� �Ÿ� ���� ��ȯ�մϴ�.
	 */
	float GetNearZ() { return nearZ_; }


	/**
	 * @brief ����� Ŭ���� �������� �Ÿ� ���� ����ϴ�.
	 *
	 * @return ����� Ŭ���� �������� �Ÿ� ���� ��ȯ�մϴ�.
	 */
	const float& GetNearZ() const { return nearZ_; }


	/**
	 * @brief ���Ÿ� Ŭ���� �������� �Ÿ� ���� ����ϴ�.
	 *
	 * @return ���Ÿ� Ŭ���� �������� �Ÿ� ���� ��ȯ�մϴ�.
	 */
	float GetFarZ() { return farZ_; }


	/**
	 * @brief ���Ÿ� Ŭ���� �������� �Ÿ� ���� ����ϴ�.
	 *
	 * @return ���Ÿ� Ŭ���� �������� �Ÿ� ���� ��ȯ�մϴ�.
	 */
	const float& GetFarZ() const { return farZ_; }


	/**
	 * @brief �þ� ����� ����ϴ�.
	 *
	 * @return �þ� ����� ��ȯ�մϴ�.
	 */
	Matrix4x4f GetViewMatrix() { return view_; }


	/**
	 * @brief �þ� ����� ����ϴ�.
	 *
	 * @return �þ� ����� ��ȯ�մϴ�.
	 */
	const Matrix4x4f& GetViewMatrix() const { return view_; }


	/**
	 * @brief ���� ����� ����ϴ�.
	 *
	 * @return ���� ����� ��ȯ�մϴ�.
	 */
	Matrix4x4f GetProjectionMatrix() { return projection_; }


	/**
	 * @brief ���� ����� ����ϴ�.
	 *
	 * @return ���� ����� ��ȯ�մϴ�.
	 */
	const Matrix4x4f& GetProjectionMatrix() const { return projection_; }


	/**
	 * @brief ī�޶��� ���� �� ��ġ�� �����մϴ�.
	 *
	 * @param eyePosition ������ ī�޶��� ���� �� ��ġ�Դϴ�.
	 */
	void SetEyePosition(const Vector3f& eyePosition)
	{
		eyePosition_ = eyePosition;
		UpdateViewMatrix();
	}


	/**
	 * @brief ī�޶� �ٶ󺸰� �ִ� ��ġ�� �����մϴ�.
	 *
	 * @param eyeDirection ������ ī�޶� �ٶ󺸰� �ִ� ��ġ�Դϴ�.
	 */
	void SetEyeDirection(const Vector3f& eyeDirection)
	{
		eyeDirection_ = eyeDirection;
		UpdateViewMatrix();
	}


	/**
	 * @brief ī�޶��� �� ������ �����մϴ�.
	 *
	 * @param upDirection ������ ī�޶��� �� �����Դϴ�.
	 */
	void SetUpDirection(const Vector3f& upDirection)
	{
		upDirection_ = upDirection;
		UpdateViewMatrix();
	}


	/**
	 * @brief ����� ���� �ʵ� ����(����)�� �����մϴ�.
	 *
	 * @param fovRadians ������ �ʵ� ����(����) �Դϴ�.
	 */
	void SetFov(float fovRadians)
	{
		fov_ = fovRadians;
		UpdateProjectionMatrix();
	}


	/**
	 * @brief �� ���� X:Y�� ���� ���� ������ �����մϴ�.
	 *
	 * @param aspectRatio ������ �� ������ ���� ���� �����Դϴ�.
	 */
	void SetAspectRatio(float aspectRatio)
	{
		aspectRatio_ = aspectRatio;
		UpdateProjectionMatrix();
	}


	/**
	 * @brief ����� Ŭ���� �������� �Ÿ��� �����մϴ�.
	 *
	 * @param nearZ ������ ����� Ŭ���� �������� �Ÿ��Դϴ�.
	 */
	void SetNearZ(float nearZ)
	{
		nearZ_ = nearZ;
		UpdateProjectionMatrix();
	}


	/**
	 * @brief ���Ÿ� Ŭ���� �������� �Ÿ��� �����մϴ�.
	 *
	 * @param farZ ������ ���Ÿ� Ŭ���� �������� �Ÿ��Դϴ�.
	 */
	void SetFarZ(float farZ)
	{
		farZ_ = farZ;
		UpdateProjectionMatrix();
	}


protected:
	/**
	 * @brief �þ� ����� ������Ʈ�մϴ�.
	 */
	void UpdateViewMatrix();


	/**
	 * @brief ���� ����� ������Ʈ�մϴ�.
	 */
	void UpdateProjectionMatrix();


protected:
	/**
	 * @brief ī�޶��� ���� �� ��ġ�Դϴ�.
	 */
	Vector3f eyePosition_;


	/**
	 * @brief ī�޶��� �����Դϴ�.
	 */
	Vector3f eyeDirection_;


	/**
	 * @brief ī�޶��� �� �����Դϴ�.
	 */
	Vector3f upDirection_;


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
	Matrix4x4f view_;


	/**
	 * @brief ���� ����Դϴ�.
	 *
	 * @note ���� ��������� �ƴ� ���� ���� ����Դϴ�.
	 */
	Matrix4x4f projection_;
};