#pragma once

#include <functional>
#include <string>


namespace GameMaker
{
struct WindowParam
{
	std::string title;
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
	bool bIsResizble = false; /** �������� ũ�� ���� �����Դϴ�.�⺻ ���� false�Դϴ�. */
	bool bIsFullscreen = false; /** Ǯ ��ũ�� �����Դϴ�. �⺻ ���� false�Դϴ�. */
};

class GameEngine
{
public:
	static void Init(const WindowParam& param);
	static void Shutdown();
	static void RunLoop(const std::function<void(float)>& callback);

	static void SetEndLoopCallback(const std::function<void()>& callback) { endLoopCallback_ = callback; }
	static void* GetGameWindow() { return window_; }
	static void SetShouldCloseWindow(bool bShouldCloseWindow) { bShouldCloseWindow_ = bShouldCloseWindow; }

private:
	static void PreInit(); /** Init ȣ�� ������ ������ �ʱ�ȭ ���� */
	static void PostInit(); /** Init ȣ�� ���Ŀ� ������ �ʱ�ȭ ���� */
	
private:
	static bool bIsInit_;
	static void* window_;
	static bool bShouldCloseWindow_;
	static std::function<void()> endLoopCallback_;
	static std::function<void(float)> frameCallback_;
};

}