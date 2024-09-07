#pragma once

#include <functional>
#include <map>

#include "Collision2D.h"
#include "IApp.h"

#include "Entity2D.h"

class TTFont;

class Button : public Entity2D
{
public:
	struct Layout
	{
		GameMath::Vec4f textColor;
		GameMath::Vec4f disableColor;
		GameMath::Vec4f enableColor;
		GameMath::Vec4f pressColor;
		GameMath::Vec4f releaseColor;

		GameMath::Vec2f center;
		GameMath::Vec2f size;
		Mouse mouse;

		TTFont* font;
		std::wstring text;
		float side;
	};

public:
	Button(const Layout& layout, const std::function<void()>& clickEvent);
	virtual ~Button();

	DISALLOW_COPY_AND_ASSIGN(Button);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	enum class State : int32_t
	{
		DISABLED = 0x00,
		ENABLED  = 0x01,
		PRESSED  = 0x02,
		RELEASED = 0x03,
	};

	State GetState(const Press& press, const State& state);
	bool IsDetectMouseCursor();

private:
	IApp* app_ = nullptr;

	Layout layout_;
	Rect2D bound_;
	State state_ = State::DISABLED;

	GameMath::Vec2f textPos_;

	std::function<void()> clickEvent_ = nullptr;

	std::map<State, GameMath::Vec4f> stateColors_;
};