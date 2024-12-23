#pragma once

#include "Entity2D.h"

class TTFont;
class Player;

class Title : public Entity2D
{
public:
	Title();
	virtual ~Title();

	DISALLOW_COPY_AND_ASSIGN(Title);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	TTFont* font_ = nullptr;

	Vec2f textPos_;
	Vec4f textColor_;
	Vec2f textShadowPos_;
	Vec4f textShadowColor_;
	std::wstring text_;
};