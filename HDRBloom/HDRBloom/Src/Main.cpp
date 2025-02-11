#include <cstdint>
#include <Windows.h>

#include "Application.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->Init();
	app->Run();
	app.reset();
	return 0;
}