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
	None          = 0x0000,
	Active        = 0x0001,
	Inactive      = 0x0002,
	Close         = 0x0003,
	Move          = 0x0004,
	Resize        = 0x0005,
	EnterResize   = 0x0006,
	ExitResize    = 0x0007,
	EnterMinimize = 0x0008,
	ExitMinimize  = 0x0009,
	EnterMaximize = 0x0010,
	ExitMaximize  = 0x0011,
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
	 * @brief �Է� ���¸� ������Ʈ�մϴ�.
	 */
	void Tick();


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
	 * @brief ������ �̺�Ʈ �׼��� �߰��մϴ�.
	 *
	 * @param signature ������ �̺�Ʈ �׼��� �ñ״�ó ���Դϴ�.
	 * @param windowEvent ������ �׼ǿ� �����ϴ� ������ �̺�Ʈ�Դϴ�.
	 * @param eventAction �̺�Ʈ �׼ǿ� �����ϴ� �׼��Դϴ�.
	 * @param bIsActive ������ �̺�Ʈ �׼� Ȱ��ȭ �����Դϴ�. �⺻ ���� true�Դϴ�.
	 *  
	 * @note �ñ״�ó ���ڿ��� ���� ������ �̺�Ʈ �׼ǵ鿡 �����ϴ� ���ڿ� ������ �����ؾ� �մϴ�.
	 */
	void AddWindowEventAction(const std::string& signature, const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive = true);


	/**
	 * @brief ������ �̺�Ʈ �׼��� �����մϴ�.
	 * 
	 * @param signature ������ �̺�Ʈ �׼��� �ñ״�ó ���Դϴ�.
	 * 
	 * @note �ñ״�ó�� �����ϴ� ������ �̺�Ʈ�� �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	void DeleteWindowEventAction(const std::string& signature);


	/**
	 * @brief ������ �̺�Ʈ �׼��� Ȱ��ȭ ���θ� �����մϴ�.
	 * 
	 * @param signature ������ �̺�Ʈ �׼��� �ñ״�ó ���Դϴ�.
	 * @param bIsActive ������ �̺�Ʈ�� Ȱ��ȭ �����Դϴ�.
	 * 
	 * @note �ñ״�ó�� �����ϴ� ������ �̺�Ʈ�� �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	void SetActiveWindowEventAction(const std::string& signature, bool bIsActive);


	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �׼ǵ��� �����մϴ�.
	 * 
	 * @param signature ������ ������ �̺�Ʈ�Դϴ�.
	 */
	void ExecuteWindowEventAction(const EWindowEvent& windowEvent);


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
	 * @brief ������ �̺�Ʈ Ǯ���� �����մϴ�.
	 */
	void PollWindowEvents();


private:
	/**
	 * @brief �Է� ó�� ����� �Ǵ� �������Դϴ�.
	 */
	Window* inputControlWindow_ = nullptr;


	/**
	 * @brief ������ â�� �ּ�ȭ �������� Ȯ���մϴ�.
	 */
	bool bIsMinimize_ = false;


	/**
	 * @brief ������ â�� �ִ�ȭ �������� Ȯ���մϴ�.
	 */
	bool bIsMaximize_ = false;

	
	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
	 */
	std::unordered_map<std::string, WindowEventAction> windowEventActions_;
};