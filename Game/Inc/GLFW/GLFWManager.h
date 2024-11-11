#pragma once

#include <array>
#include <string>

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "Utils/Macro.h"

/**
 * --------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPress : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};

/** Ű �ڵ� ���Դϴ�. */
enum class EKey
{
	KEY_SPACE = 32,
	KEY_APOSTROPHE = 39,
	KEY_COMMA = 44,
	KEY_MINUS = 45,
	KEY_PERIOD = 46,
	KEY_SLASH = 47,
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_SEMICOLON = 59,
	KEY_EQUAL = 61,
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_LEFT_BRACKET = 91,
	KEY_BACKSLASH = 92,
	KEY_RIGHT_BRACKET = 93,
	KEY_GRAVE_ACCENT = 96,
	KEY_WORLD_1 = 161,
	KEY_WORLD_2 = 162,
	KEY_ESCAPE = 256,
	KEY_ENTER = 257,
	KEY_TAB = 258,
	KEY_BACKSPACE = 259,
	KEY_INSERT = 260,
	KEY_DELETE = 261,
	KEY_RIGHT = 262,
	KEY_LEFT = 263,
	KEY_DOWN = 264,
	KEY_UP = 265,
	KEY_PAGE_UP = 266,
	KEY_PAGE_DOWN = 267,
	KEY_HOME = 268,
	KEY_END = 269,
	KEY_CAPS_LOCK = 280,
	KEY_SCROLL_LOCK = 281,
	KEY_NUM_LOCK = 282,
	KEY_PRINT_SCREEN = 283,
	KEY_PAUSE = 284,
	KEY_F1 = 290,
	KEY_F2 = 291,
	KEY_F3 = 292,
	KEY_F4 = 293,
	KEY_F5 = 294,
	KEY_F6 = 295,
	KEY_F7 = 296,
	KEY_F8 = 297,
	KEY_F9 = 298,
	KEY_F10 = 299,
	KEY_F11 = 300,
	KEY_F12 = 301,
	KEY_F13 = 302,
	KEY_F14 = 303,
	KEY_F15 = 304,
	KEY_F16 = 305,
	KEY_F17 = 306,
	KEY_F18 = 307,
	KEY_F19 = 308,
	KEY_F20 = 309,
	KEY_F21 = 310,
	KEY_F22 = 311,
	KEY_F23 = 312,
	KEY_F24 = 313,
	KEY_F25 = 314,
	KEY_KP_0 = 320,
	KEY_KP_1 = 321,
	KEY_KP_2 = 322,
	KEY_KP_3 = 323,
	KEY_KP_4 = 324,
	KEY_KP_5 = 325,
	KEY_KP_6 = 326,
	KEY_KP_7 = 327,
	KEY_KP_8 = 328,
	KEY_KP_9 = 329,
	KEY_KP_DECIMAL = 330,
	KEY_KP_DIVIDE = 331,
	KEY_KP_MULTIPLY = 332,
	KEY_KP_SUBTRACT = 333,
	KEY_KP_ADD = 334,
	KEY_KP_ENTER = 335,
	KEY_KP_EQUAL = 336,
	KEY_LEFT_SHIFT = 340,
	KEY_LEFT_CONTROL = 341,
	KEY_LEFT_ALT = 342,
	KEY_LEFT_SUPER = 343,
	KEY_RIGHT_SHIFT = 344,
	KEY_RIGHT_CONTROL = 345,
	KEY_RIGHT_ALT = 346,
	KEY_RIGHT_SUPER = 347,
	KEY_MENU = 348
};

/**
 * GLFW ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GLFWManager& GetRef();
	
	/** GLFW �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GLFWManager* GetPtr();

	/** �ֱٿ� �߻��� GLFW ������ �����մϴ�. */
	void SetLsatError(int32_t code, const char* description);

	/** ���� �߻� ���θ� Ȯ���մϴ�. */
	bool IsDetectError() const { return bIsDetectError_; }

	/** GLFW ������ ���� �ڵ� ���� ����ϴ�. */
	const int32_t GetErrorCode() const { return errorCode_; }

	/** GLFW ������ ���� ������ C ��Ÿ�� ���ڿ��� ����ϴ�. */
	const char* GetErrorDescription() const { return errorDescription_.c_str(); }

	/** GLFW ������ ���� �޽����� C ��Ÿ�� ���ڿ��� ����ϴ�. */
	const char* GetErrorMessage() const { return errorMessage_.c_str(); }

	/** �� �������� �����մϴ�. */
	void Tick();

	/** Ŀ���� ������ ���ο� �ִ��� Ȯ���մϴ�. */
	bool IsEnterCursor() const { return bIsEnterCursor_; }

	/** ���� Ű ���� �Է� ���¸� ����ϴ�. */
	EPress GetKeyPress(const EKey& key);

	/** Tick ȣ�� ������ Ŀ�� ��ġ�� ����ϴ�. */
	const glm::vec2& GetPrevCursorPos() const { return prevCursorPos_; }

	/** Tick ȣ�� ������ Ŀ�� ��ġ�� ����ϴ�. */
	const glm::vec2& GetCurrCursorPos() const { return currCursorPos_; }
	
private:
	/** GameApp���� GLFWManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/** GLManager���� GLFWManager�� ���ο� ������ �� �ֵ��� ����. */
	friend class GLManager;

	/** GLFW ���� ó���� ���� �ݹ� �Լ��Դϴ�. */
	static void ErrorCallback(int32_t errorCode, const char* description);

	/** Ű���� �Է��� �����Ǿ��� �� ȣ��Ǵ� �ݹ� �Լ��Դϴ�. */
	static void KeyEventCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);

	/** ���콺 Ŀ���� ������ �� ȣ��Ǵ� �ݹ� �Լ��Դϴ�. */
	static void CursorMoveCallback(GLFWwindow* window, double x, double y);

	/** ���콺 Ŀ���� �������� �� ȣ��Ǵ� �ݹ��Լ��Դϴ�. */
	static void CursorEnterCallback(GLFWwindow* window, int32_t entered);

	/** ���콺 ��ư �Է��� �����Ǿ��� �� ȣ��Ǵ� �ݹ� �Լ��Դϴ�. */
	static void MouseButtonEventCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);

	/** Ŀ���� ������ â ���� ���θ� �����մϴ�. */
	void SetCursorEnter(int32_t entered);

	/** ���� Ŀ�� ��ġ�� �����մϴ�. */
	void SetCursorPosition(double x, double y);

	/** ���� Ű ���� ���� �����մϴ�. */
	void SetKeyboardState(int32_t key, int32_t action);

	/** Ű�� ���ȴ��� Ȯ���մϴ�. */
	bool IsPressKey(int32_t* keyboardState, const EKey& key);

	/**
	 * GLFW �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�. 
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

	/** GLFW �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup(int32_t width, int32_t height, const char* title);
	void Shutdown();
	
private:
	/** GLFW �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GLFWManager singleton_;

	/** GLFW �Ŵ����� �����ϴ� ���� �������Դϴ�. */
	GLFWwindow* mainWindow_ = nullptr;

	/** GLFW �Ŵ����� �����ϴ� ���� �������� ����/���� ũ���Դϴ�. */
	int32_t mainWindowWidth_ = 0;
	int32_t mainWindowHeight_ = 0;

	/** Ŀ���� ������ ���ο� �ִ��� Ȯ���մϴ�. */
	bool bIsEnterCursor_ = true;

	/** Tick ȣ�� ������ Ŀ�� ��ġ�Դϴ�. */
	glm::vec2 prevCursorPos_ = glm::vec2();

	/** Tick ȣ�� ������ Ŀ�� ��ġ�Դϴ�. */
	glm::vec2 currCursorPos_ = glm::vec2();

	/** Ű �迭�� �ִ� ���Դϴ�. */
	static const uint32_t KEY_BOARD_STATE_SIZE = 348;

	/** Tick ȣ�� ������ Ű �����Դϴ�. */
	std::array<int32_t, KEY_BOARD_STATE_SIZE> prevKeyboardState_;

	/** Tick ȣ�� ������ Ű �����Դϴ�. */
	std::array<int32_t, KEY_BOARD_STATE_SIZE> currKeyboardState_;

	/** GLFW ���� �߻� �����Դϴ�. */
	bool bIsDetectError_ = false;

	/**
	 * GLFW ���� �ڵ��Դϴ�.
	 * ����: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	int32_t errorCode_ = 0;

	/** GLFW ������ ���� ���� �Դϴ�. */
	std::string errorDescription_;

	/** GLFW ���� �޽����Դϴ�. */
	std::string errorMessage_;
};