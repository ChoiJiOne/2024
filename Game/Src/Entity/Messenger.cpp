#include "Entity/Messenger.h"
#include "GL/GLManager.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"

Messenger::Messenger(UICamera* uiCamera, TTFont* font)
	: uiCamera_(uiCamera)
	, font_(font)
{
	tickOrder_ = 3;
	renderOrder_ = 3;

	messageRemoveEvent_ = [&](const Message& message) { return message.remainTime <= 0.0f; };

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
		message.textColor.a = message.remainTime / message.time;
	}

	messages_.remove_if(messageRemoveEvent_);
}

void Messenger::Render()
{
}

void Messenger::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}

void Messenger::Send(const std::wstring& text, const glm::vec2& centerPos, const glm::vec4& color, float time)
{
	Message message;
	message.text = text;
	message.textBasePos = font_->MeasureBasePos(text, centerPos);
	message.textColor = color;
	message.time = time;
	message.remainTime = time;
	
	messages_.push_back(message);
}