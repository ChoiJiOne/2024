#pragma once

#include <map>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"

/** Ŭ���� ���� �����Դϴ�. */
class Background;
class Camera2D;
class CoinCollector;
class FadeEffector;
class FrameBuffer;
class GamePlayRecorder;
class KeyEventTrigger;
class Player;
class Playground;
class PostProcessor;
class UICamera;


/** ���� �÷��� ���Դϴ�. */
class GamePlayScene : public IGameScene
{
public:
	GamePlayScene();
	virtual ~GamePlayScene();

	DISALLOW_COPY_AND_ASSIGN(GamePlayScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

	/** 
	 * ��ƼƼ�� �߰��մϴ�. 
	 * - �߰��ϴ� ��ƼƼ�� ���������� �ʽ��ϴ�. 
	 * - ���� �������� �켱���� ���� �����ϴ�. 
	 */
	void AddEntity(IEntity* entity, int32_t updateOrder);

	/** 
	 * ��ƼƼ�� �߰��մϴ�. 
	 * - �߰��ϴ� ��ƼƼ�� �������� �����մϴ�. 
	 * - ���� �������� �켱���� ���� �����ϴ�. 
	 */
	void AddEntity(IEntity2D* entity, int32_t updateOrder, int32_t renderOrder);

	/** ��ƼƼ�� �����մϴ�. */
	void RemoveEntity(IEntity* entity);

private:
	/** ���� ���� ������ ���� �÷��� �� ���ο� ������ �� �ֵ��� �����մϴ�. */
	friend class GamePauseScene;

	/** Tick�� �����ϱ� ���� ȣ���մϴ�. */
	void PreTick(float deltaSeconds);

	/** ���� �÷��� ���� �ʱ�ȭ�մϴ�. */
	void Initialize();

	/** ���� �÷��� ���� �ʱ�ȭ�� �����մϴ�. */
	void UnInitialize();

	/** ���� �÷��� ���� ��ƼƼ�� �ε��մϴ�. */
	void LoadEntity();

	/** ���� �÷��� ���� ��ƼƼ�� �ε� �����մϴ�. */
	void UnloadEntity();

private:
	/** ������Ʈ�� ��ƼƼ�Դϴ�. */
	std::multimap<int32_t, IEntity*> updateEntites_;

	/** �������� ��ƼƼ�Դϴ�. */
	std::multimap<int32_t, IEntity2D*> renderEntities_;

	/** ���� ��ƼƼ�� �����Դϴ�. */
	std::pair<int32_t, int32_t> gameEntityRange_;

	/** UI ��ƼƼ�� �����Դϴ�. */
	std::pair<int32_t, int32_t> uiEntityRange_;

	/** ���� �÷��� ������ ��Ÿ���� ��ƼƼ�Դϴ�. */
	Playground* playground_ = nullptr;

	/** ���� �÷��� ���� ���� ī�޶��Դϴ�. */
	Camera2D* mainCamera_ = nullptr;

	/** ���� �÷��� ���� ��ũ�� ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** ������ �÷����� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** ������ ��׶��� ��ƼƼ�Դϴ�. */
	Background* background_ = nullptr;
	
	/** �÷��̾ ȹ���� ������ �����ϴ� ��ƼƼ�Դϴ�. */
	CoinCollector* coinCollector_ = nullptr;

	/** ���� �÷��� ����� �����ϴ� ��ƼƼ�Դϴ�. */
	GamePlayRecorder* gamePlayRecorder_ = nullptr;

	/** ESC Ŭ�� �� ������ ������Ű�� ��ƼƼ�Դϴ�. */
	KeyEventTrigger* gamePauseTrigger_ = nullptr;

	/** ���̵� ȿ���� ������ ��ƼƼ�Դϴ�. */
	FadeEffector* fadeEffector_ = nullptr;
	
	/** ���̵� �� �ð��Դϴ�. */
	float fadeInTime_ = 1.0f;

	/** ���̵� �ƿ� �ð��Դϴ�. */
	float fadeOutTime_ = 4.0f;

	/** ������ ���ۿ� ��ó���� �����ϴ� ������Ʈ�Դϴ�. */
	PostProcessor* postProcessor_ = nullptr;

	/** �������� ������ ������ �����Դϴ�. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** ������ ���ۿ� �������� �� ������ ������ �ɼ��Դϴ�. */
	RenderTargetOption renderTargetOption_;

	/** ���� ������ �����ϴ� ������ �̺�Ʈ�Դϴ�. */
	std::map<EWindowEvent, WindowEventID> windowPauseEvents_;

	/** ������ �����Ǿ����� Ȯ���մϴ�. */
	bool bIsPause_ = false;
};