#pragma once

#include "IGameFramework.h"


/**
 * @brief Ŭ���̾�Ʈ ���ø����̼��Դϴ�.
 */
class ClientApplication : public IGameFramework
{
public:
	/**
	 * @brief Ŭ���̾�Ʈ ���ø����̼��� ����Ʈ �������Դϴ�.
	 */
	ClientApplication() = default;


	/**
	 * @brief Ŭ���̾�Ʈ ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ClientApplication();


	/**
	 * @brief Ŭ���̾�Ʈ ���ø����̼��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ClientApplication);


	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 */
	virtual void Setup() override;


	/**
	 * @brief ���� �����ӿ�ũ ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� �����ӿ�ũ�� �����մϴ�.
	 */
	virtual void Run() override;


private:
	/**
	 * @brief Ŭ���̾�Ʈ ����Դϴ�.
	 */
	std::wstring clientPath_;


	/**
	 * @brief ���� Ÿ�̸��Դϴ�.
	 */
	GameTimer timer_;


	/**
	 * @brief �Ʒ��� ��� ������ ��� ������ ���� ��� �����Դϴ�.
	 */
	Matrix4x4f view_;
	Matrix4x4f projection_;
};