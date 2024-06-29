#pragma once

#include <functional>


namespace GameMaker
{
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
	 */
	static void Init();


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
	static void* GetGameWindow() { return gameWindow_; }


	/**
	 * @brief ���� ���� ���θ� �����մϴ�.
	 *
	 * @param bIsQuit ������ ���� ���� �����Դϴ�. ������ �����ϰ� �ʹٸ� true, �׷��� ������ false�Դϴ�.
	 */
	static void SetQuitLoop(bool bIsQuit) { bIsQuitLoop_ = bIsQuit; }


private:
	/**
	 * @brief ���� ������ �ʱ�ȭ �Ǿ����� Ȯ���մϴ�.
	 */
	static bool bIsInit_;


	/**
	 * @brief ���� �������� �������Դϴ�.
	 */
	static void* gameWindow_;


	/**
	 * @brief ������ ������ �� �����Դϴ�.
	 */
	static bool bIsQuitLoop_;


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