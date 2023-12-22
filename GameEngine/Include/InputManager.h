#pragma once

#include <cstdint>
#include <windows.h>

#include "IManager.h"

class Window;


/**
 * @brief �Է� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class InputManager : public IManager
{
public:
	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return �Է� ó���� �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static InputManager& Get()
	{
		static InputManager instance;
		return instance;
	}


	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - �� �޼��� ȣ�� ���� �Է� ó�� ����� �Ǵ� ������ �����͸� �����ؾ� �մϴ�.
	 * - �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief �Է� ó�� ����� �Ǵ� �����츦 �����մϴ�.
	 * 
	 * @param window �Է� ó�� ����� �Ǵ� �������Դϴ�.
	 */
	void SetInputControlWindow(Window* window) { inputControlWindow_ = window; }


	/**
	 * @brief �Է� ó�� ����� �Ǵ� �����츦 ����ϴ�.
	 * 
	 * @return �Է� ó�� ����� �Ǵ� �������� �����͸� ����ϴ�.
	 */
	Window* GetInputControlWindow() const { return inputControlWindow_; }


private:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(InputManager);


private:
	/**
	 * @brief �Է� ó�� ����� �Ǵ� �������Դϴ�.
	 */
	Window* inputControlWindow_ = nullptr;
};