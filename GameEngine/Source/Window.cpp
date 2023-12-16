#include "Window.h"

#include "WindowsAssertion.h"

bool Window::bIsRegisterWindowClass_ = false;
HINSTANCE Window::hInstance_ = nullptr;
std::wstring Window::windowClassName_;

Window::~Window()
{
	Destroy();
}

void Window::Create(const std::wstring& title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizable, bool bIsShow, bool bIsFullscreenMode)
{
	ASSERT(windowHandle_ == nullptr, "already create window...");
	
	int32_t windowPosX = 0;
	int32_t windowPosY = 0;
	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	uint32_t windowStyle = 0;

	if (bIsFullscreenMode)
	{
		bIsResizable_ = false;
		bIsFullscreenMode_ = true;

		windowPosX = 0;
		windowPosY = 0;
		windowWidth = static_cast<int32_t>(GetSystemMetrics(SM_CXSCREEN));
		windowHeight = static_cast<int32_t>(GetSystemMetrics(SM_CYSCREEN));
		windowStyle = WS_POPUP;

		DEVMODEW devMode = {};
		devMode.dmSize = sizeof(DEVMODEW);
		devMode.dmPelsWidth = static_cast<uint32_t>(windowWidth);
		devMode.dmPelsHeight = static_cast<uint32_t>(windowHeight);
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		WINDOWS_ASSERT(ChangeDisplaySettingsW(&devMode, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL, "failed to set fullscreen mode...");
	}
	else
	{
		bIsResizable_ = bIsResizable;
		bIsFullscreenMode_ = false;

		RECT windowRect = { 0, 0, w, h };
		WINDOWS_ASSERT(AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE), "failed to calculate window size...");

		windowPosX = x;
		windowPosY = y;
		windowWidth = windowRect.right - windowRect.left;
		windowHeight = windowRect.bottom - windowRect.top;
		windowStyle = bIsResizable ? WS_OVERLAPPEDWINDOW : (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	}

	windowHandle_ = CreateWindowExW(
		WS_EX_APPWINDOW,
		windowClassName_.c_str(),
		title.c_str(),
		static_cast<DWORD>(windowStyle),
		windowPosX,
		windowPosY,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		hInstance_,
		nullptr
	);
	WINDOWS_ASSERT(windowHandle_ != nullptr, "failed to create window...");
}

void Window::Destroy()
{
	if (windowHandle_ == nullptr)
	{
		return;
	}

	if (bIsFullscreenMode_)
	{
		WINDOWS_ASSERT(ChangeDisplaySettingsW(nullptr, 0) == DISP_CHANGE_SUCCESSFUL, "failed to set default mode...");
	}

	WINDOWS_ASSERT(DestroyWindow(windowHandle_), "failed to destroy window...");
	windowHandle_ = nullptr;
}

void Window::RegisterWindowClass(const std::wstring& windowClassName, WINDOWPROC windowProc)
{
	ASSERT(!bIsRegisterWindowClass_, "already register window class...");
	ASSERT(windowProc != nullptr, "Window procedure is nullptr...");

	hInstance_ = GetModuleHandleW(nullptr);
	windowClassName_ = windowClassName;

	WNDCLASSEXW wcexw = {};
	wcexw.cbSize = sizeof(WNDCLASSEXW);
	wcexw.style = CS_HREDRAW | CS_VREDRAW;
	wcexw.lpfnWndProc = windowProc;
	wcexw.cbClsExtra = 0;
	wcexw.cbWndExtra = 0;
	wcexw.hInstance = hInstance_;
	wcexw.hIcon = LoadIcon(hInstance_, IDI_APPLICATION);
	wcexw.hIconSm = LoadIcon(hInstance_, IDI_APPLICATION);
	wcexw.hCursor = LoadCursor(hInstance_, IDC_ARROW);
	wcexw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcexw.lpszMenuName = nullptr;
	wcexw.lpszClassName = windowClassName_.c_str();

	WINDOWS_ASSERT(RegisterClassExW(&wcexw) != 0, "failed to register window class...");
	bIsRegisterWindowClass_ = true;
}

void Window::UnregisterWindowClass()
{
	ASSERT(bIsRegisterWindowClass_, "haven't registered before or have already unregistered...");

	UnregisterClassW(windowClassName_.c_str(), hInstance_);

	hInstance_ = nullptr;
	bIsRegisterWindowClass_ = false;
}