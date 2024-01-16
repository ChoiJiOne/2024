#pragma once

#include "Sphere3D.h"
#include "IObject.h"
#include "Transform.h"

class Material;
class StaticMesh;


/**
 * @brief �÷��̾ ���� ������ ������Ʈ�Դϴ�.
 */
class Player : public IObject
{
public:
	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Player() = default;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Player();


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Player);


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� �޽ø� ����ϴ�.
	 *
	 * @return �÷��̾ ���� ������ ������Ʈ�� �޽ø� ��ȯ�մϴ�.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ������ ����ϴ�.
	 *
	 * @return �÷��̾ ���� ������ ������Ʈ�� ������ ��ȯ�մϴ�.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� Ʈ�������� ����ϴ�.
	 *
	 * @return �÷��̾ ���� ������ ������Ʈ�� Ʈ�������� ��ȯ�մϴ�.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ��� ������ ����ϴ�.
	 *
	 * @return �÷��̾ ���� ������ ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	const Sphere3D& GetBoundingVolume() const { return boundingVolume_; }


private:
	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ���� �޽��Դϴ�.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� �����Դϴ�.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� Ʈ�������Դϴ�.
	 */
	Transform transform_;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�� ��� �����Դϴ�.
	 */
	Sphere3D boundingVolume_;
};