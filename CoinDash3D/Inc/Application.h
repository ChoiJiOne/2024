#pragma once

#include "AudioModule.h"
#include "CrashModule.h"
#include "FileModule.h"
#include "GameModule.h"
#include "MathModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"


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

};