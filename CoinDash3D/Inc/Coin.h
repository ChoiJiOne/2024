#pragma once

#include <vector>

#include "Collision.h"
#include "Mat.h"
#include "Transform.h"
#include "Vec.h"

#include "IEntity.h"

class Character;
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
	 * @param character ���ΰ� �浹 ���θ� Ȯ���� ĳ���� ��ƼƼ�Դϴ�.
	 */
	Coin(const Vec3f& position, Character* character);


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
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


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
	const AABB& GetAABB() const { return aabb_; }


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


	/**
	 * @brief �÷��̾ �� ������ �����ϰ� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return �÷��̾ �� ������ �����ϰ� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool HasCollectedCoin() const { return hasCollectedCoin_; }


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


	/**
	 * @brief ���ΰ� �浹 ���θ� Ȯ���� ĳ���� ��ƼƼ�Դϴ�.
	 */
	Character* character_ = nullptr;


	/**
	 * @brief �÷��̾ ������ �������� Ȯ���մϴ�.
	 */
	bool hasCollectedCoin_ = false;
};