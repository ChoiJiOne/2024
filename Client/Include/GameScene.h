#pragma once

#include "GameObject.h"
#include "IScene.h"
#include "LightShader.h"
#include "ShadowMap.h"
#include "ShadowShader.h"

#include "MovableCamera.h"
#include "StaticLight.h"


/**
 * @brief ���� �÷��� ���Դϴ�.
 */
class GameScene : public IScene
{
public:
	/**
	 * @brief ���� �÷��� ���� �������Դϴ�.
	 */
	GameScene();


	/**
	 * @brief ���� �÷��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameScene();


	/**
	 * @brief ���� �÷��� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameScene);


	/**
	 * @brief ���� �÷��� ���� �� �������� �����մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief �÷��̾ �����ϴ� ������Ʈ�� ����ٴϴ� ī�޶��Դϴ�.
	 */
	MovableCamera* camera_ = nullptr;


	/**
	 * @brief ���� ���� ���� ����Ʈ�Դϴ�.
	 */
	StaticLight* light_ = nullptr;


	/**
	 * @brief ���� ���� ������Ʈ ������ ������Ʈ���Դϴ�.
	 */
	std::vector<GameObject*> updateObjects_;


	/**
	 * @brief ���� ���� ������ ������ ������Ʈ���Դϴ�.
	 */
	std::vector<GameObject*> renderObjects_;


	/**
	 * @brief ���� �� ������ ���� ���� ���� ����� �ؽ�ó�Դϴ�.
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief �ε��� ���� ���� ũ���Դϴ�.
	 */
	const uint32_t SHADOW_WIDTH = 1024;


	/**
	 * @brief �ε��� ���� ���� ũ���Դϴ�.
	 */
	const uint32_t SHADOW_HEIGHT = 1024;


	/**
	 * @brief ���� �� ������ ���� ���� ���� �������ϴ� ���̴��Դϴ�.
	 */
	ShadowShader* shadowShader_ = nullptr;

	/**
	 * @brief ���� �� ������ ���� ������ ȿ���� �����ϴ� ���̴��Դϴ�.
	 */
	LightShader* lightShader_ = nullptr;
};