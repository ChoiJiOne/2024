#pragma once

#include <array>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "DirectionalLight.h"
#include "FileUtils.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "GLAssertion.h"
#include "InputManager.h"
#include "Macro.h"
#include "Material.h"
#include "MathUtils.h"
#include "PointLight.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "SpotLight.h"
#include "StaticMesh.h"
#include "StringUtils.h"
#include "ShadowMap.h"
#include "Skybox.h"
#include "Texture2D.h"
#include "TTFont.h"
#include "Window.h"
#include "WindowsAssertion.h"
#include "WindowsCrashUtils.h"


/**
 * @brief ���� �����ӿ�ũ �������̽��Դϴ�.
 * 
 * @note ���� ������ �����Ǵ� Ŭ������ �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�.
 */
class IGameFramework
{
public:
	/**
	 * @brief ���� �����ӿ�ũ�� ����Ʈ �������Դϴ�.
	 */
	IGameFramework() = default;


	/**
	 * @brief ���� �����ӿ�ũ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IGameFramework();


	/**
	 * @brief ���� �����ӿ�ũ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IGameFramework);


	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 */
	virtual void Setup();


	/**
	 * @brief ���� �����ӿ�ũ ����� �����մϴ�.
	 */
	virtual void Shutdown();


	/**
	 * @brief ���� �����ӿ�ũ�� �����մϴ�.
	 */
	virtual void Run() = 0;


protected:
	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�ߴ��� Ȯ���մϴ�.
	 */
	bool bIsSetup_ = false;


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