#pragma once

#include <list>


#include "IScene.h"

class Application; 
class DepthRenderer;
class GeometryRenderer2D;
class GeometryRenderer3D;
class MeshRenderer;
class ShadowMap;
class TextRenderer;

class Camera;
class Character;
class Coin;
class CoinSpawner;
class Floor;
class Light;
class MiniMap;


/**
 * @brief ���� �÷��� ���Դϴ�.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief ���� �÷��� ���� �������Դϴ�.
	 * 
	 * @param app ���� �÷��� ���� ������ ���ø����̼� Ŭ�����Դϴ�.
	 */
	PlayScene(Application* app);


	/**
	 * @brief ���� �÷��� ���� ���� �Ҹ����Դϴ�.
	 */
	PlayScene() {}


	/**
	 * @brief ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� �����մϴ�.
	 */
	virtual void Enter() override;


	/**
	 * @brief ������ �����ϴ�.
	 */
	virtual void Exit() override;


private:
	/**
	 * @brief ��ü ������ ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	void Update(float deltaSeconds);


	/**
	 * @brief ������ �غ� �մϴ�.
	 */
	void PrepareForRendering();


	/**
	 * @brief �� �������� �����մϴ�.
	 */
	void Render();


	/**
	 * @brief ���� �� �������� �����մϴ�.
	 */
	void DepthPass();


	/**
	 * @brief �� �������� �����մϴ�.
	 */
	void RenderPass();


private:
	/**
	 * @brief 3D ���� ���� ���� �������ϴ� �������Դϴ�.
	 */
	DepthRenderer* depthRenderer_ = nullptr;


	/**
	 * @brief 2D ���� ������ �������ϴ� �������Դϴ�.
	 */
	GeometryRenderer2D* geometryRenderer2D_ = nullptr;


	/**
	 * @brief 3D ���� ������ �������ϴ� �������Դϴ�.
	 */
	GeometryRenderer3D* geometryRenderer3D_ = nullptr;


	/**
	 * @brief 3D �޽��� �������ϴ� �������Դϴ�.
	 */
	MeshRenderer* meshRenderer_ = nullptr;


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� �������Դϴ�.
	 */
	TextRenderer* textRenderer_ = nullptr;


	/**
	 * @brief ���� ���� �������� �ε��� ���Դϴ�.
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief ī�޶� ��ƼƼ�Դϴ�.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief �÷��̾ �����ϴ� ĳ�����Դϴ�.
	 */
	Character* character_ = nullptr;


	/**
	 * @brief �ٴ� ��ƼƼ�Դϴ�.
	 */
	Floor* floor_ = nullptr;


	/**
	 * @brief ����Ʈ ��ƼƼ�Դϴ�.
	 */
	Light* light_ = nullptr;


	/**
	 * @brief ���� ��ƼƼ�Դϴ�.
	 */
	std::list<Coin*> coins_;


	/**
	 * @brief ������ �����ϴ� ��ƼƼ�Դϴ�.
	 */
	CoinSpawner* coinSpawner_ = nullptr;


	/**
	 * @brief �̴ϸ� ��ƼƼ�Դϴ�.
	 */
	MiniMap* miniMap_ = nullptr;
};