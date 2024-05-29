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
 * @brief �ٴ� ��ƼƼ�Դϴ�.
 */
class Floor : public IEntity
{
public:
	/**
	 * @brief �ٴ� ��ƼƼ�� �������Դϴ�.
	 */
	Floor();


	/**
	 * @brief �ٴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Floor();


	/**
	 * @brief �ٴ� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Floor);


	/**
	 * @brief �ٴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief �ٴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief �ٴ� ��ƼƼ�� ���� �޽� ����� ����ϴ�.
	 *
	 * @return �ٴ� ��ƼƼ�� ���� �޽� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	std::vector<StaticMesh*>& GetMeshes() { return meshes_; }


	/**
	 * @brief �ٴ� ��ƼƼ�� Ʈ������ ����� ����ϴ�.
	 *
	 * @return �ٴ� ��ƼƼ�� Ʈ������ ��� �����ڸ� ��ȯ�մϴ�.
	 */
	std::vector<Transform>& GetTransforms() { return transforms_; }


	/**
	 * @brief �ٴ� ��ƼƼ�� ���͸����� ����ϴ�.
	 *
	 * @return �ٴ� ��ƼƼ�� ���͸����� ��ȯ�մϴ�.
	 */
	ITexture2D* GetMaterial() { return material_; }


private:
	/**
	 * @brief �ٴ� ��ƼƼ�� ���� �޽� ����Դϴ�.
	 */
	std::vector<StaticMesh*> meshes_;


	/**
	 * @brief �ٴ� ��ƼƼ�� Ʈ�������Դϴ�.
	 */
	std::vector<Transform> transforms_;


	/**
	 * @brief �ٴ� ��ƼƼ�� ���͸����Դϴ�.
	 */
	ITexture2D* material_ = nullptr;
};