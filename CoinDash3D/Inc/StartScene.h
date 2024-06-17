#pragma once

#include "IScene.h"

class Application;
class GeometryRenderer2D;
class TextRenderer;

class Button;
class Panel;


/**
 * @brief ���� ���� ���Դϴ�.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief ���� ���� ���� �������Դϴ�.
	 *
	 * @param app ���� �÷��� ���� ������ ���ø����̼� Ŭ�����Դϴ�.
	 */
	StartScene(Application* app);


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	StartScene() {}


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
	 * @brief �� ���� ��ƼƼ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds �� ���� ��Ÿ �ð����Դϴ�.
	 */
	void Update(float deltaSeconds);


	/**
	 * @brief ������ �غ� �մϴ�.
	 */
	void PrepareForRendering();


	/**
	 * @brief �� ���� ��ƼƼ�� �������մϴ�.
	 */
	void Render();


private:
	/**
	 * @brief 2D ���� ������ �������ϴ� �������Դϴ�.
	 */
	GeometryRenderer2D* geometryRenderer2D_ = nullptr;


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� �������Դϴ�.
	 */
	TextRenderer* textRenderer_ = nullptr;


	/**
	 * @brief ũ�⿡ ���� ��Ʈ ���ҽ��Դϴ�.
	 */
	std::map<int32_t, TTFont*> fonts_;


	/**
	 * @brief Ÿ��Ʋ �г��Դϴ�.
	 */
	Panel* titlePanel_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	Button* startButton_ = nullptr;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	Button* quitButton_ = nullptr;
};