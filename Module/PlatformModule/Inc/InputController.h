#pragma once

#include <array>
#include <functional>
#include <windows.h>


/**
 * @brief �Է� ���¸� ��Ÿ���ϴ�.
 *
 * @note �����ӿ� ���� �Է� �����Դϴ�.
 * --------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPressState : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};


/**
 * @brief Ű ���Դϴ�.
 *
 * @see https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */
enum class EKey : int32_t
{
	KEY_NONE = 0x00,
	KEY_LBUTTON = 0x01,
	KEY_RBUTTON = 0x02,
	KEY_CANCEL = 0x03,
	KEY_MBUTTON = 0x04,
	KEY_XBUTTON1 = 0x05,
	KEY_XBUTTON2 = 0x06,
	KEY_BACK = 0x08,
	KEY_TAB = 0x09,
	KEY_CLEAR = 0x0C,
	KEY_RETURN = 0x0D,
	KEY_SHIFT = 0x10,
	KEY_CONTROL = 0x11,
	KEY_MENU = 0x12,
	KEY_PAUSE = 0x13,
	KEY_CAPITAL = 0x14,
	KEY_KANA = 0x15,
	KEY_HANGUEL = 0x15,
	KEY_HANGUL = 0x15,
	KEY_IME_ON = 0x16,
	KEY_JUNJA = 0x17,
	KEY_FINAL = 0x18,
	KEY_HANJA = 0x19,
	KEY_KANJI = 0x19,
	KEY_IME_OFF = 0x1A,
	KEY_ESCAPE = 0x1B,
	KEY_CONVERT = 0x1C,
	KEY_NONCONVERT = 0x1D,
	KEY_ACCEPT = 0x1E,
	KEY_MODECHANGE = 0x1F,
	KEY_SPACE = 0x20,
	KEY_PRIOR = 0x21,
	KEY_NEXT = 0x22,
	KEY_END = 0x23,
	KEY_HOME = 0x24,
	KEY_LEFT = 0x25,
	KEY_UP = 0x26,
	KEY_RIGHT = 0x27,
	KEY_DOWN = 0x28,
	KEY_SELECT = 0x29,
	KEY_PRINT = 0x2A,
	KEY_EXECUTION = 0x2B,
	KEY_SNAPSHOT = 0x2C,
	KEY_INSERT = 0x2D,
	KEY_DELETE = 0x2E,
	KEY_HELP = 0x2F,
	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,
	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,
	KEY_LWIN = 0x5B,
	KEY_RWIN = 0x5C,
	KEY_APPS = 0x5D,
	KEY_SLEEP = 0x5F,
	KEY_NUMPAD0 = 0x60,
	KEY_NUMPAD1 = 0x61,
	KEY_NUMPAD2 = 0x62,
	KEY_NUMPAD3 = 0x63,
	KEY_NUMPAD4 = 0x64,
	KEY_NUMPAD5 = 0x65,
	KEY_NUMPAD6 = 0x66,
	KEY_NUMPAD7 = 0x67,
	KEY_NUMPAD8 = 0x68,
	KEY_NUMPAD9 = 0x69,
	KEY_MULTIPLY = 0x6A,
	KEY_ADD = 0x6B,
	KEY_SEPARATOR = 0x6C,
	KEY_SUBTRACT = 0x6D,
	KEY_DECIMAL = 0x6E,
	KEY_DIVIDE = 0x6F,
	KEY_F1 = 0x70,
	KEY_F2 = 0x71,
	KEY_F3 = 0x72,
	KEY_F4 = 0x73,
	KEY_F5 = 0x74,
	KEY_F6 = 0x75,
	KEY_F7 = 0x76,
	KEY_F8 = 0x77,
	KEY_F9 = 0x78,
	KEY_F10 = 0x79,
	KEY_F11 = 0x7A,
	KEY_F12 = 0x7B,
	KEY_F13 = 0x7C,
	KEY_F14 = 0x7D,
	KEY_F15 = 0x7E,
	KEY_F16 = 0x7F,
	KEY_F17 = 0x80,
	KEY_F18 = 0x81,
	KEY_F19 = 0x82,
	KEY_F20 = 0x83,
	KEY_F21 = 0x84,
	KEY_F22 = 0x85,
	KEY_F23 = 0x86,
	KEY_F24 = 0x87,
	KEY_NUMLOCK = 0x90,
	KEY_SCROLL = 0x91,
	KEY_LSHIFT = 0xA0,
	KEY_RSHIFT = 0xA1,
	KEY_LCONTROL = 0xA2,
	KEY_RCONTROL = 0xA3,
	KEY_LMENU = 0xA4,
	KEY_RMENU = 0xA5,
	KEY_BROWSER_BACK = 0xA6,
	KEY_BROWSER_FORWARD = 0xA7,
	KEY_BROWSER_REFRESH = 0xA8,
	KEY_BROWSER_STOP = 0xA9,
	KEY_BROWSER_SEARCH = 0xAA,
	KEY_BROWSER_FAVORITES = 0xAB,
	KEY_BROWSER_HOME = 0xAC,
	KEY_VOLUME_MUTE = 0xAD,
	KEY_VOLUME_DOWN = 0xAE,
	KEY_VOLUME_UP = 0xAF,
	KEY_MEDIA_NEXT_TRACK = 0xB0,
	KEY_MEDIA_PREV_TRACK = 0xB1,
	KEY_MEDIA_STOP = 0xB2,
	KEY_MEDIA_PLAY_PAUSE = 0xB3,
	KEY_LAUNCH_MAIL = 0xB4,
	KEY_LAUNCH_MEDIA_SELECT = 0xB5,
	KEY_LAUNCH_APP1 = 0xB6,
	KEY_LAUNCH_APP2 = 0xB7,
	KEY_OEM_1 = 0xBA,
	KEY_OEM_PLUS = 0xBB,
	KEY_OEM_COMMA = 0xBC,
	KEY_OEM_MINUS = 0xBD,
	KEY_OEM_PERIOD = 0xBE,
	KEY_OEM_2 = 0xBF,
	KEY_OEM_3 = 0xC0,
	KEY_OEM_4 = 0xDB,
	KEY_OEM_5 = 0xDC,
	KEY_OEM_6 = 0xDD,
	KEY_OEM_7 = 0xDE,
	KEY_OEM_8 = 0xDF,
	KEY_OEM_102 = 0xE2,
	KEY_PACKET = 0xE7,
	KEY_ATTN = 0xF6,
	KEY_CRSEL = 0xF7,
	KEY_EXSEL = 0xF8,
	KEY_EREOF = 0xF9,
	KEY_PLAY = 0xFA,
	KEY_ZOOM = 0xFB,
	KEY_NONAME = 0xFC,
	KEY_PA1 = 0xFD,
	KEY_OEM_CLEAR = 0xFE,
};


/**
 * @brief ������ �̺�Ʈ�Դϴ�.
 */
enum class EWindowEvent : int32_t
{
	NONE         = 0x0000,
	FOCUS_GAIN   = 0x0001,
	FOCUS_LOST   = 0x0002,
	CLOSE        = 0x0003,
	MOVE         = 0x0004,
	RESIZE       = 0x0005,
	ENTER_RESIZE = 0x0006,
	EXIT_RESIZE  = 0x0007,
	ENTER_MIN    = 0x0008,
	EXIT_MIN     = 0x0009,
	ENTER_MAX    = 0x000A,
	EXIT_MAX     = 0x000B,
};


/**
 * @brief ������ �̺�Ʈ�� Ű ���Դϴ�.
 */
using WindowEventID = int32_t;


/**
 * @brief ���� Ÿ���� ���콺 Ŀ�� ��ġ�Դϴ�.
 */
struct CursorPos
{
	int32_t x;
	int32_t y;
};


/**
 * @brief �Է� ó���� �����ϴ� ��Ʈ�ѷ��Դϴ�.
 * 
 * @note �� Ŭ������ ��� ��� ������ �޼���� ��� ����(static) Ÿ���Դϴ�.
 */
class InputController
{
public:
	/**
	 * @brief ���� Ű�� �Է� ���¸� Ȯ���մϴ�.
	 *
	 * @param keyCode �Է� ���¸� Ȯ���� Ű�� �ڵ尪�Դϴ�.
	 *
	 * @return Ű�� �Է� ���¸� ��ȯ�մϴ�.
	 */
	static EPressState GetKeyPressState(const EKey& keyCode);


	/**
	 * @brief ���콺�� ���� ��ġ�� ����ϴ�.
	 *
	 * @return ���콺�� ���� ��ġ���� ��ȯ�մϴ�.
	 */
	static CursorPos GetPrevCursorPos() { return prevCursorPosition; }


	/**
	 * @brief ���콺�� ���� ��ġ�� ����ϴ�.
	 *
	 * @return ���콺�� ���� ��ġ���� ��ȯ�մϴ�.
	 */
	static CursorPos GetCurrCursorPos() { return currCursorPosition; }


	/**
	 * @brief ������ �̺�Ʈ �׼��� �߰��մϴ�.
	 *
	 * @param windowEvent ������ �׼ǿ� �����ϴ� ������ �̺�Ʈ�Դϴ�.
	 * @param eventAction �̺�Ʈ �׼ǿ� �����ϴ� �׼��Դϴ�.
	 * @param bIsActive ������ �̺�Ʈ �׼� Ȱ��ȭ �����Դϴ�. �⺻ ���� true�Դϴ�.
	 *
	 * @return ������ �̺�Ʈ�� ID ���� ��ȯ�մϴ�.
	 */
	static WindowEventID AddWindowEventAction(const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive = true);


	/**
	 * @brief ������ �̺�Ʈ �׼��� �����մϴ�.
	 *
	 * @param windowEventID ������ �̺�Ʈ �׼��� ID ���Դϴ�.
	 *
	 * @note �ñ״�ó�� �����ϴ� ������ �̺�Ʈ�� �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	static void DeleteWindowEventAction(const WindowEventID& windowEventID);


	/**
	 * @brief ������ �̺�Ʈ �׼��� Ȱ��ȭ ���θ� �����մϴ�.
	 *
	 * @param windowEventID ������ �̺�Ʈ �׼��� ID ���Դϴ�.
	 * @param bIsActive ������ �̺�Ʈ�� Ȱ��ȭ �����Դϴ�.
	 *
	 * @note �ñ״�ó�� �����ϴ� ������ �̺�Ʈ�� �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	static void SetActiveWindowEventAction(const WindowEventID& windowEventID, bool bIsActive);


private:
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
	 * @brief �Է� ó�� ��Ʈ�ѷ��� ���� ���¸� ������Ʈ�մϴ�.
	 */
	static void Tick();


	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �׼ǵ��� �����մϴ�.
	 *
	 * @param signature ������ ������ �̺�Ʈ�Դϴ�.
	 */
	static void ExecuteWindowEventAction(const EWindowEvent& windowEvent);


	/**
	 * @brief Ư�� ���� Ű�� ���ȴ��� Ȯ���մϴ�.
	 *
	 * @param keyBufferPtr �˻縦 ������ ���� Ű ������ �������Դϴ�.
	 * @param keyCode ���ȴ��� Ȯ���� Ű �ڵ� ���Դϴ�.
	 *
	 * @return Ű�� ���ȴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsPressKey(const uint8_t* keyBufferPtr, const EKey& keyCode);


	/**
	 * @brief ���� ���콺 Ŀ���� ��ġ�� ����ϴ�.
	 *
	 * @return ������ ��ǥ�� ������ ���콺 ��ġ�� ��ȯ�մϴ�.
	 */
	static CursorPos GetCurrentCursorPosition();


	/**
	 * @brief �÷��� ����� ���θ� ������ �� �ֵ��� friend ���� �߰�
	 */
	friend class PlatformModule;


	/**
	 * @brief ������ ���ν��� �Լ��� PlatformModule ���θ� ������ �� �ֵ��� friend ���� �߰�
	 */
	friend LRESULT CALLBACK WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);


private:
	/**
	 * @brief Ű ������ ũ���Դϴ�.
	 */
	static const int32_t KEY_BUFFER_SIZE = 256;


	/**
	 * @brief ������Ʈ(Tick) ������ ���� Ű ������ �����Դϴ�.
	 */
	static std::array<uint8_t, KEY_BUFFER_SIZE> prevKeyboardState;


	/**
	 * @brief ������Ʈ(Tick) ������ ���� Ű ������ �����Դϴ�.
	 */
	static std::array<uint8_t, KEY_BUFFER_SIZE> currKeyboardState;


	/**
	 * @brief ������Ʈ(Tick) ������ Ŀ�� ��ġ�Դϴ�.
	 */
	static CursorPos prevCursorPosition;


	/**
	 * @brief ������Ʈ(Tick) ������ Ŀ�� ��ġ�Դϴ�.
	 */
	static CursorPos currCursorPosition;


	/**
	 * @brief �Է� ó�� �Ŵ����� �̺�Ʈ �׼� �迭�� ũ���Դϴ�.
	 */
	static uint32_t windowEventActionSize;


	/**
	 * @brief �Է� ó�� �Ŵ����� �̺�Ʈ �׼� �迭�� �ִ� ũ���Դϴ�.
	 */
	static const uint32_t MAX_EVENT_ACTION_SIZE = 100;


	/**
	 * @brief �Է� ó�� �Ŵ����� �̺�Ʈ �׼� �迭�Դϴ�.
	 */
	static std::array<WindowEventAction, MAX_EVENT_ACTION_SIZE> windowEventActions;
};