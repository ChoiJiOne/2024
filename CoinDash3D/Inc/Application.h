#pragma once

#include <memory>

#include "AudioModule.h"
#include "CrashModule.h"
#include "FileModule.h"
#include "GameModule.h"
#include "MathModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

#include "IScene.h"

class DepthRenderer;
class GeometryRenderer2D;
class GeometryRenderer3D;
class MeshRenderer;
class ShadowMap;
class TextRenderer;


/**
 * @brief ���ø����̼��� �ʱ�ȭ/����/�����ϴ� Ŭ�����Դϴ�.
 */
class Application
{
public:
	/**
	 * @brief ���ø����̼��� �������Դϴ�.
	 */
	Application();


	/**
	 * @brief ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Application();


	/**
	 * @brief ���÷����̼��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Application);


	/**
	 * @brief ���ø����̼��� �ʱ�ȭ�մϴ�.
	 */
	void Init();


	/**
	 * @brief ���ø����̼��� �����մϴ�.
	 */
	void Run();


private:
	/**
	 * @brief �� ���ο��� Application�� ���ο� ������ �� �ֵ��� �����մϴ�.
	 */
	friend class IScene;
	friend class PlayScene;


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
	 * @brief �ε��� ���Դϴ�.
	 */
	ShadowMap* shadowMap_ = nullptr;

	
	/**
	 * @brief �÷��� ���Դϴ�.
	 */
	std::unique_ptr<IScene> playScene_ = nullptr;


	/**
	 * @brief ���� ���Դϴ�.
	 */
	IScene* currentScene_ = nullptr;
};