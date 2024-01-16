#pragma once

#include "Box3D.h"
#include "IObject.h"

class Material;
class StaticMesh;


/**
 * @brief �ٴ� ������Ʈ�Դϴ�.
 */
class Floor : public IObject
{
public:
	/**
	 * @brief �ٴ� ������Ʈ�� �⺻ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Floor() = default;


	/**
	 * @brief �ٴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Floor();


	/**
	 * @brief �ٴ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Floor);


	/**
	 * @brief �ٴ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief �ٴ� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �ٴ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ٴ� ������Ʈ�� �޽ø� ����ϴ�.
	 * 
	 * @return �ٴ� ������Ʈ�� �޽ø� ��ȯ�մϴ�.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief �ٴ� ������Ʈ�� ������ ����ϴ�.
	 * 
	 * @return �ٴ� ������Ʈ�� ������ ��ȯ�մϴ�.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief �ٴ� ������Ʈ�� ���� ��ġ�� ����ϴ�.
	 * 
	 * @return �ٴ� ������Ʈ�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief �ٴ� ������Ʈ�� ��� ������ ����ϴ�.
	 * 
	 * @return �ٴ� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	const Box3D& GetBoundingVolume() const { return boundingVolume_; }


private:
	/**
	 * @brief �ٴ� ������Ʈ�� ���� �޽��Դϴ�.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief �ٴ� ������Ʈ�� �����Դϴ�.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief �ٴ� ������Ʈ�� ���� ��ġ�Դϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief �ٴ� ������Ʈ�� ��� �����Դϴ�.
	 */
	Box3D boundingVolume_;
};