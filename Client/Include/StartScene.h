#pragma once

#include "Framebuffer.h"
#include "IScene.h"
#include "PostEffectShader.h"
#include "TTFont.h"
#include "UIMouseButton.h"
#include "UIPanel.h"


/**
 * @brief ���� ���� ���Դϴ�.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief ���� ���� ���� �������Դϴ�.
	 */
	StartScene();


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StartScene();


	/**
	 * @brief ���� ���� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief ���� ���� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief ���� ���� ���� ���ҽ��� �ε��մϴ�.
	 */
	void LoadResources();


	/**
	 * @brief ���� ���� ���� ������Ʈ�� �ε��մϴ�.
	 */
	void LoadObjects();


private:
	/**
	 * @brief ũ�Ⱑ 32�� ��Ʈ ���ҽ��Դϴ�.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief ũ�Ⱑ 128�� ��Ʈ ���ҽ��Դϴ�.
	 */
	TTFont* font128_ = nullptr;


	/**
	 * @brief ��ó�� ȿ���� �����ϱ� ���� ������ �����Դϴ�.
	 */
	Framebuffer* framebuffer_ = nullptr;


	/**
	 * @brief ��ó�� ȿ���� �����ϱ� ���� ���̵� ȿ�� ���̴��Դϴ�.
	 */
	PostEffectShader* postEffectShader_ = nullptr;


	/**
	 * @brief ���� Ÿ��Ʋ UI ������Ʈ�Դϴ�.
	 */
	UIPanel* mainTitle_ = nullptr;


	/**
	 * @brief ���� ��ư�Դϴ�.
	 */
	UIMouseButton* startButton_ = nullptr;


	/**
	 * @brief ���� ��ư�Դϴ�.
	 */
	UIMouseButton* quitButton_ = nullptr;
};