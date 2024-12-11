#pragma once

#include "IResource.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief �޽��� �⺻ ����(Material)�Դϴ�.
 */
class Material : public IResource
{
public:
	/**
	 * @brief ������ ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
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
	 * @brief ����(Material) ���ҽ��� �Դϴ�.
	 *
	 * @param ambientRGB ������ �ֺ�(Ambient) �����Դϴ�.
	 * @param diffuseRGB ������ Ȯ��(Diffuse) �����Դϴ�.
	 * @param specularRGB ������ �ݻ�(Specular) �����Դϴ�.
	 * @param shininess ������ ��� ����Դϴ�.
	 */
	void Initialize(const Vector3f& ambientRGB, const Vector3f& diffuseRGB, const Vector3f& specularRGB, float shininess);


	/**
	 * @brief ����(Material)�� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;

	
	/**
	 * @brief ������ �ֺ�(Ambient) ������ ����ϴ�.
	 * 
	 * @return ������ �ֺ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief ������ �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ������ �ֺ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief ������ Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ������ Ȯ�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief ������ Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ������ Ȯ�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief ������ �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ������ �ݻ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief ������ �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ������ �ݻ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief ������ ��� ������ ����ϴ�.
	 *
	 * @return ������ ��� ������ ��ȯ�մϴ�.
	 */
	float GetShininess() { return shininess_; }


	/**
	 * @brief ������ ��� ������ ����ϴ�.
	 *
	 * @return ������ ��� ������ ��ȯ�մϴ�.
	 */
	const float& GetShininess() const { return shininess_; }


	/**
	 * @brief ������ �ֺ�(Ambient) ������ �����մϴ�.
	 * 
	 * @param ambientRGB ������ �ֺ�(Ambient) ����Դϴ�.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief ������ Ȯ��(Diffuse) ������ �����մϴ�.
	 * 
	 * @param diffuseRGB ������ Ȯ��(Diffuse) ����Դϴ�.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief ������ �ݻ�(Specular) ������ �����մϴ�.
	 * 
	 * @param specular ������ �ݻ�(Specular) ����Դϴ�.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief ������ ��� ������ �����մϴ�.
	 * 
	 * @param shininess ������ ��� ����Դϴ�.
	 */
	void SetShininess(float shininess) { shininess_ = shininess; }


private:
	/**
	 * @brief ������ �ֺ�(Ambient) �����Դϴ�.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief ������ Ȯ��(Diffuse) �����Դϴ�.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief ������ �ݻ�(Specular) �����Դϴ�.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief ������ ��� ����Դϴ�.
	 */
	float shininess_;
};