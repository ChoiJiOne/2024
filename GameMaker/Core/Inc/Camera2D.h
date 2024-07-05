#pragma once

#include "GameMath.h"
#include "IEntity.h"


namespace GameMaker
{
/**
 * @brief 2D ī�޶� ��ƼƼ�� �������̽��Դϴ�.
 */
class Camera2D : public IEntity
{
public:
	/**
	 * @brief 2D ī�޶��� �⺻ �������Դϴ�.
	 */
	Camera2D() = default;


	/**
	 * @brief ī�޶� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Camera2D() {}


	/**
	 * @brief 2D ī�޶��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Camera2D);


	/**
	 * @brief ī�޶� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) = 0;


	/**
	 * @brief ī�޶� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief 2D ī�޶��� ���� �� �߽� ��ǥ�� ����ϴ�.
	 * 
	 * @return 2D ī�޶��� ���� �� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	const Vec2f& GetCenter() const { return center_; }


	/**
	 * @brief 2D ī�޶��� ���� ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return 2D ī�޶��� ���� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	const float& GetWidth() const { return width_; }


	/**
	 * @brief 2D ī�޶��� ���� ���� ũ�⸦ ����ϴ�.
	 * 
	 * @return 2D ī�޶��� ���� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	const float& GetHeight() const { return height_; }


	/**
	 * @brief 2D ī�޶��� ���� ���� ����� ����ϴ�.
	 * 
	 * @return 2D ī�޶��� ���� ���� ����� ��ȯ�մϴ�.
	 */
	const Mat4x4& GetOrtho() const { return ortho_; }


protected:
	/**
	 * @brief 2D ī�޶��� ���� �� �߽� ��ǥ�Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief 2D ī�޶��� ���� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 2D ī�޶��� ���� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 2D ī�޶��� ���� ���� ����Դϴ�.
	 */
	Mat4x4 ortho_;
};

}