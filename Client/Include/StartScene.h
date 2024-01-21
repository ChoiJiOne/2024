#pragma once

#include "Framebuffer.h"
#include "IScene.h"
#include "PostEffectShader.h"
#include "TTFont.h"
#include "UIMouseButton.h"
#include "UIPanel.h"


/**
 * @brief 게임 시작 씬입니다.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief 게임 시작 씬의 생성자입니다.
	 */
	StartScene();


	/**
	 * @brief 게임 시작 씬의 가상 소멸자입니다.
	 */
	virtual ~StartScene();


	/**
	 * @brief 게임 시작 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief 게임 시작 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief 게임 시작 씬의 리소스를 로딩합니다.
	 */
	void LoadResources();


	/**
	 * @brief 게임 시작 씬의 오브젝트를 로딩합니다.
	 */
	void LoadObjects();


private:
	/**
	 * @brief 크기가 32인 폰트 리소스입니다.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief 크기가 128인 폰트 리소스입니다.
	 */
	TTFont* font128_ = nullptr;


	/**
	 * @brief 후처리 효과를 적용하기 위한 프레임 버퍼입니다.
	 */
	Framebuffer* framebuffer_ = nullptr;


	/**
	 * @brief 후처리 효과를 적용하기 위한 페이드 효과 셰이더입니다.
	 */
	PostEffectShader* postEffectShader_ = nullptr;


	/**
	 * @brief 메인 타이틀 UI 오브젝트입니다.
	 */
	UIPanel* mainTitle_ = nullptr;


	/**
	 * @brief 시작 버튼입니다.
	 */
	UIMouseButton* startButton_ = nullptr;


	/**
	 * @brief 종료 버튼입니다.
	 */
	UIMouseButton* quitButton_ = nullptr;
};