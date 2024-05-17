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
 * @brief ���ø����̼��� �ʱ�ȭ/����/�����ϴ� Ŭ�����Դϴ�.
 */
class Application
{
public:
	/**
	 * @brief ���ø����̼��� �������Դϴ�.
	 */
	Application();


	/**
	 * @brief ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Application();


	/**
	 * @brief ���÷����̼��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Application);


	/**
	 * @brief ���ø����̼��� �ʱ�ȭ�մϴ�.
	 */
	void Init();


	/**
	 * @brief ���ø����̼��� �����մϴ�.
	 */
	void Run();


private:
	/**
	 * @brief ������Ʈ�� �����մϴ�.
	 * 
	 * @param deltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	void Update(float deltaSeconds);


	/**
	 * @brief ������ �� �غ� �����մϴ�.
	 */
	void PrepareForRendering();


	/**
	 * @brief �׸��⸦ �����մϴ�.
	 */
	void Render();


private:
	/**
	 * @brief 3D ���� ������ �������ϱ� ���� �������Դϴ�.
	 */
	GeometryRenderer3D* geometryRenderer_ = nullptr;


	/**
	 * @brief 3D �޽ø� �������ϱ� ���� �������Դϴ�.
	 */
	MeshRenderer* meshRenderer_ = nullptr;


	/**
	 * @brief 3D �޽��� �ƿ������� �׸��� �������Դϴ�.
	 */
	Shader* outlineRenderer_ = nullptr;


	/**
	 * @brief ī�޶� ��ƼƼ�Դϴ�.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief ��Ʈ�� ��ƼƼ�Դϴ�.
	 */
	Control* control_ = nullptr;


	/**
	 * @brief �� ��ƼƼ ����Դϴ�.
	 */
	std::list<Sphere3D*> spheres_;
};