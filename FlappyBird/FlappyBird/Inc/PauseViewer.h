#pragma once

#include <string>
#include <functional>

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�Դϴ�.
 */
class PauseViewer : public IEntity
{
public:
	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param fontID �ؽ�Ʈ ������ �� ����� ��Ʈ ���ҽ��� ID�Դϴ�.
	 */
	explicit PauseViewer(const RUID& fontID);


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PauseViewer();


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PauseViewer);


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ���¸� �ٽ� �簳�� �̺�Ʈ�� �����մϴ�.
	 * 
	 * @param continueEvent ������ �̺�Ʈ�Դϴ�.
	 */
	void SetContinueEvent(const std::function<void()>& continueEvent) { continueEvent_ = continueEvent; }


private:
	/**
	 * @brief �ؽ�Ʈ ������ �� ����� ��Ʈ ���ҽ��� ID�Դϴ�.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief ȭ�鿡 ǥ���� �ؽ�Ʈ�� ��ġ�Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief ȭ�鿡 ǥ���� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring text_;


	/**
	 * @brief ���� ���¸� �ٽ� �簳�� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> continueEvent_;
};