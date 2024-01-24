#pragma once

#include <array>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Assertion.h"
#include "AudioManager.h"
#include "Box3D.h"
#include "Camera3D.h"
#include "CommandLineUtils.h"
#include "FileUtils.h"
#include "Framebuffer.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "GLAssertion.h"
#include "InputManager.h"
#include "IManager.h"
#include "IObject.h"
#include "IScene.h"
#include "Light.h"
#include "LightShader.h"
#include "Macro.h"
#include "Material.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "PostEffectShader.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "ShadowMap.h"
#include "ShadowShader.h"
#include "Skybox.h"
#include "Sound.h"
#include "Sphere3D.h"
#include "StaticMesh.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "Transform.h"
#include "TTFont.h"
#include "Window.h"
#include "WindowsAssertion.h"
#include "WindowsCrashUtils.h"


/**
 * @brief ���ø����̼� �������̽��Դϴ�.
 *
 * @note ���ø����̼��� �ʱ�ȭ �� �����ϴ� Ŭ������ �ݵ�� �� Ŭ������ ��ӹ޾ƾ� �մϴ�.
 */
class IApplication
{
public:
	/**
	 * @brief ���ø����̼� �������̽��� �������Դϴ�.
	 */
	IApplication();


	/**
	 * @brief ���ø����̼� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IApplication();


	/**
	 * @brief ���ø����̼� �������̽��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IApplication);


	/**
	 * @brief ���ø����̼� �������̽��� �ʱ�ȭ�մϴ�.
	 *
	 * @note ���� Ŭ���������� �ʱ�ȭ ���� �� �޼��带 �ݵ�� ȣ���ؾ� �մϴ�.
	 */
	virtual void Setup();


	/**
	 * @brief ���ø����̼� �������̽��� ����� �����մϴ�.
	 */
	virtual void Shutdown();


	/**
	 * @brief ���ø����̼��� �����մϴ�.
	 */
	virtual void Run() = 0;


protected:
	/**
	 * @brief ���ø����̼��� �Ӽ��� �����մϴ�.
	 * 
	 * @param windowTitle ���ø����̼��� ������ Ÿ��Ʋ�Դϴ�.
	 * @param windowPosition ���ø����̼��� ȭ�� �� �������� (X, Y) ��ġ�Դϴ�.
	 * @param windowWidth ���ø����̼��� ������ ���� ũ���Դϴ�.
	 * @param windowHeight ���ø����̼��� ������ ���� ũ���Դϴ�.
	 * @param bIsResize ���ø����̼��� ������ ũ�� ���� �����Դϴ�.
	 * @param bIsFullscreen ���ø����̼��� ������ Ǯ ��ũ�� �����Դϴ�.
	 * @param bIsVsync ���ø����̼��� ���� ����ȭ �����Դϴ�.
	 * @param bIsImGui ImGui ���̺귯�� ��� �����Դϴ�.
	 */
	void SetProperties(
		const std::wstring& windowTitle, 
		const Vector2i& windowPosition, 
		int32_t windowWidth, 
		int32_t windowHeight,
		bool bIsResize,
		bool bIsFullscreen,
		bool bIsVsync,
		bool bIsImGui
	);

	
protected:
	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�ߴ��� Ȯ���մϴ�.
	 */
	bool bIsSetup_ = false;


	/**
	 * @brief �Ӽ� ������ �����ߴ��� Ȯ���մϴ�.
	 */
	bool bIsPropertiesSet_ = false;


	/**
	 * @brief ���ø����̼� ������ Ÿ��Ʋ�Դϴ�.
	 */
	std::wstring windowTitle_;


	/**
	 * @brief ���ø����̼��� ȭ�� �� (x, y) ��ǥ�Դϴ�.
	 */
	Vector2i windowPosition_;


	/**
	 * @brief ���ø����̼��� ȭ�� ���� ���� ũ���Դϴ�.
	 */
	int32_t windowWidth_ = 0;


	/**
	 * @brief ���ø����̼��� ȭ�� ���� ���� ũ���Դϴ�.
	 */
	int32_t windowHeight_ = 0;


	/**
	 * @brief ���ø����̼��� ������ ũ�� ���� �����Դϴ�.
	 */
	bool bIsResize_ = false;


	/**
	 * @brief ���ø����̼��� ������ Ǯ ��ũ�� �����Դϴ�.
	 */
	bool bIsFullscreen_ = false;


	/**
	 * @brief ���ø����̼��� ���� ����ȭ �����Դϴ�.
	 */
	bool bIsVsync_ = true;


	/**
	 * @brief ImGui ���̺귯�� ��� �����Դϴ�.
	 */
	bool bIsImGui_ = false;

	
	/**
	 * @brief ���� ���� ���ᰡ �����Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsDoneLoop_ = false;


	/**
	 * @brief ��Ʈ ����Դϴ�.
	 */
	std::wstring rootPath_;


	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	std::wstring enginePath_;


	/**
	 * @brief ���� �������Դϴ�.
	 */
	std::unique_ptr<Window> window_ = nullptr;
};