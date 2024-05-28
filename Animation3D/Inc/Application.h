#pragma once

#include "CrashModule.h"
#include "GameModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

class Camera;
class Character;
class GeometryRenderer3D;
class MeshRenderer3D;


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
	MeshRenderer3D* meshRenderer_ = nullptr;


	/**
	 * @brief ī�޶� ��ƼƼ�Դϴ�.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief ĳ���� ��ƼƼ�Դϴ�.
	 */
	Character* character_ = nullptr;
};