#pragma once

#include <array>
#include <list>

#include <imgui.h>

#include "IEntity.h"

class Camera;
class Sphere3D;


/**
 * @brief 각종 속성을 제어하는 컨트롤 엔티티입니다.
 */
class Control : public IEntity
{
public:
	/**
	 * @brief 각종 속성을 제어하는 컨트롤 엔티티의 생성자입니다.
	 * 
	 * @param camera 카메라 엔티티의 포인터입니다.
	 * @param spheres 구 엔티티 목록입니다.
	 */
	Control(Camera* camera, std::list<Sphere3D*>& spheres);


	/**
	 * @brief 각종 속성을 제어하는 컨트롤 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Control();


	/**
	 * @brief 각종 속성을 제어하는 컨트롤 엔티티의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Control);


	/**
	 * @brief 각종 속성을 제어하는 컨트롤 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief 각종 속성을 제어하는 컨트롤 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release();


	/**
	 * @brief 현재 선택 중인 구를 얻습니다.
	 * 
	 * @return 현재 선택 중인 구를 반환합니다.
	 */
	Sphere3D* GetPickSphere() { return pickSphere_; }


private:
	/**
	 * @brief 선택된 구 엔티티를 얻습니다.
	 * 
	 * @return 선택된 구 엔티티의 포인터를 반환합니다.
	 */
	Sphere3D* GetPickingSphere3D();


private:
	/**
	 * @brief 컨트롤 엔티티의 UI 위치입니다.
	 */
	ImVec2 location_;


	/**
	 * @brief 컨트롤 엔티티의 UI 크기입니다.
	 */
	ImVec2 size_;


	/**
	 * @brief 컨트롤 엔티티의 UI 옵션 플래그입니다.
	 */
	ImGuiWindowFlags flags_;


	/**
	 * @brief 퍼포먼스 측정을 위한 FPS 값 목록의 최댓값입니다.
	 */
	static const uint32_t MAX_FPS_CACHE_SIZE = 2000;


	/**
	 * @brief 현재 FPS 인덱스입니다.
	 */
	int32_t currentFPS_ = 0;


	/**
	 * @brief 퍼포먼스 측정을 위한 FPS 값 목록입니다.
	 */
	std::array<float, MAX_FPS_CACHE_SIZE> calculateFPSs_ = {0.0f,};


	/**
	 * @brief FPS의 평균값입니다.
	 */
	float averageFPS_ = 0.0f;


	/**
	 * @brief 컨트롤 엔티티의 대상이 되는 카메라입니다.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief 현재 선택 중인 구 엔티티입니다.
	 */
	Sphere3D* pickSphere_ = nullptr;


	/**
	 * @brief 생성할 수 있는 최대 엔티티의 수입니다.
	 */
	static const uint32_t MAX_CREATE_ENTITY = 200;


	/**
	 * @brief 구 엔티티 목록입니다.
	 */
	std::list<Sphere3D*>& spheres_;
};

