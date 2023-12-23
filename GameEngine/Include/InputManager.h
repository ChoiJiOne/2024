#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <windows.h>

#include "IManager.h"

class Window;


/**
 * @brief ������ �̺�Ʈ�Դϴ�.
 */
enum class EWindowEvent : int32_t
{
	None = 0x0000,
	Active = 0x01,
	Inactive = 0x02,
	Close = 0x03,
};


/**
 * @brief ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
 */
struct WindowEventAction
{
	bool				  bIsActive;         // ������ �̺�Ʈ�� Ȱ��ȭ �����Դϴ�.
	EWindowEvent		  windowEvent;       // ������ �̺�Ʈ�Դϴ�.
	std::function<void()> windowEventAction; // ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
};


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


	/**
	 * @brief ������ �޽����� ó���մϴ�.
	 *
	 * @param windowHandle ���ν����� ó���� ������ �ڵ��Դϴ�.
	 * @param message �޽��� �ĺ����Դϴ�.
	 * @param wParam �޽����� �ΰ� �����Դϴ�.
	 * @param lParam �޽����� �ΰ� �����Դϴ�.
	 *
	 * @return �޽����� ó������ ��� 0�� ��ȯ�մϴ�. �׷��� ������ DefWindowProcW�� ��ȯ�� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-procedures
	 * - ProcessWindowMessage ���ο��� �޽����� ó������ ���� 0�� ��ȯ
	 */
	LRESULT ProcessWindowMessage(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam);


	/**
	 * @brief �⺻���� ������ �޽����� ó���մϴ�.
	 * 
	 * @param windowHandle ���ν����� ó���� ������ �ڵ��Դϴ�.
	 * @param message �޽��� �ĺ����Դϴ�.
	 * @param wParam �޽����� �ΰ� �����Դϴ�.
	 * @param lParam �޽����� �ΰ� �����Դϴ�.
	 * 
	 * @return �޽����� ó������ ��� 0�� ��ȯ�մϴ�. �׷��� ������ DefWindowProcW�� ��ȯ�� ���� ��ȯ�մϴ�.
	 * 
	 * @see 
	 * - https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-procedures
	 * - ProcessWindowMessage ���ο��� �޽����� ó������ ���� 0�� ��ȯ
	 */
	static LRESULT CALLBACK WindowProc(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam);


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


	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
	 */
	std::unordered_map<std::string, WindowEventAction> windowEventActions_;
};