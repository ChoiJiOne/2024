#pragma once

#include <vector>

#include "Collision.h"
#include "Mat.h"
#include "Transform.h"
#include "Vec.h"

#include "IEntity.h"

class StaticMesh;
class ITexture2D;


/**
 * @brief ���� ��ƼƼ�Դϴ�.
 */
class Coin : public IEntity
{
public:
	/**
	 * @brief ���� ��ƼƼ�� �������Դϴ�.
	 */
	Coin();


	/**
	 * @brief ���� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Coin();


	/**
	 * @brief ���� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Coin);


	/**
	 * @brief ���� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ���� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief ���� ��ƼƼ�� ���� �޽ø� ����ϴ�.
	 *
	 * @return ���� ��ƼƼ�� ���� �޽ø� ��ȯ�մϴ�.
	 */
	StaticMesh* GetMesh() { return mesh_; }


	/**
	 * @brief ���� ��ƼƼ�� Ʈ�������� ����ϴ�.
	 *
	 * @return ���� ��ƼƼ�� Ʈ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Transform& GetTransform() { return transform_; }


	/**
	 * @brief ���� ��ƼƼ�� ���͸����� ����ϴ�.
	 *
	 * @return ���� ��ƼƼ�� ���͸����� ��ȯ�մϴ�.
	 */
	ITexture2D* GetMaterial() { return material_; }


private:
	/**
	 * @brief ���� ��ƼƼ�� ���� �޽� ����Դϴ�.
	 */
	StaticMesh* mesh_;


	/**
	 * @brief ���� ��ƼƼ�� Ʈ�������Դϴ�.
	 */
	Transform transform_;


	/**
	 * @brief ���� ��ƼƼ�� ���͸����Դϴ�.
	 */
	ITexture2D* material_ = nullptr;
};