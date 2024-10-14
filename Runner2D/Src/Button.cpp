#include "Assertion.h"
#include "Atlas2D.h"
#include "EntityManager.h"
#include "IApp.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Button.h"

Button::Button(const Layout& layout, const std::function<void()>& clickEvent)
	: layout_(layout)
	, clickEvent_(clickEvent)
{
	app_ = IApp::Get();

	bound_ = Rect2D(layout_.center, layout_.size);

	Vec2f textSize;
	layout_.font->MeasureText(layout_.text, textSize.x, textSize.y);

	textPos_ = layout_.center + Vec2f(-textSize.x * 0.5f, +textSize.y * 0.5f);
	stateColors_ = 
	{
		{ State::DISABLED, layout_.disableColor },
		{ State::ENABLED,  layout_.enableColor  },
		{ State::PRESSED,  layout_.pressColor   },
		{ State::RELEASED, layout_.releaseColor },
	};

	bIsInitialized_ = true;
}

Button::~Button()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Button::Tick(float deltaSeconds)
{
	Press press = app_->GetMousePress(layout_.mouse);
	state_ = GetState(press, state_);

	if (state_ == State::RELEASED && clickEvent_)
	{
		clickEvent_();
	}
}

void Button::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::Get();

	renderMgr.DrawRoundRect(bound_.center, bound_.size.x, bound_.size.y, layout_.side, stateColors_.at(state_), 0.0f);
	renderMgr.DrawString(layout_.font, layout_.text, textPos_, layout_.textColor);
}

void Button::Release()
{
	CHECK(bIsInitialized_);

	app_ = nullptr;

	bIsInitialized_ = false;
}

Button::State Button::GetState(const Press& press, const State& state)
{
	if (!IsDetectMouseCursor())
	{
		if (state == State::PRESSED && press == Press::HELD)
		{
			return State::PRESSED;
		}
		else
		{
			return State::DISABLED;
		}
	}

	if (state == State::DISABLED)
	{
		if (press == Press::HELD || press == Press::PRESSED)
		{
			return State::DISABLED;
		}
		else // press == Press::NONE || press == Press::RELEASED
		{
			return State::ENABLED;
		}
	}
	else if (state == State::ENABLED)
	{
		if (press == Press::HELD || press == Press::PRESSED)
		{
			return State::PRESSED;
		}
		else
		{
			return State::ENABLED;
		}
	}
	else if (state == State::PRESSED)
	{
		if (press == Press::RELEASED)
		{
			return State::RELEASED;
		}
		else if (press == Press::HELD || press == Press::PRESSED)
		{
			return State::PRESSED;
		}
		else // press == Press::NONE
		{
			return State::ENABLED;
		}
	}
	else // state == State::RELEASED
	{
		if (press == Press::NONE || press == Press::RELEASED)
		{
			return State::ENABLED;
		}
		else // press == Press::HELD || press == Press::PRESSED
		{
			return State::PRESSED;
		}
	}

	return State::DISABLED;
}

bool Button::IsDetectMouseCursor()
{
	Vec2i currPos = app_->GetCurrMousePos();

	Vec2f screenSize;
	app_->GetScreenSize<float>(screenSize.x, screenSize.y);
	
	Point2D mouseCursor;
	mouseCursor.center.x = -screenSize.x * 0.5f + static_cast<float>(currPos.x);
	mouseCursor.center.y = +screenSize.y * 0.5f - static_cast<float>(currPos.y);
	
	return bound_.Intersect(&mouseCursor);
}