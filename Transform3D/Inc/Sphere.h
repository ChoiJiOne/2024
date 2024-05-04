#pragma once

#include <imgui.h>

#include "Transform.h"
#include "StaticMesh.h"
#include "TileMap.h"
#include "Vertex3D.h"

#include "IEntity.h"

class MeshRenderer;
class Camera;


/**
 * @brief ��(Sphere) ��ƼƼ�Դϴ�.
 */
class Sphere : public IEntity
{
public:
	/**
	 * @brief ��(Sphere) ��ƼƼ�� �������Դϴ�.
	 *
	 * @param renderer ���� �������� �� ������ �������Դϴ�.
	 * @param camera ī�޶��Դϴ�.
	 */
	Sphere(MeshRenderer* renderer, Camera* camera);


	/**
	 * @brief ��(Sphere) ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Sphere();


	/**
	 * @brief ��(Sphere) ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sphere);


	/**
	 * @brief ��(Sphere) ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ��(Sphere) ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ��(Sphere) ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ImGui ������ �Ӽ��Դϴ�.
	 */
	ImGuiWindowFlags_ windowFlags_;


	/**
	 * @brief ImGui ���� ��ġ�Դϴ�.
	 */
	ImVec2 location_;


	/**
	 * @brief ImGui ���� ũ���Դϴ�.
	 */
	ImVec2 size_;


	/**
	 * @brief ���� �޽� ���ҽ��Դϴ�.
	 */
	StaticMesh<VertexPositionNormalUv3D>* mesh_ = nullptr;


	/**
	 * @brief ���� ������ Ÿ�ϸ��Դϴ�.
	 */
	TileMap* tileMap_ = nullptr;


	/**
	 * @brief ���� ���� �� ��ġ�Դϴ�.
	 */
	Vec3f position_ = Vec3f(0.0f, 0.0f, 0.0f);


	/**
	 * @brief ���� ȸ�� ���Դϴ�.
	 */
	Vec3f axis_ = Vec3f(0.0f, 0.0f, 0.0f);
	
	
	/**
	 * @brief ȸ�� ���� �߽����� ȸ���� ���� �����Դϴ�.
	 */
	float radian_ = 0.0f;


	/**
	 * @brief ���� ũ���Դϴ�.
	 */
	Vec3f scale_ = Vec3f(1.0f, 1.0f, 1.0f);


	/**
	 * @brief ���� Ʈ�������Դϴ�.
	 */
	Transform transform_;


	/**
	 * @brief �� ������ �� ������ �������Դϴ�.
	 */
	MeshRenderer* renderer_ = nullptr;


	/**
	 * @brief ī�޶��Դϴ�.
	 */
	Camera* camera_ = nullptr;
};