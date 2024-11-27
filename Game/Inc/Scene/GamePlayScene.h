#pragma once

#include <map>

#include "Scene/IGameScene.h"
#include "GL/RenderManager2D.h"

/** 클래스 전방 선언입니다. */
class Camera2D;
class FadeEffector;
class UICamera;
class Player;
class PostProcessor;
class FrameBuffer;


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
	/** Tick을 수행하기 전에 호출합니다. */
	void PreTick(float deltaSeconds);

private:
	/** 업데이트할 엔티티입니다. */
	std::multimap<int32_t, IEntity*> updateEntites_;

	/** 렌더링할 엔티티입니다. */
	std::multimap<int32_t, IEntity2D*> renderEntities_;

	/** 게임 플레이 씬의 메인 카메라입니다. */
	Camera2D* mainCamera_ = nullptr;

	/** 게임 플레이 씬의 스크린 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 게임을 플레이할 플레이어입니다. */
	Player* player_ = nullptr;
	
	/** 페이드 효과를 제어할 엔티티입니다. */
	FadeEffector* fadeEffector_ = nullptr;

	/** 페이드 인 시간입니다. */
	float fadeInTime_ = 1.0f;

	/** 페이드 아웃 시간입니다. */
	float fadeOutTime_ = 3.0f;

	/** 프레임 버퍼에 후처리를 수행하는 오브젝트입니다. */
	PostProcessor* postProcessor_ = nullptr;

	/** 렌더링을 수행할 프레임 버퍼입니다. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** 프레임 버퍼에 렌더링할 때 설정할 렌더링 옵션입니다. */
	RenderTargetOption renderTargetOption_;
};