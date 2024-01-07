#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ������(Directional Light)�Դϴ�.
 */
class DirectionalLight
{
public:
	/**
	 * @brief ������(Directional Light)�� ����Ʈ �������Դϴ�.
	 */
	DirectionalLight() = default;


	/**
	 * @brief ������(Directional Light)�� �������Դϴ�.
	 * 
	 * @param position �������� ��ġ�Դϴ�.
	 * @param direction �������� �����Դϴ�.
	 * @param ambientRGB �������� Ambient �����Դϴ�.
	 * @param diffuseRGB �������� Diffuse �����Դϴ�.
	 * @param specularRGB �������� Specular �����Դϴ�.
	 */
	DirectionalLight(const Vector3f& position, const Vector3f& direction, const Vector3f& ambientRGB, const Vector3f& diffuseRGB, const Vector3f& specularRGB)
		: position_(position)
		, direction_(direction)
		, ambientRGB_(ambientRGB)
		, diffuseRGB_(diffuseRGB)
		, specularRGB_(specularRGB) {}


	/**
	 * @brief ������(Directional Light)�� ���� �������Դϴ�.
	 * 
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 */
	DirectionalLight(DirectionalLight&& instance) noexcept
		: position_(instance.position_)
		, direction_(instance.direction_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_) {}


	/**
	 * @brief ������(Directional Light)�� ���� �������Դϴ�.
	 *
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 */
	DirectionalLight(const DirectionalLight& instance) noexcept
		: position_(instance.position_)
		, direction_(instance.direction_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_) {}


	/**
	 * @brief ������(Directional Light)�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~DirectionalLight() {}


	/**
	 * @brief �������� ���� �������Դϴ�.
	 * 
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 * 
	 * @return ������ �������� �����ڸ� ��ȯ�մϴ�.
	 */
	DirectionalLight& operator=(DirectionalLight&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		direction_ = instance.direction_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;

		return *this;
	}


	/**
	 * @brief �������� ���� �������Դϴ�.
	 *
	 * @param instance �������� ���� ������Ƽ�� ������ �ν����Դϴ�.
	 *
	 * @return ������ �������� �����ڸ� ��ȯ�մϴ�.
	 */
	DirectionalLight& operator=(const DirectionalLight& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		direction_ = instance.direction_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;

		return *this;
	}

	
	/**
	 * @brief ������(Directional Light)�� ��ġ�� ����ϴ�.
	 * 
	 * @return ������(Directional Light)�� ��ġ�� ��ȯ�մϴ�.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief ������(Directional Light)�� ��ġ�� ����ϴ�.
	 *
	 * @return ������(Directional Light)�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief ������(Directional Light)�� ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDirection() { return direction_; }


	/**
	 * @brief ������(Directional Light)�� ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDirection() const { return direction_; }


	/**
	 * @brief ������(Directional Light)�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief ������(Directional Light)�� �ֺ�(Ambient) ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� �ֺ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief ������(Directional Light)�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief ������(Directional Light)�� Ȯ��(Diffuse) ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� Ȯ�� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief ������(Directional Light)�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief ������(Directional Light)�� �ݻ�(Specular) ������ ����ϴ�.
	 *
	 * @return ������(Directional Light)�� �ݻ� ������ ��ȯ�մϴ�.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief ������(Directional Light)�� ��ġ�� �����մϴ�.
	 * 
	 * @param position ������ �������� ��ġ�Դϴ�.
	 */
	void SetPosition(const Vector3f& position) { position_ = position; }


	/**
	 * @brief ������(Directional Light)�� ������ �����մϴ�.
	 * 
	 * @param direction ������ �������� �����Դϴ�.
	 */
	void SetDirection(const Vector3f& direction) { direction_ = direction; }


	/**
	 * @brief ������(Directional Light)�� �ֺ�(Ambient) ������ �����մϴ�.
	 *
	 * @param ambientRGB ������ �ֺ�(Ambient) �����Դϴ�.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief ������(Directional Light)�� Ȯ��(Diffuse) ������ �����մϴ�.
	 *
	 * @param diffuseRGB ������ Ȯ��(Diffuse) �����Դϴ�.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief ������(Directional Light)�� �ݻ�(Specular) ������ �����մϴ�.
	 *
	 * @param specular ������ �ݻ�(Specular) �����Դϴ�.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


private:
	/**
	 * @brief �������� ��ġ�Դϴ�. 
	 * 
	 * @note �׸��� ��� �� ����մϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief �������� �����Դϴ�.
	 */
	Vector3f direction_;


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
};