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
 * @brief 구 엔티티입니다.
 */
class Sphere3D : public IEntity
{
public:
	/**
	 * @brief 구 엔티티의 생성자입니다.
	 */
	Sphere3D();


	/**
	 * @brief 구 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Sphere3D();


	/**
	 * @brief 구 엔티티의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sphere3D);


	/**
	 * @brief 구 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief 구 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release();


	/**
	 * @brief 구 엔티티의 메시 리소스를 얻습니다.
	 * 
	 * @return 구 엔티티의 메시 리소스를 반환합니다.
	 */
	StaticMesh<VertexPositionNormalUv3D>* GetMesh() { return mesh_; }


	/**
	 * @brief 구 엔티티의 제질 리소스를 얻습니다.
	 * 
	 * @return 구 엔티티의 제질 리소스를 반환합니다.
	 */
	ITexture2D* GetMaterial() { return material_; }


	/**
	 * @brief 구의 트랜스폼을 얻습니다.
	 *
	 * @return 구의 트랜스폼을 반환합니다.
	 */
	Transform& GetTransform() { return transform_; }


	/**
	 * @brief 구의 트랜스폼을 얻습니다.
	 * 
	 * @return 구의 트랜스폼을 반환합니다.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief 구의 경계 영역을 얻습니다.
	 *
	 * @return 구의 경계 영역을 반환합니다.
	 */
	Sphere& GetBound() { return bound_; }


	/**
	 * @brief 구의 경계 영역을 얻습니다.
	 * 
	 * @return 구의 경계 영역을 반환합니다.
	 */
	const Sphere& GetBound() const { return bound_; }


private:
	/**
	 * @brief 구 엔티티의 메시 리소스입니다.
	 */
	StaticMesh<VertexPositionNormalUv3D>* mesh_ = nullptr;


	/**
	 * @brief 구 엔티티의 재질입니다.
	 */
	Checkboard* material_ = nullptr;


	/**
	 * @brief 구 엔티티의 트랜스폼입니다.
	 */
	Transform transform_;


	/**
	 * @brief 구 엔티티의 경계 영역입니다.
	 */
	Sphere bound_;
};