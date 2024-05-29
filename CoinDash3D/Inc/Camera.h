#pragma once

#include "Mat.h"
#include "Vec.h"

#include "IEntity.h"

class Character;


/**
 * @brief ���� ���� ī�޶� ��ƼƼ�Դϴ�.
 */
class Camera : public IEntity
{
public:
	/**
	 * @brief ī�޶� ��ƼƼ�� �������Դϴ�.
	 *
	 * @param character ī�޶� ����ٴ� ĳ�����Դϴ�.
	 */
	Camera(Character* character);


	/**
	 * @brief ī�޶� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Camera();


	/**
	 * @brief ī�޶� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Camera);


	/**
	 * @brief ī�޶� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ī�޶� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief ī�޶��� ���� �� ��ġ�� ����ϴ�.
	 *
	 * @return ī�޶��� ���� �� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vec3f& GetEyePosition() const { return eyePosition_; }


	/**
	 * @brief �þ� ����� ����ϴ�.
	 *
	 * @return �þ� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetView() const { return view_; }


	/**
	 * @brief ���� ����� ����ϴ�.
	 *
	 * @return ���� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetProjection() const { return projection_; }


private:
	/**
	 * @brief ĳ������ ��ġ�� �������� ī�޶��� ��ġ�� ����ϴ�.
	 */
	Vec3f GetEyePositionFromCharacter();


	/**
	 * @brief ī�޶��� ���¸� ������Ʈ�մϴ�.
	 */
	void UpdateState();


private:
	/**
	 * @brief ī�޶��� ���� �� ��ġ�Դϴ�.
	 */
	Vec3f eyePosition_;


	/**
	 * @brief ī�޶��� �����Դϴ�.
	 */
	Vec3f eyeDirection_;


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
	 *
	 * @note ���� ��������� �ƴ� ���� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;


	/**
	 * @brief ī�޶��� ������ �ӵ��Դϴ�.
	 */
	float speed_ = 2.5f;


	/**
	 * @brief Y�� ���Ϸ� ȸ�� �����Դϴ�.
	 */
	float yaw_ = 0.0f;


	/**
	 * @brief X�� ���Ϸ� ȸ�� �����Դϴ�.
	 */
	float pitch_ = 0.0f;


	/**
	 * @brief X�� ȸ�� ������ �ִ��Դϴ�.
	 */
	float minPitch_ = 0.0f;


	/**
	 * @brief X�� ȸ�� ������ �ּڰ��Դϴ�.
	 */
	float maxPitch_ = 0.0f;


	/**
	 * @brief �÷��̾�� ī�޶� ������ �Ÿ��Դϴ�.
	 */
	float distance_ = 0.0f;


	/**
	 * @brief ī�޶� ����ٴ� ĳ�����Դϴ�.
	 */
	Character* character_ = nullptr;
};