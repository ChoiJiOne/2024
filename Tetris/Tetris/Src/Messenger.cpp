#include "Assertion.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "TTFont.h"

#include "Messenger.h"

Messenger::Messenger()
{
	font_ = ResourceManager::GetRef().GetByName<TTFont>("Font32");
	removeEvent_ = [&](const Message& message) { return message.remainTime <= 0.0f; };

	bIsInitialized_ = true;
}

Messenger::~Messenger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Messenger::Tick(float deltaSeconds)
{
	for (auto& message : messages_)
	{
		message.remainTime -= deltaSeconds;
		message.color.w = message.remainTime / message.time;
	}

	messages_.remove_if(removeEvent_);
}

void Messenger::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::GetRef();
	for (const auto& message : messages_)
	{
		renderMgr.DrawString(font_, message.text, message.position, message.color);
	}
}

void Messenger::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void Messenger::Reset()
{
	messages_.clear();
}

void Messenger::Send(const std::wstring& text, const Vec2f& position, const Vec3f& color, float time)
{
	Vec2f textSize;
	font_->MeasureText(text, textSize.x, textSize.y);

	Message message;
	message.text = text;
	message.position = position + Vec2f(-0.5f * textSize.x, +0.5f * textSize.y);
	message.color = Vec4f(color.x, color.y, color.z, 1.0f);
	message.time = time;
	message.remainTime = time;

	messages_.push_back(message);
}