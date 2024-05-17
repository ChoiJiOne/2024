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
 * @brief ���� ����� ���ҽ� �������̽��Դϴ�.
 * 
 * @note
 * - ���� ��� ���� ���ҽ��� ���̴�, �ؽ�ó, ��Ʈ, �޽ð� �ֽ��ϴ�.
 * - �� �������̽����� ������ ������, �ʱ�ȭ�� �����ϴ�.
 * - �� �������̽��� ��ӹ޴� Ŭ������ ������ Ȥ�� �� ���� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
 */
class IResource
{
public:
	/**
	 * @brief ���ҽ� �������̽��� ����Ʈ �������Դϴ�.
	 */
	IResource() = default;


	/**
	 * @brief ���ҽ� �������̽��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���ҽ� �������̽��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~IResource() {}


	/**
	 * @brief ���ҽ� �������̽��� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IResource);


	/**
	 * @brief ���ҽ� �������̽� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ���ҽ� �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief ���ҽ��� �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 *
	 * @return ���ҽ��� �ʱ�ȭ�� ���� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsInitialized() const { return bIsInitialized_; }


protected:
	/**
	 * @brief ���ҽ��� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsInitialized_ = false;
};