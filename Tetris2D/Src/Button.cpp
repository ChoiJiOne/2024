#include <json/json.h>

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

Button* Button::CreateFromFile(const std::string& path, const Mouse& mouse, TTFont* font, const std::function<void()>& clickEvent)
{
	std::vector<uint8_t> buffer = GameUtils::ReadFile(path);
	std::string jsonString(buffer.begin(), buffer.end());

	Json::Value root;
	Json::Reader reader;
	ASSERT(reader.parse(jsonString, root), "Failed to parse '%s' file.", path.c_str());

	auto getColorFromJson = [&](const std::string& color, Vec4f& outColor)
		{
			CHECK(!root[color].isNull());
			CHECK(!root[color]["r"].isNull() && !root[color]["g"].isNull() && !root[color]["b"].isNull() && !root[color]["a"].isNull());
			CHECK(root[color]["r"].isDouble() && root[color]["g"].isDouble() && root[color]["b"].isDouble() && root[color]["a"].isDouble());

			outColor = Vec4f(root[color]["r"].asFloat(), root[color]["g"].asFloat(), root[color]["b"].asFloat(), root[color]["a"].asFloat());
		};

	Vec4f textColor;
	getColorFromJson("textColor", textColor);

	Vec4f disableColor;
	getColorFromJson("disableColor", disableColor);

	Vec4f enableColor;
	getColorFromJson("enableColor", enableColor);

	Vec4f pressColor;
	getColorFromJson("pressColor", pressColor);

	Vec4f releaseColor;
	getColorFromJson("releaseColor", releaseColor);

	CHECK(!root["center"].isNull() && !root["center"]["x"].isNull() && !root["center"]["y"].isNull());
	CHECK(root["center"]["x"].isDouble() && root["center"]["y"].isDouble());
	Vec2f center(root["center"]["x"].asFloat(), root["center"]["y"].asFloat());

	CHECK(!root["size"].isNull() && !root["size"]["w"].isNull() && !root["size"]["h"].isNull());
	CHECK(root["size"]["w"].isDouble() && root["size"]["h"].isDouble());
	Vec2f size(root["size"]["w"].asFloat(), root["size"]["h"].asFloat());

	CHECK(!root["text"].isNull() && root["text"].isString());
	std::string text = root["text"].asString();

	CHECK(!root["side"].isNull() && root["side"].isDouble());
	float side = root["side"].asFloat();

	Layout layout;
	layout.textColor = textColor;
	layout.disableColor = disableColor;
	layout.enableColor = enableColor;
	layout.pressColor = pressColor;
	layout.releaseColor = releaseColor;
	layout.center = center;
	layout.size = size;
	layout.mouse = mouse;
	layout.font = font;
	layout.text = GameUtils::Convert(text);
	layout.side = side;

	return EntityManager::Get().Create<Button>(layout, clickEvent);
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