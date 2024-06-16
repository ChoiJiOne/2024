#pragma once

#include "IScene.h"

class Application; 
class DepthRenderer;
class GeometryRenderer2D;
class GeometryRenderer3D;
class MeshRenderer;
class TextRenderer;


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
};