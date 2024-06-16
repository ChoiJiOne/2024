#pragma once

#include "Mat.h"
#include "Vec.h"

#include "IEntity.h"

class Camera;


/**
 * @brief ���� ���� ������ ��ƼƼ�Դϴ�.
 */
class Light : public IEntity
{
public:
	/**
	 * @brief ������ ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param camera ������ ��ġ�� ������ �� ī�޶� ��ƼƼ�Դϴ�.
	 */
	Light(Camera* camera);


	/**
	 * @brief ������ ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Light();


	/**
	 * @brief ������ ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Light);


	/**
	 * @brief ������ ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ������ ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief ���� ���� ����Ʈ ��ġ ���� ����ϴ�.
	 * 
	 * @return ���� ���� ����Ʈ ��ġ ���� ��ȯ�մϴ�.
	 */
	const Vec3f& GetPosition() const { return position_; }


	/**
	 * @brief ����Ʈ ���� ���� ����ϴ�.
	 * 
	 * @return ����Ʈ ���� ���� ��ȯ�մϴ�.
	 */
	const Vec3f& GetDirection() const { return direction_; }


	/**
	 * @brief ����Ʈ ������ ����� ����ϴ�.
	 * 
	 * @return ����Ʈ ������ ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetLightSpaceMatrix() const { return lightSpaceMatrix_; }


	/**
	 * @brief ����Ʈ�� RGB���� ���� ����ϴ�.
	 * 
	 * @return ����Ʈ�� RGB ���� ���� ��ȯ�մϴ�.
	 */
	const Vec3f& GetColor() const { return color_; }


private:
	/**
	 * @brief ����Ʈ�� ��ġ�Դϴ�.
	 */
	Vec3f position_;


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vec3f direction_;


	/**
	 * @brief ����Ʈ�� ������ �þ� ����Դϴ�.
	 */
	Mat4x4 view_;


	/**
	 * @brief ����Ʈ ������ ���� ���� ����Դϴ�.
	 */
	Mat4x4 projection_;


	/**
	 * @brief ����Ʈ ������ ����Դϴ�.
	 */
	Mat4x4 lightSpaceMatrix_;


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vec3f color_;


	/**
	 * @brief ������ ��ġ�� ������ �� ī�޶� ��ƼƼ�Դϴ�.
	 */
	Camera* camera_ = nullptr;
};