#pragma once

#include "GameMath.h"
#include "IEntity.h"


/**
 * @brief ���� ���� ī�޶� ��ƼƼ�Դϴ�.
 */
class Camera : public GameMaker::IEntity
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
	 * @brief �þ� ����� ����ϴ�.
	 *
	 * @return �þ� ����� ��ȯ�մϴ�.
	 */
	const GameMaker::Mat4x4& GetView() const { return view_; }


	/**
	 * @brief ���� ����� ����ϴ�.
	 *
	 * @return ���� ����� ��ȯ�մϴ�.
	 */
	const GameMaker::Mat4x4& GetProjection() const { return projection_; }


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
	 * @brief ī�޶��� ���� �� ��ġ�Դϴ�.
	 */
	GameMaker::Vec3f eyePosition_;


	/**
	 * @brief ī�޶��� �����Դϴ�.
	 */
	GameMaker::Vec3f eyeDirection_;


	/**
	 * @brief ī�޶��� �� �����Դϴ�.
	 */
	GameMaker::Vec3f upDirection_;


	/**
	 * @brief ī�޶��� ������ �����Դϴ�.
	 */
	GameMaker::Vec3f rightDirection_;


	/**
	 * @brief ���� ���� ī�޶� �� �����Դϴ�.
	 */
	GameMaker::Vec3f worldUpDirection_ = GameMaker::Vec3f(0.0f, 1.0f, 0.0f);


	/**
	 * @brief ����� ���� �ʵ� ����(����)�Դϴ�.
	 */
	float fov_ = 0.0f;


	/**
	 * @brief �� ���� X:Y�� ���� ���� �����Դϴ�.
	 */
	float aspectRatio_ = 0.0f;


	/**
	 * @brief ����� Ŭ���� �������� �Ÿ��Դϴ�. 0���� Ŀ�� �մϴ�.
	 */
	float nearZ_ = 0.0f;


	/**
	 * @brief ���Ÿ� Ŭ���� �������� �Ÿ��Դϴ�. 0���� Ŀ�� �մϴ�.
	 */
	float farZ_ = 0.0f;


	/**
	 * @brief �� ����Դϴ�.
	 */
	GameMaker::Mat4x4 view_;


	/**
	 * @brief ���� ����Դϴ�.
	 *
	 * @note ���� ��������� �ƴ� ���� ���� ����Դϴ�.
	 */
	GameMaker::Mat4x4 projection_;


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