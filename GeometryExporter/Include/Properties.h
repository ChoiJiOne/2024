#pragma once

#include "IObject.h"

#include "DirectionalLight.h"


/**
 * @brief ����� ���� ������ �Ӽ��Դϴ�.
 */
class Properties : public IObject
{
public:
	/**
	 * @brief ���� ������ �Ӽ��� ����Ʈ �������Դϴ�.
	 */
	Properties() = default;


	/**
	 * @brief ���� ������ �Ӽ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Properties();


	/**
	 * @brief ���� ������ �Ӽ��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Properties);


	/**
	 * @brief ���� ������ �Ӽ��� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� ������ �Ӽ��� ������Ʈ�մϴ�.
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
	 * @brief ���� ������ �Ӽ��� �������� ����ϴ�.
	 * 
	 * @return ���� ������ �Ӽ��� ������ ��ü ��� �����ڸ� ��ȯ�մϴ�.
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