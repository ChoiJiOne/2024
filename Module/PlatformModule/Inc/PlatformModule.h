#pragma once

#include <functional>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#error "not support platform"
#endif


/**
 * @brief �÷���(Windows) ���� ó���� �����ϴ� ����Դϴ�.
 * 
 * @note �� Ŭ������ ��� ��� ������ �޼���� ��� ����(static) Ÿ���Դϴ�.
 */
class PlatformModule
{
public:
	/**
	 * @brief �÷��� ����� ���� ó�� ����Դϴ�.
	 */
	enum class Errors
	{
		OK            = 0x00, // ������ �����ϴ�.
		FAILED        = 0x01, // �Ϲ����� �����Դϴ�.
		ERR_API       = 0x02, // �Ϲ����� API �����Դϴ�.
		ERR_PREV_INIT = 0x03, // ������ �ʱ�ȭ�� �����߽��ϴ�.
		ERR_NOT_INIT  = 0x04, // �ʱ�ȭ�� ������� �ʾҽ��ϴ�.
		ERR_IMGUI     = 0x05, // IMGUI ���� �����Դϴ�.
	};


	/**
	 * @brief ������ ������ ����� �Ķ�����Դϴ�.
	 */
	struct WindowConstructParams
	{
		std::wstring title;     // ������ Ÿ��Ʋ�Դϴ�.
		int32_t x;              // ������ ��� ������ x��ǥ�Դϴ�.
		int32_t y;              // ������ ��� ������ y��ǥ�Դϴ�.
		int32_t w;              // �������� ���� ũ���Դϴ�.
		int32_t h;              // �������� ���� ũ���Դϴ�.
		bool bIsResizable;      // ������ ũ�� ���� �����Դϴ�.
		bool bIsFullscreenMode; // �������� Ǯ��ũ�� �����Դϴ�.
	};


public:
	/**
	 * @brief �÷��� ����� �ʱ�ȭ�մϴ�.
	 * 
	 * @param windowParam ������ ������ ����� �Ķ�����Դϴ�.
	 * 
	 * @return �ʱ�ȭ�� �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Init(const WindowConstructParams& windowParam);


	/**
	 * @brief �÷��� ����� �ʱ�ȭ�� �����մϴ�.
	 * 
	 * @return �ʱ�ȭ ������ �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Uninit();


	/**
	 * @brief �÷��� ����� ���� �ֱ� ���� �޽����� ����ϴ�.
	 * 
	 * @return �÷��� ����� ���� �ֱٿ� �߻��� ���� �޽����� ������ ���� ��ȯ�մϴ�.
	 */
	static const wchar_t* GetLastErrorMessage();


	/**
	 * @brief ������ �ڵ� ���� ����ϴ�.
	 * 
	 * @return ������ �ڵ� ���� ��ȯ�մϴ�.
	 */
	static HWND GetWindowHandle();


	/**
	 * @brief ������ �����մϴ�.
	 * 
	 * @param callback ���� ���� �� ȣ���� ������ ������ �ݹ� �Լ��Դϴ�.
	 */
	static void RunLoop(const std::function<void(float)>& callback);


	/**
	 * @brief ���� ���� ���� �� ȣ���� �ݹ� �Լ��� �����մϴ�.
	 * 
	 * @param callback ���� ���� ���� �� ȣ���� �ݹ� �Լ��Դϴ�.
	 */
	static void SetEndLoopCallback(const std::function<void()>& callback) { endLoopCallback = callback; }


	/**
	 * @brief ��ũ�� ũ�⸦ ����ϴ�.
	 *
	 * @param outWidth ��ũ���� ���� ũ���Դϴ�.
	 * @param outHeight ��ũ���� ���� ũ���Դϴ�.
	 *
	 * @return ��ũ�� ũ�⸦ ��� �� �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors GetScreenSize(int32_t& outWidth, int32_t& outHeight);


	/**
	 * @brief Ǯ��ũ�� ������� Ȯ���մϴ�.
	 * 
	 * @return Ǯ��ũ�� ����̸� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsFullscreenMode() { return bIsFullscreenMode; }


private:
	/**
	 * @brief ���� �޽����� �����մϴ�.
	 *
	 * @note ������ �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	static void SetLastErrorMessage();


	/**
	 * @brief ���� �޽����� �����մϴ�.
	 *
	 * @param message ������ �޽����Դϴ�.
	 */
	static void SetLastErrorMessage(const std::wstring& message);


	/**
	 * @brief ������ Ŭ������ ����մϴ�.
	 * 
	 * @return ������ Ŭ���� ��Ͽ� �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors RegisterWindowClass();


	/**
	 * @brief ������ â�� �����մϴ�.
	 * 
	 * @param windowParam ������ ������ ����� �Ķ�����Դϴ�.
	 * 
	 * @return ������ ������ �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors CreatePlatformWindow(const WindowConstructParams& windowParam);


	/**
	 * @brief ������ ���ν��� �Լ��� PlatformModule ���θ� ������ �� �ֵ��� friend ���� �߰�
	 */
	friend LRESULT CALLBACK WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);


private:
	/**
	 * @brief �÷��� ����� �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 */
	static bool bIsInit;


	/**
	 * @brief Ǯ ��ũ�� ������� Ȯ���մϴ�.
	 */
	static bool bIsFullscreenMode;


	/**
	 * @brief ������ â�� �ּ�ȭ �������� Ȯ���մϴ�.
	 */
	static bool bIsMinimize;


	/**
	 * @brief ������ â�� �ִ�ȭ �������� Ȯ���մϴ�.
	 */
	static bool bIsMaximize;


	/**
	 * @brief ���α׷��� �ڵ� ���Դϴ�.
	 */
	static HINSTANCE instance;


	/**
	 * @brief ������ Ŭ���� �̸��Դϴ�.
	 */
	static std::wstring className;


	/**
	 * @brief ������ �ڵ� ���Դϴ�.
	 */
	static HWND windowHandle;


	/**
	 * @brief ���ڿ� ������ �ִ� ũ���Դϴ�.
	 */
	static const uint32_t MAX_BUFFER_SIZE = 1024;


	/**
	 * @brief �ֱ� ���� �޽����Դϴ�.
	 */
	static wchar_t lastErrorMessage[MAX_BUFFER_SIZE];


	/**
	 * @brief ���� ���� ���� �� ������ �ݹ� �Լ��Դϴ�.
	 */
	static std::function<void()> endLoopCallback;



	/**
	 * @brief ���� ���� �� ȣ���� ������ ������ �ݹ� �Լ��Դϴ�.
	 */
	static std::function<void(float)> frameCallback;
};