#pragma once


/**
 * @brief Ÿ��(Ŭ���� Ȥ�� ����ü)�� ���� ������ �� ���� �����ڸ� ������� ���ϵ��� �����մϴ�.
 *
 * @note �� ��ũ�ΰ� ���ǵǾ� ���� ���� Ÿ���� �ݵ�� ��������� ���� �����ڿ� ���� �����ڸ� ���� �����ڸ� �����ؾ� �մϴ�.
 *
 * @param TypeName ���� ������ �� ���� �����ڸ� ������ Ÿ���� �̸��Դϴ�.
 */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)    \
TypeName(TypeName&&) = delete;                \
TypeName(const TypeName&) = delete;           \
TypeName& operator=(TypeName&&) = delete;     \
TypeName& operator=(const TypeName) = delete;
#endif


/**
 * @brief �� �������̽��Դϴ�.
 */
class IScene
{
public:
	/**
	 * @brief �� �������̽��� �������Դϴ�.
	 */
	IScene() {}


	/**
	 * @brief �� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IScene() {}


	/**
	 * @brief �� �������̽��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;


	/**
	 * @brief ���� �����մϴ�.
	 */
	virtual void Enter() = 0;


	/**
	 * @brief ������ �����ϴ�.
	 */
	virtual void Exit() = 0;


	/**
	 * @brief �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�.
	 *
	 * @return �� ��ȯ�� �����Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsDetectSwitch() const { return bDetectSwitch_; }


	/**
	 * @brief ���� ����� ���� ����ϴ�.
	 *
	 * @return ���� ����� ���� �����͸� ��ȯ�մϴ�.
	 */
	virtual IScene* GetLink() { return link_; }


	/**
	 * @brief ���� �����մϴ�.
	 *
	 * @param link ������ ���� �������Դϴ�.
	 */
	virtual void SetLink(IScene* link) { link_ = link; }


protected:
	/**
	 * @brief ���� �����ߴ��� Ȯ���մϴ�.
	 */
	bool bIsEnter_ = false;


	/**
	 * @brief �� ��ȯ�� �����Ǿ����� Ȯ���մϴ�.
	 */
	bool bDetectSwitch_ = false;


	/**
	 * @brief ����� ���Դϴ�.
	 */
	IScene* link_ = nullptr;
};