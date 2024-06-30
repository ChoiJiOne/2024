#pragma once

#include <functional>
#include <string>


namespace GameMaker
{
/**
 * @brief ������ ���� �ɼ��Դϴ�.
 * 
 * @note Ǯ ��ũ������ �����ϸ� �������� �Ϻ� �ɼ��� ���õ˴ϴ�.
 */
struct WindowParam
{
	std::string title;
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
	bool bIsResizble = false; // �������� ũ�� ���� �����Դϴ�. �⺻ ���� false�Դϴ�.
	bool bIsFullscreen = false; // Ǯ ��ũ�� �����Դϴ�. �⺻ ���� false�Դϴ�.
};


/**
 * @brief ���� ���� Ŭ�����Դϴ�.
 *
 * @note �� Ŭ������ ��� ��� �Լ� �� ������ ��� ����(static) Ÿ���Դϴ�.
 */
class GameEngine
{
public:
	/**
	 * @brief ���� ������ �ʱ�ȭ�մϴ�.
	 * 
	 * @param param ������ ���� �� ������ �Ķ�����Դϴ�.
	 */
	static void Init(const WindowParam& param);


	/**
	 * @brief ���� ������ �ʱ�ȭ�� �����մϴ�.
	 */
	static void Shutdown();


	/**
	 * @brief ���� ������ ������ �����մϴ�.
	 *
	 * @param callback ���� ���� �� ȣ���� ������ ������ �ݹ� �Լ��Դϴ�.
	 */
	static void RunLoop(const std::function<void(float)>& callback);


	/**
	 * @brief ���� ���� ���� �� ȣ���� �ݹ� �Լ��� �����մϴ�.
	 *
	 * @param callback ���� ���� ���� �� ȣ���� �ݹ� �Լ��Դϴ�.
	 */
	static void SetEndLoopCallback(const std::function<void()>& callback) { endLoopCallback_ = callback; }


	/**
	 * @brief ���� �������� �����͸� ����ϴ�.
	 *
	 * @return ���� �������� �����͸� ��ȯ�մϴ�.
	 */
	static void* GetGameWindow() { return window_; }


	/**
	 * @brief ���� ������ ���� ���θ� �����մϴ�.
	 *
	 * @param bShouldCloseWindow ������ ���� ������ ���� �����Դϴ�. �����ϰ� �ʹٸ� true, �׷��� ������ false�Դϴ�.
	 */
	static void SetShouldCloseWindow(bool bShouldCloseWindow) { bShouldCloseWindow_ = bShouldCloseWindow; }


private:
	/**
	 * @brief ���� ������ ���� �ý����� �ʱ�ȭ�մϴ�.
	 */
	static void InitSubSystem();


private:
	/**
	 * @brief ���� ������ �ʱ�ȭ �Ǿ����� Ȯ���մϴ�.
	 */
	static bool bIsInit_;


	/**
	 * @brief ���� �������� �������Դϴ�.
	 */
	static void* window_;


	/**
	 * @brief ���� ������ ���� �����Դϴ�.
	 */
	static bool bShouldCloseWindow_;


	/**
	 * @brief ���� ���� ���� �� ������ �ݹ� �Լ��Դϴ�.
	 */
	static std::function<void()> endLoopCallback_;


	/**
	 * @brief ���� ���� �� ȣ���� ������ ������ �ݹ� �Լ��Դϴ�.
	 */
	static std::function<void(float)> frameCallback_;
};

}