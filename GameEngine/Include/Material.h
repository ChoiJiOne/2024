#pragma once

#include "IResource.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief �޽��� �⺻ ���� ���ҽ��Դϴ�.
 */
class Material : public IResource
{
public:
	/**
	 * @brief ������ ����Ʈ �������Դϴ�.
	 */
	Material() = default;


	/**
	 * @brief ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Material();


	/**
	 * @brief ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Material);


	/**
	 * @brief ���� ���ҽ��� �����մϴ�.
	 * 
	 * @param ambient ������ �ֺ�(Ambient) ����Դϴ�.
	 * @param diffuse ������ Ȯ��(Diffuse) ����Դϴ�.
	 * @param specular ������ �ݻ�(Specular) ����Դϴ�.
	 * @param shininess ������ ��� ����Դϴ�.
	 */
	void Initialize(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess);


	/**
	 * @brief ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ �ֺ�(Ambient) ��Ҹ� ����ϴ�.
	 * 
	 * @return ������ �ֺ� ��Ҹ� ��ȯ�մϴ�.
	 */
	Vector3f GetAmbient() { return ambient_; }


	/**
	 * @brief ������ �ֺ�(Ambient) ��Ҹ� ����ϴ�.
	 *
	 * @return ������ �ֺ� ��Ҹ� ��ȯ�մϴ�.
	 */
	const Vector3f& GetAmbient() const { return ambient_; }


	/**
	 * @brief ������ Ȯ��(Diffuse) ��Ҹ� ����ϴ�.
	 *
	 * @return ������ Ȯ�� ��Ҹ� ��ȯ�մϴ�.
	 */
	Vector3f GetDiffuse() { return diffuse_; }


	/**
	 * @brief ������ Ȯ��(Diffuse) ��Ҹ� ����ϴ�.
	 *
	 * @return ������ Ȯ�� ��Ҹ� ��ȯ�մϴ�.
	 */
	const Vector3f& GetDiffuse() const { return diffuse_; }


	/**
	 * @brief ������ �ݻ�(Specular) ��Ҹ� ����ϴ�.
	 *
	 * @return ������ �ݻ� ��Ҹ� ��ȯ�մϴ�.
	 */
	Vector3f GetSpecular() { return specular_; }


	/**
	 * @brief ������ �ݻ�(Specular) ��Ҹ� ����ϴ�.
	 *
	 * @return ������ �ݻ� ��Ҹ� ��ȯ�մϴ�.
	 */
	const Vector3f& GetSpecular() const { return specular_; }


	/**
	 * @brief ������ ��� ��Ҹ� ����ϴ�.
	 *
	 * @return ������ ��� ��Ҹ� ��ȯ�մϴ�.
	 */
	float GetShininess() { return shininess_; }


	/**
	 * @brief ������ ��� ��Ҹ� ����ϴ�.
	 *
	 * @return ������ ��� ��Ҹ� ��ȯ�մϴ�.
	 */
	const float& GetShininess() const { return shininess_; }


	/**
	 * @brief ������ �ֺ�(Ambient) ��Ҹ� �����մϴ�.
	 * 
	 * @param ambient ������ �ֺ�(Ambient) ����Դϴ�.
	 */
	void SetAmbient(const Vector3f& ambient) { ambient_ = ambient; }


	/**
	 * @brief ������ Ȯ��(Diffuse) ��Ҹ� �����մϴ�.
	 * 
	 * @param diffuse ������ Ȯ��(Diffuse) ����Դϴ�.
	 */
	void SetDiffuse(const Vector3f& diffuse) { diffuse_ = diffuse; }


	/**
	 * @brief ������ �ݻ�(Specular) ��Ҹ� �����մϴ�.
	 * 
	 * @param specular ������ �ݻ�(Specular) ����Դϴ�.
	 */
	void SetSpecular(const Vector3f& specular) { specular_ = specular; }


	/**
	 * @brief ������ ��� ��Ҹ� �����մϴ�.
	 * 
	 * @param shininess ������ ��� ����Դϴ�.
	 */
	void SetShininess(float shininess) { shininess_ = shininess; }


private:
	/**
	 * @brief ������ �ֺ�(Ambient) ����Դϴ�.
	 */
	Vector3f ambient_;


	/**
	 * @brief ������ Ȯ��(Diffuse) ����Դϴ�.
	 */
	Vector3f diffuse_;


	/**
	 * @brief ������ �ݻ�(Specular) ����Դϴ�.
	 */
	Vector3f specular_;


	/**
	 * @brief ������ ��� ����Դϴ�.
	 */
	float shininess_;
};