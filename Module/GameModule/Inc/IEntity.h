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
 * @brief ��ƼƼ �������̽��Դϴ�.
 */
class IEntity
{
public:
	/**
	 * @brief ��ƼƼ �������̽��� ����Ʈ �������Դϴ�.
	 */
	IEntity() = default;


	/**
	 * @brief ��ƼƼ �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IEntity() {}


	/**
	 * @brief ��ƼƼ �������̽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IEntity);


	/**
	 * @brief ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 *
	 * @note
	 * - ��ƼƼ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 * - ��Ÿ �ð� ���� �ʴ����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;

	
	/**
	 * @brief ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ��ƼƼ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief ��ƼƼ�� �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 *
	 * @return ��ƼƼ�� �ʱ�ȭ�� ���� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsInitialized() const { return bIsInitialized_; }


protected:
	/**
	 * @brief ��ƼƼ�� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsInitialized_ = false;
};