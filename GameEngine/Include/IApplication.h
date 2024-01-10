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
#include "FileUtils.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "GLAssertion.h"
#include "InputManager.h"
#include "IManager.h"
#include "IObject.h"
#include "Macro.h"
#include "Material.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
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
 * @brief ���ø����̼� �������̽��Դϴ�.
 *
 * @note ���ø����̼��� �ʱ�ȭ �� �����ϴ� Ŭ������ �ݵ�� �� Ŭ������ ��ӹ޾ƾ� �մϴ�.
 */
class IApplication
{
public:
	/**
	 * @brief ���ø����̼� �������̽��� ����Ʈ �������Դϴ�.
	 */
	IApplication() = default;


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