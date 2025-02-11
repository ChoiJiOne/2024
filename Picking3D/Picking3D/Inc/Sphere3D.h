#pragma once

#include "Collision.h"
#include "Checkboard.h"
#include "ITexture2D.h"
#include "Mat.h"
#include "StaticMesh.h"
#include "Transform.h"
#include "Vertex3D.h"

#include "IEntity.h"


/**
 * @brief �� ��ƼƼ�Դϴ�.
 */
class Sphere3D : public IEntity
{
public:
	/**
	 * @brief �� ��ƼƼ�� �������Դϴ�.
	 */
	Sphere3D();


	/**
	 * @brief �� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Sphere3D();


	/**
	 * @brief �� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sphere3D);


	/**
	 * @brief �� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief �� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief �� ��ƼƼ�� �޽� ���ҽ��� ����ϴ�.
	 * 
	 * @return �� ��ƼƼ�� �޽� ���ҽ��� ��ȯ�մϴ�.
	 */
	StaticMesh<VertexPositionNormalUv3D>* GetMesh() { return mesh_; }


	/**
	 * @brief �� ��ƼƼ�� ���� ���ҽ��� ����ϴ�.
	 * 
	 * @return �� ��ƼƼ�� ���� ���ҽ��� ��ȯ�մϴ�.
	 */
	ITexture2D* GetMaterial() { return material_; }


	/**
	 * @brief ���� Ʈ�������� ����ϴ�.
	 *
	 * @return ���� Ʈ�������� ��ȯ�մϴ�.
	 */
	Transform& GetTransform() { return transform_; }


	/**
	 * @brief ���� Ʈ�������� ����ϴ�.
	 * 
	 * @return ���� Ʈ�������� ��ȯ�մϴ�.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief ���� ��� ������ ����ϴ�.
	 *
	 * @return ���� ��� ������ ��ȯ�մϴ�.
	 */
	Sphere& GetBound() { return bound_; }


	/**
	 * @brief ���� ��� ������ ����ϴ�.
	 * 
	 * @return ���� ��� ������ ��ȯ�մϴ�.
	 */
	const Sphere& GetBound() const { return bound_; }


private:
	/**
	 * @brief �� ��ƼƼ�� �޽� ���ҽ��Դϴ�.
	 */
	StaticMesh<VertexPositionNormalUv3D>* mesh_ = nullptr;


	/**
	 * @brief �� ��ƼƼ�� �����Դϴ�.
	 */
	Checkboard* material_ = nullptr;


	/**
	 * @brief �� ��ƼƼ�� Ʈ�������Դϴ�.
	 */
	Transform transform_;


	/**
	 * @brief �� ��ƼƼ�� ��� �����Դϴ�.
	 */
	Sphere bound_;
};