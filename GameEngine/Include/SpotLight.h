#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ������(Spot Light)�Դϴ�.
 */
class SpotLight
{
public:
	/**
	 * @brief ������(Spot Light)�� ����Ʈ �������Դϴ�.
	 */
	SpotLight() = default;


	/**
	 * @brief ������(Spot Light)�� �������Դϴ�.
	 *
	 * @param position �������� ��ġ�Դϴ�.
	 * @param direction �������� �����Դϴ�.
	 * @param cutOff �������� �� ���� �ڻ��� ���Դϴ�.
	 * @param outerCutOff �������� �ܺ� �� ���� �ڻ��� ���Դϴ�.
	 * @param ambientRGB �������� Ambient �����Դϴ�.
	 * @param diffuseRGB �������� Diffuse �����Դϴ�.
	 * @param specularRGB �������� Specular �����Դϴ�.
	 * @param constant �������� ������ ��꿡 ����� ������Դϴ�.
	 * @param linear �������� ������ ��꿡 ����� �������Դϴ�.
	 * @param quadratic �������� ������ ��꿡 ����� �������Դϴ�.
	 */
	SpotLight(
		const Vector3f& position,
		const Vector3f& direction,
		const float& cutOff,
		const float& outerCutOff,
		const Vector3f& ambientRGB,
		const Vector3f& diffuseRGB,
		const Vector3f& specularRGB,
		const float& constant,
		const float& linear,
		const float& quadratic
	) : position_(position),
		direction_(direction),
		cutOff_(cutOff),
		outerCutOff_(outerCutOff),
		ambientRGB_(ambientRGB),
		diffuseRGB_(diffuseRGB),
		specularRGB_(specularRGB),
		constant_(constant),
		linear_(linear),
		quadratic_(quadratic) {}


	/**
	 * @brief ������(Spot Light)�� ���� �������Դϴ�.
	 *
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 */
	SpotLight(SpotLight&& instance) noexcept
		: position_(instance.position_)
		, direction_(instance.direction_)
		, cutOff_(instance.cutOff_)
		, outerCutOff_(instance.outerCutOff_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief ������(Spot Light)�� ���� �������Դϴ�.
	 *
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 */
	SpotLight(const SpotLight& instance) noexcept
		: position_(instance.position_)
		, direction_(instance.direction_)
		, cutOff_(instance.cutOff_)
		, outerCutOff_(instance.outerCutOff_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief ������(Spot Light)�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~SpotLight() {}


	/**
	 * @brief �������� ���� �������Դϴ�.
	 *
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 *
	 * @return ������ �������� �����ڸ� ��ȯ�մϴ�.
	 */
	SpotLight& operator=(SpotLight&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		direction_ = instance.direction_;
		cutOff_ = instance.cutOff_;
		outerCutOff_ = instance.outerCutOff_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief �������� ���� �������Դϴ�.
	 *
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 *
	 * @return ������ �������� �����ڸ� ��ȯ�մϴ�.
	 */
	SpotLight& operator=(const SpotLight& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		direction_ = instance.direction_;
		cutOff_ = instance.cutOff_;
		outerCutOff_ = instance.outerCutOff_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief ������(Spot Light)�� ��ġ�� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ��ġ�� ��ȯ�մϴ�.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief ������(Spot Light)�� ��ġ�� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief ������(Spot Light)�� ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDirection() { return direction_; }


	/**
	 * @brief ������(Spot Light)�� ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDirection() const { return direction_; }


	/**
	 * @brief ������(Spot Light)�� �� ���� �ڻ��� ���� ����ϴ�.
	 * 
	 * @return ������(Spot Light)�� �� ���� �ڻ��� ���� ��ȯ�մϴ�.
	 */
	float GetCutOff() { return cutOff_; }


	/**
	 * @brief ������(Spot Light)�� �� ���� �ڻ��� ���� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �� ���� �ڻ��� ���� ��ȯ�մϴ�.
	 */
	const float& GetCutOff() const { return cutOff_; }


	/**
	 * @brief ������(Spot Light)�� �ܺ� �� ���� �ڻ��� ���� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �ܺ� �� ���� �ڻ��� ���� ��ȯ�մϴ�.
	 */
	float GetOuterCutOff() { return outerCutOff_; }


	/**
	 * @brief ������(Spot Light)�� �ܺ� �� ���� �ڻ��� ���� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �ܺ� �� ���� �ڻ��� ���� ��ȯ�մϴ�.
	 */
	const float& GetOuterCutOff() const { return outerCutOff_; }
	

	/**
	 * @brief ������(Spot Light)�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief ������(Spot Light)�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief ������(Spot Light)�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief ������(Spot Light)�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief ������(Spot Light)�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief ������(Spot Light)�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ������(Spot Light)�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� ������� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��꿡 ����� ������� ��ȯ�մϴ�.
	 */
	float GetConstant() { return constant_; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� ������� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��꿡 ����� ������� ��ȯ�մϴ�.
	 */
	const float& GetConstant() const { return constant_; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	float GetLinear() { return linear_; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	const float& GetLinear() const { return linear_; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	float GetQuadratic() { return quadratic_; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� �������� ����ϴ�.
	 *
	 * @return ������(Spot Light)�� ������ ��꿡 ����� �������� ��ȯ�մϴ�.
	 */
	const float& GetQuadratic() const { return quadratic_; }


	/**
	 * @brief ������(Spot Light)�� ��ġ�� �����մϴ�.
	 *
	 * @param position ������ �������� ��ġ�Դϴ�.
	 */
	void SetPosition(const Vector3f& position) { position_ = position; }


	/**
	 * @brief ������(Spot Light)�� ������ �����մϴ�.
	 *
	 * @param direction ������ �������� �����Դϴ�.
	 */
	void SetDirection(const Vector3f& direction) { direction_ = direction; }


	/**
	 * @brief ������(Spot Light)�� �� ���� �ڻ��� ���� �����մϴ�.
	 * 
	 * @param cutOff ������ �� ���� �ڻ��� ���Դϴ�.
	 */
	void SetCutOff(const float& cutOff) { cutOff_ = cutOff; }


	/**
	 * @brief ������(Spot Light)�� �ܺ� �� ���� �ڻ��� ���� �����մϴ�.
	 *
	 * @param outerCutOff ������ �ܺ� �� ���� �ڻ��� ���Դϴ�.
	 */
	void SetOuterCutOff(const float& outerCutOff) { outerCutOff_ = outerCutOff; }


	/**
	 * @brief ������(Spot Light)�� �ֺ�(Ambient) ������ �����մϴ�.
	 *
	 * @param ambientRGB ������ �ֺ�(Ambient) �����Դϴ�.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief ������(Spot Light)�� Ȯ��(Diffuse) ������ �����մϴ�.
	 *
	 * @param diffuseRGB ������ Ȯ��(Diffuse) �����Դϴ�.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief ������(Spot Light)�� �ݻ�(Specular) ������ �����մϴ�.
	 *
	 * @param specular ������ �ݻ�(Specular) �����Դϴ�.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� ������� �����մϴ�.
	 *
	 * @param constant ������ ����� ���Դϴ�.
	 */
	void SetConstant(float constant) { constant_ = constant; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� �������� �����մϴ�.
	 *
	 * @param linear ������ ������ ���Դϴ�.
	 */
	void SetLinear(float linear) { linear_ = linear; }


	/**
	 * @brief ������(Spot Light)�� ������ ��꿡 ����� �������� �����մϴ�.
	 *
	 * @param quadratic ������ ������ ���Դϴ�.
	 */
	void SetQuadratic(float quadratic) { quadratic_ = quadratic; }


private:
	/**
	 * @brief �������� ��ġ�Դϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief �������� �����Դϴ�.
	 */
	Vector3f direction_;


	/**
	 * @brief �������� �� �������Դϴ�.
	 *
	 * @note �� ���� �ڻ��� ���Դϴ�.
	 */
	float cutOff_;


	/**
	 * @brief �������� �ܺ� �� �������Դϴ�.
	 *
	 * @note �� ���� �ڻ��� ���Դϴ�.
	 */
	float outerCutOff_;


	/**
	 * @brief �������� Ambient �����Դϴ�.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief �������� Diffuse �����Դϴ�.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief �������� Specular �����Դϴ�.
	 */
	Vector3f specularRGB_;
	

	/**
	 * @brief �������� ������ ��꿡 ����� ������Դϴ�.
	 *
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float constant_;


	/**
	 * @brief �������� ������ ��꿡 ����� �������Դϴ�.
	 *
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float linear_;


	/**
	 * @brief �������� ������ ��꿡 ����� �������Դϴ�.
	 *
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float quadratic_;
};