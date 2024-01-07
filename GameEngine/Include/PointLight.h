#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ����(Point Light)�Դϴ�.
 */
class PointLight
{
public:
	/**
	 * @brief ����(Point Light)�� ����Ʈ �������Դϴ�.
	 */
	PointLight() = default;


	/**
	 * @brief ����(Point Light)�� �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param ambientRGB ������ Ambient �����Դϴ�.
	 * @param diffuseRGB ������ Diffuse �����Դϴ�.
	 * @param specularRGB ������ Specular �����Դϴ�.
	 * @param constant ������ ������ ��꿡 ����� ������Դϴ�.
	 * @param linear ������ ������ ��꿡 ����� �������Դϴ�.
	 * @param quadratic ������ ������ ��꿡 ����� �������Դϴ�.
	 */
	PointLight(
		const Vector3f& position, 
		const Vector3f& ambientRGB, 
		const Vector3f& diffuseRGB, 
		const Vector3f& specularRGB, 
		const float& constant, 
		const float& linear, 
		const float& quadratic
	) : position_(position), 
		ambientRGB_(ambientRGB), 
		diffuseRGB_(diffuseRGB), 
		specularRGB_(specularRGB),
		constant_(constant),
		linear_(linear),
		quadratic_(quadratic) {}


	/**
	 * @brief ����(Point Light)�� ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� ������Ƽ�� ������ �ν����Դϴ�.
	 */
	PointLight(PointLight&& instance) noexcept
		: position_(instance.position_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_) 
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief ����(Point Light)�� ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� ������Ƽ�� ������ �ν����Դϴ�.
	 */
	PointLight(const PointLight& instance) noexcept
		: position_(instance.position_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief ����(Point Light)�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PointLight() {}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� ������Ƽ�� ������ �ν����Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	PointLight& operator=(PointLight&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� ������Ƽ�� ������ �ν����Դϴ�.
	 *
	 * @return ������ ������ �����ڸ� ��ȯ�մϴ�.
	 */
	PointLight& operator=(const PointLight& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief ����(Point Light)�� ��ġ�� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ��ġ�� ��ȯ�մϴ�.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief ����(Point Light)�� ��ġ�� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetPosition() const { return position_; }
	

	/**
	 * @brief ����(Point Light)�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ����(Point Light)�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief ����(Point Light)�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ����(Point Light)�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief ����(Point Light)�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ����(Point Light)�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief ����(Point Light)�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ����(Point Light)�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief ����(Point Light)�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ����(Point Light)�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief ����(Point Light)�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ����(Point Light)�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� ������� ����ϴ�.
	 * 
	 * @return ����(Point Light)�� ������ ��꿡 ����� ������� ��ȯ�մϴ�.
	 */
	float GetConstant() { return constant_; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� ������� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ������ ��꿡 ����� ������� ��ȯ�մϴ�.
	 */
	const float& GetConstant() const { return constant_; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	float GetLinear() { return linear_; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	const float& GetLinear() const { return linear_; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	float GetQuadratic() { return quadratic_; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ����(Point Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	const float& GetQuadratic() const { return quadratic_; }


	/**
	 * @brief ����(Point Light)�� ��ġ�� �����մϴ�.
	 *
	 * @param position ������ ������ ��ġ�Դϴ�.
	 */
	void SetPosition(const Vector3f& position) { position_ = position; }

	
	/**
	 * @brief ����(Point Light)�� �ֺ�(Ambient) ������ �����մϴ�.
	 *
	 * @param ambientRGB ������ �ֺ�(Ambient) �����Դϴ�.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief ����(Point Light)�� Ȯ��(Diffuse) ������ �����մϴ�.
	 *
	 * @param diffuseRGB ������ Ȯ��(Diffuse) �����Դϴ�.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief ����(Point Light)�� �ݻ�(Specular) ������ �����մϴ�.
	 *
	 * @param specular ������ �ݻ�(Specular) �����Դϴ�.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� ������� �����մϴ�.
	 * 
	 * @param constant ������ ����� ���Դϴ�.
	 */
	void SetConstant(float constant) { constant_ = constant; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� �������� �����մϴ�.
	 * 
	 * @param linear ������ ������ ���Դϴ�.
	 */
	void SetLinear(float linear) { linear_ = linear; }


	/**
	 * @brief ����(Point Light)�� ������ ��꿡 ����� �������� �����մϴ�.
	 * 
	 * @param quadratic ������ ������ ���Դϴ�.
	 */
	void SetQuadratic(float quadratic) { quadratic_ = quadratic; }


private:
	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief ������ Ambient �����Դϴ�.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief ������ Diffuse �����Դϴ�.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief ������ Specular �����Դϴ�.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief ������ ������ ��꿡 ����� ������Դϴ�.
	 * 
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float constant_;


	/**
	 * @brief ������ ������ ��꿡 ����� �������Դϴ�.
	 * 
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float linear_;


	/**
	 * @brief ������ ������ ��꿡 ����� �������Դϴ�.
	 * 
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float quadratic_;
};