#pragma once

#include <string>

#include "Entity2D.h"

class TTFont;

class GameOver : public Entity2D
{
public:
	GameOver();
	virtual ~GameOver();

	DISALLOW_COPY_AND_ASSIGN(GameOver);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	TTFont* font_ = nullptr;

	float time_ = 0.0f;
	float maxTime_ = 0.0f;
	float moveLength_ = 0.0f;

	std::wstring text_;
	GameMath::Vec2f textSize_;
	GameMath::Vec2f textPos_;
	GameMath::Vec2f textOriginPos_;
	GameMath::Vec4f textColor_;

	GameMath::Vec2f shadowPos_;
	GameMath::Vec2f shadowOffset_;
	GameMath::Vec4f shadowColor_;
};