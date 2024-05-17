#pragma once

#include <array>
#include <list>

#include <imgui.h>

#include "IEntity.h"

class Camera;
class Sphere3D;


/**
 * @brief ���� �Ӽ��� �����ϴ� ��Ʈ�� ��ƼƼ�Դϴ�.
 */
class Control : public IEntity
{
public:
	/**
	 * @brief ���� �Ӽ��� �����ϴ� ��Ʈ�� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param camera ī�޶� ��ƼƼ�� �������Դϴ�.
	 * @param spheres �� ��ƼƼ ����Դϴ�.
	 */
	Control(Camera* camera, std::list<Sphere3D*>& spheres);


	/**
	 * @brief ���� �Ӽ��� �����ϴ� ��Ʈ�� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Control();


	/**
	 * @brief ���� �Ӽ��� �����ϴ� ��Ʈ�� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Control);


	/**
	 * @brief ���� �Ӽ��� �����ϴ� ��Ʈ�� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ���� �Ӽ��� �����ϴ� ��Ʈ�� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


private:
	/**
	 * @brief ��Ʈ�� ��ƼƼ�� UI ��ġ�Դϴ�.
	 */
	ImVec2 location_;


	/**
	 * @brief ��Ʈ�� ��ƼƼ�� UI ũ���Դϴ�.
	 */
	ImVec2 size_;


	/**
	 * @brief ��Ʈ�� ��ƼƼ�� UI �ɼ� �÷����Դϴ�.
	 */
	ImGuiWindowFlags flags_;


	/**
	 * @brief �����ս� ������ ���� FPS �� ����� �ִ��Դϴ�.
	 */
	static const uint32_t MAX_FPS_CACHE_SIZE = 2000;


	/**
	 * @brief ���� FPS �ε����Դϴ�.
	 */
	int32_t currentFPS_ = 0;


	/**
	 * @brief �����ս� ������ ���� FPS �� ����Դϴ�.
	 */
	std::array<float, MAX_FPS_CACHE_SIZE> calculateFPSs_ = {0.0f,};


	/**
	 * @brief FPS�� ��հ��Դϴ�.
	 */
	float averageFPS_ = 0.0f;


	/**
	 * @brief ��Ʈ�� ��ƼƼ�� ����� �Ǵ� ī�޶��Դϴ�.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief ������ �� �ִ� �ִ� ��ƼƼ�� ���Դϴ�.
	 */
	static const uint32_t MAX_CREATE_ENTITY = 200;


	/**
	 * @brief �� ��ƼƼ ����Դϴ�.
	 */
	std::list<Sphere3D*>& spheres_;
};

