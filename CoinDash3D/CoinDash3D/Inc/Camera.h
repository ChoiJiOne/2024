#pragma once

#include "Camera3D.h"


/**
 * @brief ���� ���� ī�޶� ��ƼƼ�Դϴ�.
 */
class Camera : public GameMaker::Camera3D
{
public:
	/**
	 * @brief ī�޶��� ������ �����Դϴ�.
	 */
	enum class EMovement
	{
		FORWARD  = 0x00,
		BACKWARD = 0x01,
		LEFT     = 0x02,
		RIGHT    = 0x03,
	};


public:
	/**
	 * @brief ī�޶� ��ƼƼ�� �������Դϴ�.
	 */
	Camera();


	/**
	 * @brief ī�޶� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Camera();


	/**
	 * @brief ī�޶� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Camera);


	/**
	 * @brief ī�޶� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ī�޶� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief ��ũ���� �����ϴ� ���� ���� ����� ����ϴ�.
	 *
	 * @return ��ũ���� �����ϴ� ���� ���� ����� ��ȯ�մϴ�.
	 */
	const GameMaker::Mat4x4& GetScreenOrtho() const { return screenOrtho_; }


	/**
	 * @brief ī�޶� ��ƼƼ�� Ȱ��ȭ ���θ� �����մϴ�.
	 *
	 * @param active ī�޶� ��ƼƼ�� Ȱ��ȭ �����Դϴ�.
	 */
	void SetActive(bool active) { bIsActive_ = active; }


private:
	/**
	 * @brief ī�޶��� ���¸� ������Ʈ�մϴ�.
	 */
	void UpdateState();


private:
	/**
	 * @brief ��ũ���� �����ϴ� ���� ���� ����Դϴ�.
	 */
	GameMaker::Mat4x4 screenOrtho_;


	/**
	 * @brief ī�޶��� ������ �ӵ��Դϴ�.
	 */
	float speed_ = 2.5f;


	/**
	 * @brief Y�� ���Ϸ� ȸ�� �����Դϴ�.
	 */
	float yaw_ = 0.0f;


	/**
	 * @brief X�� ���Ϸ� ȸ�� �����Դϴ�.
	 */
	float pitch_ = 0.0f;


	/**
	 * @brief ī�޶� Ȱ��ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsActive_ = true;
};