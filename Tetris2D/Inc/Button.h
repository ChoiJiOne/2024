#pragma once

#include <functional>
#include <map>

#include "Collision2D.h"
#include "IApp.h"

#include "IEntity2D.h"

class TTFont;

class Button : public IEntity2D
{
public:
	struct Layout
	{
		Vec4f textColor;
		Vec4f disableColor;
		Vec4f enableColor;
		Vec4f pressColor;
		Vec4f releaseColor;

		Vec2f center;
		Vec2f size;
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

	static Button* CreateFromFile(const std::string& path, const Mouse& mouse, TTFont* font, const std::function<void()>& clickEvent);

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

	Vec2f textPos_;

	std::function<void()> clickEvent_ = nullptr;

	std::map<State, Vec4f> stateColors_;
};