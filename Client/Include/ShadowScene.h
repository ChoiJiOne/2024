#pragma once

#include "IScene.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "ShadowMap.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"


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
	Vector3f cameraPosition;

	Shader* depthShader;
	Shader* shadowShader;

	StaticMesh* floor;
	StaticMesh* cube;
	StaticMesh* sphere;

	ShadowMap* shadowMap;

	Vector3f lightPosition;

	const uint32_t SHADOW_WIDTH = 1024;
	const uint32_t SHADOW_HEIGHT = 1024;

	Window* window = nullptr;
};