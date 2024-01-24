#pragma once

#include "IObject.h"
#include "IShape3D.h"
#include "Material.h"
#include "StaticMesh.h"
#include "Transform.h"


/**
 * @brief ���� ������Ʈ�Դϴ�.
 */
class GameObject : public IObject
{
public:
	/**
	 * @brief ���� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	GameObject() = default;


	/**
	 * @brief ���� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameObject() {}


	/**
	 * @brief ���� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameObject);


	/**
	 * @brief ���� ������Ʈ�� �޽ø� ����ϴ�.
	 *
	 * @return ���� ������Ʈ�� �޽ø� ��ȯ�մϴ�.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief ���� ������Ʈ�� ������ ����ϴ�.
	 *
	 * @return ���� ������Ʈ�� ������ ��ȯ�մϴ�.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief ���� ������Ʈ�� Ʈ�������� ����ϴ�.
	 *
	 * @return ���� ������Ʈ�� Ʈ�������� ��ȯ�մϴ�.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief ���� ������Ʈ�� ��� ������ ����ϴ�.
	 * 
	 * @return ���� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 * 
	 * @note �� �޼���� ���� ���� �Լ��� ���� �޼��忡�� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual const IShape3D* GetBoundingVolume() const = 0;


	/**
	 * @brief �ٸ� ���� ������Ʈ���� �浹 ���θ� Ȯ���մϴ�.
	 * 
	 * @param object �浹 ���θ� �˻��� �ٸ� ���� ������Ʈ�Դϴ�.
	 */
	bool IsCollision(const GameObject* object) const;


protected:
	/**
	 * @brief ���� ������Ʈ�� �޽��Դϴ�.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief ���� ������Ʈ�� ����(Material)�Դϴ�.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief ���� ������Ʈ�� Ʈ�������Դϴ�.
	 */
	Transform transform_;
};