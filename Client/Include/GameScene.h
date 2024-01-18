#pragma once

#include <array>

#include "GameObject.h"
#include "IScene.h"
#include "LightShader.h"
#include "Skybox.h"
#include "ShadowMap.h"
#include "ShadowShader.h"

#include "Bullet.h"
#include "BulletSpawner.h"
#include "EastWall.h"
#include "Floor.h"
#include "MovableCamera.h"
#include "NorthWall.h"
#include "Player.h"
#include "SouthWall.h"
#include "StaticLight.h"
#include "WestWall.h"


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
	 * @brief ���� ���� ���ҽ��� �ε��մϴ�.
	 */
	void LoadResources();


	/**
	 * @brief ���� ���� ������Ʈ�� �ε��մϴ�.
	 */
	void LoadObjects();
	

private:
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


	/**
	 * @brief �÷��̾ �����ϴ� ������Ʈ�� ����ٴϴ� ī�޶��Դϴ�.
	 */
	MovableCamera* camera_ = nullptr;


	/**
	 * @brief ���� ���� ���� ����Ʈ�Դϴ�.
	 */
	StaticLight* light_ = nullptr;


	/**
	 * @brief �÷��̾ ���� ������ ������Ʈ�Դϴ�.
	 */
	Player* player_ = nullptr;


	/**
	 * @brief �ٴ� ������Ʈ�Դϴ�.
	 */
	Floor* floor_ = nullptr;


	/**
	 * @brief �÷��̾ �ٶ󺸴� ���� ������ ���� ���Դϴ�.
	 */
	NorthWall* northWall_ = nullptr;

	
	/**
	 * @brief �÷��̾ �ٶ󺸴� ���� ������ ���� ���Դϴ�.
	 */
	SouthWall* southWall_ = nullptr;


	/**
	 * @brief �÷��̾ �ٶ󺸴� ���� ������ ���� ���Դϴ�.
	 */
	WestWall* westWall_ = nullptr;


	/**
	 * @brief �÷��̾ �ٶ󺸴� ���� ������ ���� ���Դϴ�.
	 */
	EastWall* eastWall_ = nullptr;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�Դϴ�.
	 */
	BulletSpawner* bulletSpawner0_ = nullptr;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�Դϴ�.
	 */
	BulletSpawner* bulletSpawner1_ = nullptr;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�Դϴ�.
	 */
	BulletSpawner* bulletSpawner2_ = nullptr;


	/**
	 * @brief �÷��̾ ���ؾ� �� �Ѿ��� �����ϴ� ������Ʈ�Դϴ�.
	 */
	BulletSpawner* bulletSpawner3_ = nullptr;


	/**
	 * @brief ���� ���� ������Ʈ ������ ������Ʈ���Դϴ�.
	 */
	std::array<GameObject*, 10> updateObjects_;


	/**
	 * @brief ���� ���� ������ ������ ������Ʈ���Դϴ�.
	 */
	std::array<GameObject*, 10> renderObjects_;
};