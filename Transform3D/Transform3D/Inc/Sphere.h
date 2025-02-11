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
 * @brief 구(Sphere) 엔티티입니다.
 */
class Sphere : public IEntity
{
public:
	/**
	 * @brief 구(Sphere) 엔티티의 생성자입니다.
	 *
	 * @param renderer 구를 렌더링할 때 참조할 렌더러입니다.
	 * @param camera 카메라입니다.
	 */
	Sphere(MeshRenderer* renderer, Camera* camera);


	/**
	 * @brief 구(Sphere) 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Sphere();


	/**
	 * @brief 구(Sphere) 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sphere);


	/**
	 * @brief 구(Sphere) 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 구(Sphere) 엔티티를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 구(Sphere) 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ImGui 윈도우 속성입니다.
	 */
	ImGuiWindowFlags_ windowFlags_;


	/**
	 * @brief ImGui 내의 위치입니다.
	 */
	ImVec2 location_;


	/**
	 * @brief ImGui 내의 크기입니다.
	 */
	ImVec2 size_;


	/**
	 * @brief 구의 메시 리소스입니다.
	 */
	StaticMesh<VertexPositionNormalUv3D>* mesh_ = nullptr;


	/**
	 * @brief 구에 매핑할 타일맵입니다.
	 */
	TileMap* tileMap_ = nullptr;


	/**
	 * @brief 구의 월드 상 위치입니다.
	 */
	Vec3f position_ = Vec3f(0.0f, 0.0f, 0.0f);


	/**
	 * @brief 구의 회전 축입니다.
	 */
	Vec3f axis_ = Vec3f(0.0f, 0.0f, 0.0f);
	
	
	/**
	 * @brief 회전 축을 중심으로 회전할 라디안 각도입니다.
	 */
	float radian_ = 0.0f;


	/**
	 * @brief 구의 크기입니다.
	 */
	Vec3f scale_ = Vec3f(1.0f, 1.0f, 1.0f);


	/**
	 * @brief 구의 트랜스폼입니다.
	 */
	Transform transform_;


	/**
	 * @brief 구 렌더링 시 참조할 렌더러입니다.
	 */
	MeshRenderer* renderer_ = nullptr;


	/**
	 * @brief 카메라입니다.
	 */
	Camera* camera_ = nullptr;
};