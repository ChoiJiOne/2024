#pragma once

#include "IObject.h"

#include "DirectionalLight.h"


/**
 * @brief ����� ���� ������ ����Ʈ �Ӽ��Դϴ�.
 */
class LightProperties : public IObject
{
public:
	/**
	 * @brief ���� ������ ����Ʈ �Ӽ��� ����Ʈ �������Դϴ�.
	 */
	LightProperties() = default;


	/**
	 * @brief ���� ������ ����Ʈ �Ӽ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~LightProperties();


	/**
	 * @brief ���� ������ ����Ʈ �Ӽ��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(LightProperties);


	/**
	 * @brief ���� ������ ����Ʈ �Ӽ��� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� ������ ����Ʈ �Ӽ��� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 *
	 * @note ��Ÿ �ð� ���� �ʴ����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ������ ����Ʈ �Ӽ��� �������� ����ϴ�.
	 * 
	 * @return ���� ������ ����Ʈ �Ӽ��� ������ ��ü ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const DirectionalLight& GetDirectionalLight() const { return directionalLight_; }


private:
	/**
	 * @brief ���� ������ �������Դϴ�.
	 */
	DirectionalLight directionalLight_;


	/**
	 * @brief �������� �����Դϴ�. ������ -1.0 ~ 1.0�Դϴ�.
	 */
	Vector3f direction_;


	/**
	 * @brief �ֺ����� RGB �����Դϴ�.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief �л걤�� RGB �����Դϴ�.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief �ݻ籤�� RGB �����Դϴ�.
	 */
	Vector3f specularRGB_;
};