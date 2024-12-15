#pragma once

#include <string>
#include <map>

#include "Vec2.h"
#include "Vec4.h"

#include "ConfigManager.h"
#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ���� ���¸� �����ִ� ��ƼƼ�Դϴ�.
 */
class StatusViewer : public IEntity
{
public:
	/**
	 * @brief ���� ���¸� �����ִ� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param fontID ��Ʈ ���ҽ� ID�Դϴ�.
	 */
	explicit StatusViewer(const RUID& fontID);


	/**
	 * @brief ���� ���¸� �����ִ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StatusViewer();


	/**
	 * @brief ���� ���¸� �����ִ� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StatusViewer);


	/**
	 * @brief ���� ���¸� �����ִ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ���¸� �����ִ� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���� ���¸� �����ִ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief ���� ������ �´� �ؽ�Ʈ�Դϴ�.
	 */
	std::map<ConfigManager::ELevel, std::wstring> levels_;
	

	/**
	 * @brief ���� �� Ÿ�Կ� �´� ���ҽ��Դϴ�.
	 */
	std::map<ConfigManager::EBird, RUID> birdIDs_;
};