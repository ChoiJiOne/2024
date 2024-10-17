#pragma once

#include <array>
#include <functional>
#include <memory>
#include <vector>

#include "Camera2D.h"
#include "GameMath.h"
#include "GameTimer.h"
#include "GameUtils.h"
#include "Macro.h"

class IApp
{
public:
	IApp(const char* title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizble, bool bIsFullscreen);
	virtual ~IApp();

	DISALLOW_COPY_AND_ASSIGN(IApp); /** ��������� ���� ������ �� ���� ������ ���� */

	virtual void Startup() = 0;
	virtual void Shutdown() = 0;
	virtual void Run() = 0;

	static IApp* Get();
	
	bool IsQuit() const { return bIsQuit_; }
	bool IsResize() const { return bIsResize_; }
	bool IsMinimize() const { return bIsMinimize_; }
	bool IsMaximize() const { return bIsMaximize_; }
	bool IsEnterMouse() const { return bIsEnterMouse_; }
	bool IsGainFocus() const { return bIsGainFocus_; }

	/** �Է� ���� ���� */
	Press GetKeyPress(const Key& key);
	Press GetMousePress(const Mouse& mouse);
	const Vec2i& GetPrevMousePos() { return prevMouseState_.position; }
	const Vec2i& GetCurrMousePos() { return currMouseState_.position; }
	WindowEventID AddWindowEventAction(const WindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive = true);
	void DeleteWindowEventAction(const WindowEventID& windowEventID);
	void SetActiveWindowEventAction(const WindowEventID& windowEventID, bool bIsActive);

protected:
	struct WindowEventAction
	{
		bool				  bIsActive = false;               // ������ �̺�Ʈ�� Ȱ��ȭ �����Դϴ�.
		WindowEvent		      windowEvent = WindowEvent::NONE; // ������ �̺�Ʈ�Դϴ�.
		std::function<void()> windowEventAction = nullptr;     // ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
	};

	struct KeyboardState
	{
		static const int32_t BUFFER_SIZE = 512;        // Ű������ Ű �� ���¸� �����ϴ� ������ ũ���Դϴ�.
		std::array<uint8_t, BUFFER_SIZE> keybordState; // Ű������ Ű �� ���¸� �����ϴ� �����Դϴ�.
	};

	struct MouseState
	{
		uint32_t state; // ���콺 ��ư�� �����Դϴ�.
		Vec2i position; // ���콺 ��ư�� ��ġ�Դϴ�.
	};

	void RunLoop(const std::function<void(float)>& frameCallback);

	void RegisterAppWindowEvent();
	bool IsPressKey(const KeyboardState& keyboardState, const Key& key);
	bool IsPressMouse(const MouseState& mouseState, const Mouse& mouse);

protected:
	static IApp* instance_;

	void* window_ = nullptr;

	GameTimer timer_;

	bool bIsQuit_ = false;
	bool bIsResize_ = false;
	bool bIsMaximize_ = false;
	bool bIsMinimize_ = false;
	bool bIsEnterMouse_ = false; /** ���콺�� ������ ���ο� �ִ��� Ȯ�� */
	bool bIsGainFocus_ = true;

	KeyboardState prevKeyboardState_;
	KeyboardState currKeyboardState_;
	MouseState prevMouseState_;
	MouseState currMouseState_;

	static const uint32_t MAX_EVENT_ACTION_SIZE = 200;
	uint32_t windowEventActionSize_ = 0;
	std::array<WindowEventAction, MAX_EVENT_ACTION_SIZE> windowEventActions_;
};