#pragma once

#include <functional>
#include <list>

#include "IEntity2D.h"
#include "GameMath.h"

class TTFont;

class Messenger : public IEntity2D
{
public:
	Messenger();
	virtual ~Messenger();

	DISALLOW_COPY_AND_ASSIGN(Messenger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();
	void Send(const std::wstring& text, const Vec2f& position, const Vec3f& color, float time);

private:
	struct Message
	{
		std::wstring text;
		Vec2f position;
		Vec4f color;
		float time = 0.0f;
		float remainTime = 0.0f;
	};

private:
	TTFont* font_ = nullptr;

	std::list<Message> messages_;
	std::function<bool(const Message&)> removeEvent_;
};
