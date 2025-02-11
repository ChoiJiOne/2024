#pragma once

#include <array>

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

#include "IEntity.h"

class GeometryRenderer3D;
class MeshRenderer;
class Camera;


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
	 * @brief 3D 기하 도형을 렌더링하는 렌더러입니다.
	 */
	GeometryRenderer3D* geometryRenderer_ = nullptr;


	/**
	 * @brief 3D 메쉬를 렌더링하는 렌더러입니다.
	 */
	MeshRenderer* meshRenderer_ = nullptr;


	/**
	 * @brief 카메라 엔티티입니다.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief 어플리케이션 내의 엔티티입니다.
	 */
	std::array<IEntity*, 3> entities_;
};