#pragma once

#include "Vec2.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�Դϴ�.
 */
class ReadyViewer : public IEntity
{
public:
	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�� �������Դϴ�.
	 */
	explicit ReadyViewer();


	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ReadyViewer();


	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ReadyViewer);


	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �غ�(Ready) ���¸� ǥ���ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �غ�(Ready) ���¸� ȭ�鿡 ǥ���� �� ���θ� �����մϴ�.
	 * 
	 * @param bIsVisible �غ�(Ready) ���¸� ȭ�鿡 ǥ���ϸ� true, �׷��� ������ false�Դϴ�.
	 */
	void SetVisible(bool bIsVisible) { bIsVisible_ = bIsVisible; }


private:
	/**
	 * @brief �غ�(Ready) ���¸� ȭ�鿡 ǥ���� �� �����Դϴ�.
	 */
	bool bIsVisible_ = true;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�Դϴ�.
	 */
	RUID infoID_ = -1;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�� ��ġ�Դϴ�.
	 */
	Vec2f infoLocation_;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float infoWidth_ = 0.0f;


	/**
	 * @brief ���� �÷��� ������ ǥ���� �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float infoHeight_ = 0.0f;


	/**
	 * @brief Get Ready �ؽ�ó�Դϴ�.
	 */
	RUID getReadyID_ = -1;


	/**
	 * @brief Get Ready �ؽ�ó�� ��ġ�Դϴ�.
	 */
	Vec2f getReadyLocation_;


	/**
	 * @brief Get Ready �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float getReadyWidth_ = 0.0f;


	/**
	 * @brief Get Ready �ؽ�ó�� ���� ũ���Դϴ�.
	 */
	float getReadyHeight_ = 0.0f;


	/**
	 * @brief ���� �ð����Դϴ�.
	 */
	float accumulateTime_ = 0.0f;
};