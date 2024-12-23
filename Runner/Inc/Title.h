#pragma once

#include <string>

#include "Entity2D.h"
#include "GameMath.h"

class TTFont;

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
	std::wstring title_;

	Vec2f position_;
	Vec2f shadowPosition_;

	Vec4f titleColor_;
	Vec4f shadowColor_;
};