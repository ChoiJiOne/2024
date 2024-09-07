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

	GameMath::Vec2f position_;
	GameMath::Vec2f shadowPosition_;

	GameMath::Vec4f titleColor_;
	GameMath::Vec4f shadowColor_;
};