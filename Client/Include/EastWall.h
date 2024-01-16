#pragma once

#include "Box3D.h"
#include "IObject.h"

class Material;
class StaticMesh;


/**
 * @brief ���� �� ������Ʈ�Դϴ�.
 */
class EastWall : public IObject
{
public:
	/**
	 * @brief ���� �� ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	EastWall() = default;


	/**
	 * @brief ���� �� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~EastWall();


	/**
	 * @brief ���� �� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(EastWall);


	/**
	 * @brief ���� �� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� �� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� �� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� �� ������Ʈ�� �޽ø� ����ϴ�.
	 *
	 * @return ���� �� ������Ʈ�� �޽ø� ��ȯ�մϴ�.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief ���� �� ������Ʈ�� ������ ����ϴ�.
	 *
	 * @return ���� �� ������Ʈ�� ������ ��ȯ�մϴ�.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief ���� �� ������Ʈ�� ���� ��ġ�� ����ϴ�.
	 *
	 * @return ���� �� ������Ʈ�� ��ġ�� ��ȯ�մϴ�.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief ���� �� ������Ʈ�� ��� ������ ����ϴ�.
	 *
	 * @return ���� �� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	const Box3D& GetBoundingVolume() const { return boundingVolume_; }


private:
	/**
	 * @brief ���� �� ������Ʈ�� ���� �޽��Դϴ�.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief ���� �� ������Ʈ�� �����Դϴ�.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief ���� �� ������Ʈ�� ���� ��ġ�Դϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief ���� �� ������Ʈ�� ��� �����Դϴ�.
	 */
	Box3D boundingVolume_;
};