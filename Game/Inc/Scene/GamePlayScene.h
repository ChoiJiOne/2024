#pragma once

#include <map>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"

/** 클래스 전방 선언입니다. */
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


/** 게임 플레이 씬입니다. */
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
	 * 엔티티를 추가합니다. 
	 * - 추가하는 엔티티는 렌더링하지 않습니다. 
	 * - 값이 작을수록 우선순위 값은 높습니다. 
	 */
	void AddEntity(IEntity* entity, int32_t updateOrder);

	/** 
	 * 엔티티를 추가합니다. 
	 * - 추가하는 엔티티는 렌더링을 수행합니다. 
	 * - 값이 작을수록 우선순위 값은 높습니다. 
	 */
	void AddEntity(IEntity2D* entity, int32_t updateOrder, int32_t renderOrder);

	/** 엔티티를 삭제합니다. */
	void RemoveEntity(IEntity* entity);

private:
	/** 게임 중지 씬에서 게임 플레이 씬 내부에 접근할 수 있도록 설정합니다. */
	friend class GamePauseScene;

	/** Tick을 수행하기 전에 호출합니다. */
	void PreTick(float deltaSeconds);

	/** 게임 플레이 씬을 초기화합니다. */
	void Initialize();

	/** 게임 플레이 씬의 초기화를 해제합니다. */
	void UnInitialize();

	/** 게임 플레이 씬의 엔티티를 로딩합니다. */
	void LoadEntity();

	/** 게임 플레이 씬의 엔티티를 로딩 해제합니다. */
	void UnloadEntity();

private:
	/** 업데이트할 엔티티입니다. */
	std::multimap<int32_t, IEntity*> updateEntites_;

	/** 렌더링할 엔티티입니다. */
	std::multimap<int32_t, IEntity2D*> renderEntities_;

	/** 게임 엔티티의 범위입니다. */
	std::pair<int32_t, int32_t> gameEntityRange_;

	/** UI 엔티티의 범위입니다. */
	std::pair<int32_t, int32_t> uiEntityRange_;

	/** 게임 플레이 영역을 나타내는 엔티티입니다. */
	Playground* playground_ = nullptr;

	/** 게임 플레이 씬의 메인 카메라입니다. */
	Camera2D* mainCamera_ = nullptr;

	/** 게임 플레이 씬의 스크린 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 게임을 플레이할 플레이어입니다. */
	Player* player_ = nullptr;

	/** 게임의 백그라운드 엔티티입니다. */
	Background* background_ = nullptr;
	
	/** 플레이어가 획득한 코인을 수집하는 엔티티입니다. */
	CoinCollector* coinCollector_ = nullptr;

	/** 게임 플레이 기록을 저장하는 엔티티입니다. */
	GamePlayRecorder* gamePlayRecorder_ = nullptr;

	/** ESC 클릭 시 게임을 중지시키는 엔티티입니다. */
	KeyEventTrigger* gamePauseTrigger_ = nullptr;

	/** 페이드 효과를 제어할 엔티티입니다. */
	FadeEffector* fadeEffector_ = nullptr;
	
	/** 페이드 인 시간입니다. */
	float fadeInTime_ = 1.0f;

	/** 페이드 아웃 시간입니다. */
	float fadeOutTime_ = 4.0f;

	/** 프레임 버퍼에 후처리를 수행하는 오브젝트입니다. */
	PostProcessor* postProcessor_ = nullptr;

	/** 렌더링을 수행할 프레임 버퍼입니다. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** 프레임 버퍼에 렌더링할 때 설정할 렌더링 옵션입니다. */
	RenderTargetOption renderTargetOption_;

	/** 게임 중지를 유발하는 윈도우 이벤트입니다. */
	std::map<EWindowEvent, WindowEventID> windowPauseEvents_;

	/** 게임이 중지되었는지 확인합니다. */
	bool bIsPause_ = false;
};