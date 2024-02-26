#pragma once

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ��׶��� ��ƼƼ�Դϴ�.
 */
class Background : public IEntity
{
public:
	/**
	 * @brief ��׶��� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param textureID ��׶��� �ؽ�ó�� ID�Դϴ�.
	 */
	Background(const RUID& textureID);


	/**
	 * @brief ��׶��� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Background();


	/**
	 * @brief ��׶��� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief ��׶��带 ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ��׶��带 ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ��׶��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ��׶��� �ؽ�ó ���ҽ��� ID�Դϴ�.
	 */
	RUID textureID_ = 0;
};