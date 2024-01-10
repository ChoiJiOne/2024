#pragma once

#include "Camera3D.h"
#include "IScene.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "Material.h"
#include "ShadowMap.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"
#include "Light.h"


/**
 * @brief ��� ������ ���� ���� ���Դϴ�.
 */
class ShadowScene : public IScene
{
public:
	/**
	 * @brief �� �������Դϴ�.
	 */
	ShadowScene();


	/**
	 * @brief ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ShadowScene();


	/**
	 * @brief ���� ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowScene);


	/**
	 * @brief ���� �� �������� �����մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	Camera3D* camera;

	Shader* depthShader;
	Shader* light;

	StaticMesh* floor;
	StaticMesh* cube;
	StaticMesh* sphere;
	Material* material;

	// 1.
	ShadowMap* shadowMap0;

	Light* lightObject;
	
	const uint32_t SHADOW_WIDTH = 1024;
	const uint32_t SHADOW_HEIGHT = 1024;

	Window* window = nullptr;
};