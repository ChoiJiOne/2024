#pragma once

#include <vector>

#include "Collision.h"
#include "Mat.h"
#include "Transform.h"
#include "Vec.h"

#include "IEntity.h"

class StaticMesh;
class ITexture;


/**
 * @brief ���� ��ƼƼ�Դϴ�.
 */
class Coin : public IEntity
{
public:
	/**
	 * @brief ���� ��ƼƼ�� �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 */
	Coin(const Vec3f& position);


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
	const std::vector<StaticMesh*>& GetMeshes() const { return meshes_; }


	/**
	 * @brief ���� ��ƼƼ�� ��� ������ ����ϴ�.
	 * 
	 * @return ���� ��ƼƼ�� ��� ������ ��ȯ�մϴ�.
	 */
	const AABB& GetBoundingVolume() const { return aabb_; }


	/**
	 * @brief ���� ��ƼƼ�� Ʈ�������� ����ϴ�.
	 *
	 * @return ���� ��ƼƼ�� Ʈ������ �����ڸ� ��ȯ�մϴ�.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief ���� ��ƼƼ�� ���͸����� ����ϴ�.
	 *
	 * @return ���� ��ƼƼ�� ���͸����� ��ȯ�մϴ�.
	 */
	const ITexture* GetMaterial() const { return material_; }


private:
	/**
	 * @brief ���� ��ƼƼ�� ���� �޽� ����Դϴ�.
	 */
	std::vector<StaticMesh*> meshes_;


	/**
	 * @brief ������ ��� �����Դϴ�.
	 */
	AABB aabb_;


	/**
	 * @brief ���� ��ƼƼ�� Ʈ�������Դϴ�.
	 */
	Transform transform_;


	/**
	 * @brief ���� ��ƼƼ�� ���͸����Դϴ�.
	 */
	ITexture* material_ = nullptr;
};