#pragma once

#include "Entity2D.h"

class TTFont;
class Player;

class CountDowner : public Entity2D
{
public:
	CountDowner();
	virtual ~CountDowner();

	DISALLOW_COPY_AND_ASSIGN(CountDowner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	float GetTime() const { return time_; }
	void SetTime(float time) { time_ = time; }

	void Reset();

private:
	Player* player_ = nullptr;
	TTFont* font_ = nullptr;

	float time_ = 0.0f;
	int32_t remainTime_ = 0;

	GameMath::Vec2f textCenter_;
	GameMath::Vec2f textPos_;
	GameMath::Vec4f textColor_;
	GameMath::Vec2f textShadowPos_;
	GameMath::Vec4f textShadowColor_;
	std::wstring text_;
};