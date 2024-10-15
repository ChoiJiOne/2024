#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

class TTFont;

class Title : public IEntity2D
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

	std::wstring text_;
	Vec2f textPos_;
	Vec4f textColor_;
};