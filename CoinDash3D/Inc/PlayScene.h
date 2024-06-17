#pragma once

#include <list>

#include "IScene.h"

class Application; 
class DepthRenderer;
class GeometryRenderer2D;
class GeometryRenderer3D;
class MeshRenderer;
class PostEffectComposer;
class ShadowMap;
class TextRenderer;

class Button;
class Camera;
class Character;
class Coin;
class CoinSpawner;
class Floor;
class Light;
class MiniMap;
class StatusViewer;


/**
 * @brief ���� �÷��� ���Դϴ�.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief ���� �÷��� ���� �����Դϴ�.
	 */
	enum class EStatus
	{
		READY = 0x00,
		PLAY  = 0x01,
		PAUSE = 0x02,
		DONE  = 0x03,
	};


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


	/**
	 * @brief ���� ���� �����͸� �����մϴ�.
	 * 
	 * @param startScene ������ ���� ���� �������Դϴ�.
	 */
	void SetStartScene(IScene* startScene) { startScene_ = startScene; }


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
	 * @brief ��ó�� ȿ��(Grayscale, Blur, Fade ���)�� ������ �� ����մϴ�.
	 */
	PostEffectComposer* postEffectComposer_ = nullptr;


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� �������Դϴ�.
	 */
	TextRenderer* textRenderer_ = nullptr;


	/**
	 * @brief ���� ���� �������� �ε��� ���Դϴ�.
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	FrameBuffer* framebuffer_ = nullptr;


	/**
	 * @brief ũ�⿡ ���� ��Ʈ ���ҽ��Դϴ�.
	 */
	std::map<int32_t, TTFont*> fonts_;


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


	/**
	 * @brief ���� ���¸� ǥ���ϴ� ��ƼƼ�Դϴ�.
	 */
	StatusViewer* statusViewer_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	Button* resetButton_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	Button* quitButton_ = nullptr;


	/**
	 * @brief ���� ���Դϴ�.
	 */
	IScene* startScene_ = nullptr;


	/**
	 * @brief ���� ���� �÷��� ���� �����Դϴ�.
	 */
	EStatus status_ = EStatus::READY;
};