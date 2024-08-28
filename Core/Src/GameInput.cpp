#include <array>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <SDL2/SDL.h>

#include "GameInput.h"

struct WindowEventAction
{
	bool				   bIsActive         = false;                        // ������ �̺�Ʈ�� Ȱ��ȭ �����Դϴ�.
	GameInput::WindowEvent windowEvent       = GameInput::WindowEvent::NONE; // ������ �̺�Ʈ�Դϴ�.
	std::function<void()>  windowEventAction = nullptr;                      // ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
};

struct KeyboardState
{
	static const int32_t BUFFER_SIZE = 512;        // Ű������ Ű �� ���¸� �����ϴ� ������ ũ���Դϴ�.
	std::array<uint8_t, BUFFER_SIZE> keybordState; // Ű������ Ű �� ���¸� �����ϴ� �����Դϴ�.
};

struct MouseState
{
	uint32_t state;           // ���콺 ��ư�� �����Դϴ�.
	GameMath::Vec2i position; // ���콺 ��ư�� ��ġ�Դϴ�.
};

extern bool bShouldCloseWindow_;

static KeyboardState prevKeyboardState_;
static KeyboardState currKeyboardState_;
static MouseState prevMouseState_;
static MouseState currMouseState_;

static const uint32_t MAX_EVENT_ACTION_SIZE = 200;
static uint32_t windowEventActionSize_ = 0;
static std::array<WindowEventAction, MAX_EVENT_ACTION_SIZE> windowEventActions_;

void ExecuteWindowEventAction(const GameInput::WindowEvent& windowEvent)
{
	for (int32_t index = 0; index < windowEventActionSize_; ++index)
	{
		if (windowEventActions_[index].windowEvent == windowEvent && windowEventActions_[index].bIsActive)
		{
			windowEventActions_[index].windowEventAction();
		}
	}
}

bool IsPressKey(const KeyboardState& keyboardState, const GameInput::Key & key)
{
	return keyboardState.keybordState.at(static_cast<int32_t>(key)) == 0 ? false : true;
}

bool IsPressMouse(const MouseState& mouseState, const GameInput::Mouse& mouse)
{
	return (mouseState.state & static_cast<uint32_t>(mouse)) == 0 ? false : true;
}

void GameInput::PollEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);

		if (e.type == SDL_QUIT)
		{
			bShouldCloseWindow_ = true;
		}

		WindowEvent windowEvent = static_cast<WindowEvent>(e.window.event);
		for (std::size_t index = 0; index < windowEventActionSize_; ++index)
		{
			if (windowEvent == windowEventActions_[index].windowEvent && windowEventActions_[index].bIsActive)
			{
				windowEventActions_[index].windowEventAction();
			}
		}
	}

	const void* currKeyboardState = reinterpret_cast<const void*>(SDL_GetKeyboardState(nullptr));

	std::memcpy(prevKeyboardState_.keybordState.data(), currKeyboardState_.keybordState.data(), KeyboardState::BUFFER_SIZE);
	std::memcpy(currKeyboardState_.keybordState.data(), currKeyboardState, KeyboardState::BUFFER_SIZE);

	prevMouseState_ = currMouseState_;
	currMouseState_.state = SDL_GetMouseState(&currMouseState_.position.x, &currMouseState_.position.y);
}

GameInput::Press GameInput::GetKeyPress(const Key& key)
{
	Press press = Press::NONE;

	if (IsPressKey(prevKeyboardState_, key))
	{
		if (IsPressKey(currKeyboardState_, key))
		{
			press = Press::HELD;
		}
		else
		{
			press = Press::RELEASED;
		}
	}
	else
	{
		if (IsPressKey(currKeyboardState_, key))
		{
			press = Press::PRESSED;
		}
		else
		{
			press = Press::NONE;
		}
	}

	return press;
}

GameInput::Press GameInput::GetMousePress(const Mouse& mouse)
{
	Press press = Press::NONE;

	if (IsPressMouse(prevMouseState_, mouse))
	{
		if (IsPressMouse(currMouseState_, mouse))
		{
			press = Press::HELD;
		}
		else
		{
			press = Press::RELEASED;
		}
	}
	else
	{
		if (IsPressMouse(currMouseState_, mouse))
		{
			press = Press::PRESSED;
		}
		else
		{
			press = Press::NONE;
		}
	}

	return press;
}

const GameMath::Vec2i& GameInput::GetPrevMousePos()
{
	return prevMouseState_.position;
}

const GameMath::Vec2i& GameInput::GetCurrMousePos()
{
	return currMouseState_.position;
}

GameInput::WindowEventID GameInput::AddWindowEventAction(const WindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive)
{
	WindowEventID windowEventID = -1;
	for (int32_t index = 0; index < windowEventActionSize_; ++index)
	{
		if (windowEventActions_[index].windowEvent == WindowEvent::NONE)
		{
			windowEventID = static_cast<WindowEventID>(index);
			break;
		}
	}

	if (windowEventID == -1)
	{
		windowEventID = windowEventActionSize_++;
	}

	windowEventActions_[windowEventID].windowEvent = windowEvent;
	windowEventActions_[windowEventID].windowEventAction = eventAction;
	windowEventActions_[windowEventID].bIsActive = bIsActive;

	return windowEventID;
}

void GameInput::DeleteWindowEventAction(const WindowEventID& windowEventID)
{
	windowEventActions_[windowEventID].windowEvent = WindowEvent::NONE;
	windowEventActions_[windowEventID].windowEventAction = nullptr;
	windowEventActions_[windowEventID].bIsActive = false;
}

void GameInput::SetActiveWindowEventAction(const WindowEventID& windowEventID, bool bIsActive)
{
	windowEventActions_[windowEventID].bIsActive = bIsActive;
}