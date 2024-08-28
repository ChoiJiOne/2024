#pragma once

#include <string>


enum class ErrorCode : int32_t
{
	OK                  = 0x00,
	FAILED              = 0x01, /** �Ϲ����� ���� */
	FAILED_STARTUP      = 0x02,
	FAILED_SHUTDOWN     = 0x03,
	FAILED_SDL          = 0x04, /** SDL2 ���̺귯�� ���� */
	FAILED_WINDOWS      = 0x05, /** Windows API ���� */
	BUFFER_OUT_OF_RANGE = 0x06, /** �迭�� ������ ��� ���� */
};

class GameError
{
public:
	GameError() {}
	GameError(const ErrorCode& errorCode, const std::string message) : errorCode_(errorCode), message_(message) {}
	GameError(GameError&& instance) noexcept : errorCode_(instance.errorCode_), message_(instance.message_) {}
	GameError(const GameError& instance) noexcept : errorCode_(instance.errorCode_), message_(instance.message_) {}

	virtual ~GameError() {}

	GameError& operator=(GameError&& instance) noexcept
	{
		if (this == &instance) return *this;

		errorCode_ = instance.errorCode_;
		message_ = instance.message_;

		return *this;
	}

	GameError& operator=(const GameError& instance) noexcept
	{
		if (this == &instance) return *this;

		errorCode_ = instance.errorCode_;
		message_ = instance.message_;

		return *this;
	}

	const ErrorCode& GetCode() const { return errorCode_; }
	const std::string& GetMessage() const { return message_; }
	
protected:
	ErrorCode errorCode_ = ErrorCode::OK;
	std::string message_;
};

#if defined(SDL_h_) /** SDL�� ���� �Ǿ��� ��. */
#include <SDL2/SDL.h>
class SDLError : public GameError
{
public:
	SDLError() : GameError(ErrorCode::FAILED_SDL, SDL_GetError()) {}
	virtual ~SDLError() {}
};
#endif

#if defined(_WIN32) || defined(_WIN64) /** Windows OS����. */
#include <windows.h>
class WindowsError : public GameError
{
public:
	WindowsError() : GameError(ErrorCode::FAILED_WINDOWS, GetErrorMessage()) {}
	virtual ~WindowsError() {}

private:
	static std::string GetErrorMessage()
	{
		static const uint32_t MAX_BUFFER_SIZE = 1024;
		static char buffer[MAX_BUFFER_SIZE];

		uint32_t size = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, MAX_BUFFER_SIZE, nullptr);

		return std::string(buffer, size);
	}
};
#endif