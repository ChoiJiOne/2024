#pragma once

#include "IResource.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief �޽��� �⺻ ����(Material)�Դϴ�.
 */
class Material
{
public:
	/**
	 * @brief ������ ����Ʈ �������Դϴ�.
	 */
	Material() = default;


	/**
	 * @brief ����(Material)�� �������Դϴ�.
	 * 
	 * @param ambient ������ �ֺ�(Ambient) ����Դϴ�.
	 * @param diffuse ������ Ȯ��(Diffuse) ����Դϴ�.
	 * @param specular ������ �ݻ�(Specular) ����Դϴ�.
	 * @param shininess ������ ��� ����Դϴ�.
	 */
	Material(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess) noexcept
		: ambient_(ambient)
		, diffuse_(diffuse)
		, specular_(specular)
		, shininess_(shininess) {}


	/**
	 * @brief ����(Material)�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Material(Material&& instance) noexcept
		: ambient_(instance.ambient_)
		, diffuse_(instance.diffuse_)
		, specular_(instance.specular_)
		, shininess_(instance.shininess_) {}


	/**
	 * @brief ����(Material)�� ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 */
	Material(const Material& instance) noexcept
		: ambient_(instance.ambient_)
		, diffuse_(instance.diffuse_)
		, specular_(instance.specular_)
		, shininess_(instance.shininess_) {}


	/**
	 * @brief ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Material();


	/**
	 * @brief ������ ���� �������Դϴ�.
	 * 
	 * @param instance ������ ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Material& operator=(Material&& instance) noexcept
	{
		if (this == &instance) return *this;

		ambient_ = instance.ambient_;
		diffuse_ = instance.diffuse_;
		specular_ = instance.specular_;
		shininess_ = instance.shininess_;

		return *this;
	}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� ������Ƽ�� ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Material& operator=(const Material& instance) noexcept
	{
		if (this == &instance) return *this;

		ambient_ = instance.ambient_;
		diffuse_ = instance.diffuse_;
		specular_ = instance.specular_;
		shininess_ = instance.shininess_;

		return *this;
	}

	
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