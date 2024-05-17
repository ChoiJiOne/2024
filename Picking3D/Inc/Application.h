#pragma once

#include <list>

#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"
#include "IEntity.h"

class Camera;
class Control;
class GeometryRenderer3D;
class MeshRenderer;
class Sphere3D;
class Shader;


/**
 * @brief 어플리케이션을 초기화/실행/해제하는 클래스입니다.
 */
class Application
{
public:
	/**
	 * @brief 어플리케이션의 생성자입니다.
	 */
	Application();


	/**
	 * @brief 어플리케이션의 가상 소멸자입니다.
	 */
	virtual ~Application();


	/**
	 * @brief 어플레케이션의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Application);


	/**
	 * @brief 어플리케이션을 초기화합니다.
	 */
	void Init();


	/**
	 * @brief 어플리케이션을 실행합니다.
	 */
	void Run();


private:
	/**
	 * @brief 업데이트를 수행합니다.
	 * 
	 * @param deltaSeconds 초단위 델타 시간값입니다.
	 */
	void Update(float deltaSeconds);


	/**
	 * @brief 렌더링 전 준비를 수행합니다.
	 */
	void PrepareForRendering();


	/**
	 * @brief 그리기를 수행합니다.
	 */
	void Render();


private:
	/**
	 * @brief 3D 기하 도형을 렌더링하기 위한 렌더러입니다.
	 */
	GeometryRenderer3D* geometryRenderer_ = nullptr;


	/**
	 * @brief 3D 메시를 렌더링하기 위한 렌더러입니다.
	 */
	MeshRenderer* meshRenderer_ = nullptr;


	/**
	 * @brief 3D 메시의 아웃라인을 그리는 렌더러입니다.
	 */
	Shader* outlineRenderer_ = nullptr;


	/**
	 * @brief 카메라 엔티티입니다.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief 컨트롤 엔티티입니다.
	 */
	Control* control_ = nullptr;


	/**
	 * @brief 구 엔티티 목록입니다.
	 */
	std::list<Sphere3D*> spheres_;
};