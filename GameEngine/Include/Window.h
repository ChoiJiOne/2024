#pragma once

#include <cstdint>
#include <string>
#include <windows.h>

#include "Macro.h"


/**
 * @brief ������ ���ν����Դϴ�.
 */
typedef LRESULT(CALLBACK* WINDOWPROC)(HWND, uint32_t, WPARAM, LPARAM);


/**
 * @brief �����츦 �����ϰ� �����մϴ�.
 */
class Window
{
public:
	/**
	 * @brief �����츦 �����ϰ� �����ϴ� Ŭ������ ����Ʈ �������Դϴ�.
	 */
	Window() = default;


	/**
	 * @brief �����츦 �����ϰ� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Window();


	/**
	 * @brief �����츦 �����ϰ� �����ϴ� Ŭ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief �����츦 �����մϴ�.
	 * 
	 * @note Ǯ ��ũ�� ��� ���� �� �Ϻ� �ɼ��� ���õ˴ϴ�.
	 * 
	 * @param title �������� Ÿ��Ʋ�Դϴ�.
	 * @param x ������ ��ġ�� X��ǥ�Դϴ�. 
	 * @param y ������ ��ġ�� Y��ǥ�Դϴ�. 
	 * @param w �������� ���� ũ���Դϴ�.
	 * @param h �������� ���� ũ���Դϴ�.
	 * @param bIsResizable �������� ũ�� ��ȯ �����Դϴ�.
	 * @param bIsShow �����츦 ǥ���� �� �����Դϴ�
	 * @param bIsFullscreenMode �����츦 Ǯ ��ũ�� ���� ������ �� �����Դϴ�.
	 */
	void Create(const std::wstring& title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizable, bool bIsShow, bool bIsFullscreenMode);


	/**
	 * @brief �����츦 �ı��մϴ�.
	 */
	void Destroy();


	/**
	 * @brief �����찡 Ǯ ��ũ��������� Ȯ���մϴ�.
	 * 
	 * @return �����찡 Ǯ ��ũ������� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsFullscreenMode() const { return bIsFullscreenMode_; }


	/**
	 * @brief �������� ũ�⸦ ������ �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return �������� ũ�⸦ ������ �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsResizable() const { return bIsResizable_; }


	/**
	 * @brief ������ �ڵ��� ����ϴ�.
	 * 
	 * @return ������ �ڵ��� ��ȯ�մϴ�.
	 */
	HWND GetHandle() { return windowHandle_; }


	/**
	 * @brief ������ Ŭ������ ����մϴ�.
	 * 
	 * @note �� ���� �޼���� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * 
	 * @param windowClassName ����� ������ Ŭ������ �̸��Դϴ�.
	 * @param windowProc ����� ������ Ŭ������ ���ν����Դϴ�.
	 */
	static void RegisterWindowClass(const std::wstring& windowClassName, WINDOWPROC windowProc);


	/**
	 * @brief ������ Ŭ������ ��� �����մϴ�.
	 */
	static void UnregisterWindowClass();


	/**
	 * @brief ������ Ŭ������ ����ߴ��� Ȯ���մϴ�.
	 * 
	 * @return ������ Ŭ������ ����ߴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsRegisterWindowClass() { return bIsRegisterWindowClass_; }
	

private:
	/**
	 * @brief ������ �ڵ��Դϴ�.
	 */
	HWND windowHandle_ = nullptr;


	/**
	 * @brief �������� ũ�⸦ �ٲ� �� �ִ��� Ȯ���մϴ�.
	 */
	bool bIsResizable_ = false;


	/**
	 * @brief Ǯ ��ũ�� ������� Ȯ���մϴ�.
	 */
	bool bIsFullscreenMode_ = false;
	

	/**
	 * @brief ������ Ŭ������ ����ߴ��� Ȯ���մϴ�.
	 */
	static bool bIsRegisterWindowClass_;


	/**
	 * @brief �ν��Ͻ��� ���� �ڵ��Դϴ�.
	 * 
	 * @note
	 * - �ν��Ͻ��� ���� �ڵ��� �޸𸮿� �ִ� ����� �⺻ �ּ��Դϴ�.
	 * - ���� : https://learn.microsoft.com/ko-kr/windows/win32/winprog/windows-data-types#:~:text=typedef%20HANDLE%20HICON%3B-,HINSTANCE,-instance%20%EB%8C%80%ED%95%9C%20%ED%95%B8%EB%93%A4%EC%9E%85%EB%8B%88%EB%8B%A4
	 */
	static HINSTANCE hInstance_;


	/**
	 * @brief ������ Ŭ������ �̸��Դϴ�.
	 * 
	 * @note 
	 * - ������ Ŭ������ ��Ÿ��, ������, Ŀ��, �޴� �� ������ ���ν����� ���� Ư���� �����մϴ�.
	 * - ���� : https://learn.microsoft.com/ko-kr/windows/win32/winmsg/about-window-classes#types-of-window-classes
	 */
	static std::wstring windowClassName_;
};