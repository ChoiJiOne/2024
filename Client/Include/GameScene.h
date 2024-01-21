#pragma once

#include <array>
#include <list>
#include <functional>

#include "Framebuffer.h"
#include "GameObject.h"
#include "IScene.h"
#include "PostEffectShader.h"
#include "LightShader.h"
#include "UIMouseButton.h"
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
#include "UIBoard.h"
#include "WestWall.h"


/**
 * @brief ���� �÷��� ���Դϴ�.
 */
class GameScene : public IScene
{
public:
	/**
	 * @brief ���� �÷��� ���� �����Դϴ�.
	 */
	enum class ESceneState : int32_t
	{
		Ready = 0x00, // ���� �÷��� �غ� �����Դϴ�.
		Play  = 0x01, // ���� �÷��� �����Դϴ�.
		Pause = 0x02, // ���� �ߴ� �����Դϴ�.
		Done  = 0x03, // ���� ���� �����Դϴ�.
	};


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


	/**
	 * @brief ���� �÷��� ���� �����մϴ�.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief ���� �÷��� ������ �����ϴ�.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief ������ ���� ���� �̺�Ʈ�� �����մϴ�.
	 *
	 * @param loopQuitEvent ������ ���� ���� ���� �̺�Ʈ�Դϴ�.
	 */
	void SetLoopQuitEvent(const std::function<void()>& loopQuitEvent) { loopQuitEvent_ = loopQuitEvent; }


private:
	/**
	 * @brief ���� ���� ���ҽ��� �ε��մϴ�.
	 */
	void LoadResources();


	/**
	 * @brief ���� ���� ������Ʈ�� �ε��մϴ�.
	 */
	void LoadObjects();


	/**
	 * @brief �� ���� ������Ʈ���� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	void UpdateScene(float deltaSeconds);


	/**
	 * @brief ���� ���� �������մϴ�.
	 */
	void RenderDepthScene();


	/**
	 * @brief ���� �������մϴ�.
	 */
	void RenderScene();
	

private:
	/**
	 * @brief ���� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;


	/**
	 * @brief ���� �÷��� ���� �����Դϴ�.
	 */
	ESceneState sceneState_ = ESceneState::Ready;


	/**
	 * @brief �÷��̾�� �Ѿ��� �浹�Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsCollisionToPlayer_ = false;


	/**
	 * @brief ũ�Ⱑ 32�� ��Ʈ ���ҽ��Դϴ�.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief ���� �� ������ ���� ���� ���� ����� �ؽ�ó�Դϴ�.
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief ��ó�� ȿ���� �����ϱ� ���� ������ �����Դϴ�.
	 */
	Framebuffer* framebuffer_ = nullptr;


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
	 * @brief ��ó�� ȿ���� �����ϱ� ���� �׷��� ������ ���̴��Դϴ�.
	 */
	PostEffectShader* grayscaleEffectShader_ = nullptr;

	
	/**
	 * @brief ��ó�� ȿ���� �����ϱ� ���� ���̵� ȿ�� ���̴��Դϴ�.
	 */
	PostEffectShader* fadeEffectShader_ = nullptr;


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
	 * @brief ���� ���� ������ ������ ������Ʈ���Դϴ�.
	 */
	std::array<GameObject*, 10> renderObjects_;


	/**
	 * @brief ���� ���� �Ѿ� ������Ʈ�Դϴ�.
	 */
	std::list<Bullet*> bullets_;


	/**
	 * @brief ���� ���� ������ �Ѿ� ������Ʈ ���Դϴ�.
	 */
	uint32_t countOfbullet_ = 0;


	/**
	 * @brief �Ѿ� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<bool(Bullet*)> bulletRemoveEvent_;


	/**
	 * @brief �÷��̾��� �÷��� ������ ǥ���ϴ� UI�Դϴ�.
	 */
	UIBoard* board_ = nullptr;


	/**
	 * @brief ���̵� �� ����� ���� �ð����Դϴ�.
	 */
	float stepTime_ = 0.0f;


	/**
	 * @brief ���̵� �� �ð��Դϴ�.
	 */
	float fadeInStepTime_ = 1.0f;


	/**
	 * @brief ������ ������ ��� �÷����ϴ� ��ư�Դϴ�.
	 */
	UIMouseButton* continueButton_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	UIMouseButton* resetButton_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	UIMouseButton* quitButton_ = nullptr;
};