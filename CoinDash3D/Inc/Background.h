#pragma once

#include "IEntity.h"

class Skybox;


/**
 * @brief �ΰ��� ��׶��� ��ƼƼ�Դϴ�.
 */
class Background : public IEntity
{
public:
	/**
	 * @brief �ΰ��� ��׶��� ��ƼƼ�� �������Դϴ�.
	 */
	Background();


	/**
	 * @brief �ΰ��� ��׶��� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Background();


	/**
	 * @brief �ΰ��� ��׶��� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief �ΰ��� ��׶��� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �ΰ��� ��׶��� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ��׶����� ��ī�� �ڽ� ���ҽ��� ����ϴ�.
	 * 
	 * @return ��׶����� ��ī�� �ڽ� ���ҽ��� ��ȯ�մϴ�.
	 */
	const Skybox* GetSkybox() const { return skybox_; }


private:
	/**
	 * @brief ��׶����� ��ī�� �ڽ� ���ҽ��Դϴ�.
	 */
	Skybox* skybox_ = nullptr;
};