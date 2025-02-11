#pragma once

#include "IObject.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ����Ʈ ������Ʈ�Դϴ�.
 */
class Light : public IObject
{
public:
	/**
	 * @brief ����Ʈ ������Ʈ�� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Light() = default;


	/**
	 * @brief ����Ʈ ������Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Light();


	/**
	 * @brief ����Ʈ ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Light);


	/**
	 * @brief ����Ʈ ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param position
	 * @param direction
	 * @param ambientRGB
	 * @param diffuseRGB
	 * @param specularRGB
	 * @param worldUp
	 * @param projection
	 */
	void Initialize(
		const Vector3f& position,
		const Vector3f& direction,
		const Vector3f& ambientRGB,
		const Vector3f& diffuseRGB,
		const Vector3f& specularRGB,
		const Vector3f& worldUp,
		const Matrix4x4f projection
	);


	/**
	 * @brief ����Ʈ ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 *
	 * @note
	 * - ����Ʈ ������Ʈ�� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 * - ��Ÿ �ð� ���� �ʴ����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ����Ʈ ������Ʈ�� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ����Ʈ�� ��ġ�� ����ϴ�.
	 *
	 * @return ����Ʈ�� ��ġ�� ��ȯ�մϴ�.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief ����Ʈ�� ��ġ�� ����ϴ�.
	 *
	 * @return ����Ʈ�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief ����Ʈ�� ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDirection() { return direction_; }


	/**
	 * @brief ����Ʈ�� ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDirection() const { return direction_; }


	/**
	 * @brief ����Ʈ�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief ����Ʈ�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief ����Ʈ�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief ����Ʈ�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief ����Ʈ�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief ����Ʈ�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ����Ʈ�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief ����Ʈ�� �þ� ����� ����ϴ�.
	 * 
	 * @return ����Ʈ�� �þ� ����� ��ȯ�մϴ�.
	 */
	Matrix4x4f GetViewMatrix() { return view_; }


	/**
	 * @brief ����Ʈ�� �þ� ����� ����ϴ�.
	 *
	 * @return ����Ʈ�� �þ� ����� ��ȯ�մϴ�.
	 */
	const Matrix4x4f& GetViewMatrix() const { return view_; }


	/**
	 * @brief ����Ʈ�� ���� ����� ����ϴ�.
	 * 
	 * @return ����Ʈ�� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix4x4f GetProjectionMatrix() { return projection_; }


	/**
	 * @brief ����Ʈ�� ���� ����� ����ϴ�.
	 *
	 * @return ����Ʈ�� ���� ����� ��ȯ�մϴ�.
	 */
	const Matrix4x4f& GetProjectionMatrix() const { return projection_; }
	

protected:
	/**
	 * @brief ����Ʈ�� ��ġ�Դϴ�.
	 *
	 * @note �׸��� ��� �� ����մϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief ����Ʈ�� �����Դϴ�.
	 */
	Vector3f direction_;


	/**
	 * @brief ����Ʈ�� Ambient �����Դϴ�.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief ����Ʈ�� Diffuse �����Դϴ�.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief ����Ʈ�� Specular �����Դϴ�.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief ����Ʈ ������ �þ� ����Դϴ�.
	 */
	Matrix4x4f view_;


	/**
	 * @brief ����Ʈ ������ ���� ����Դϴ�.
	 */
	Matrix4x4f projection_;
};