#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

class TTFont;

class Score : public IEntity2D
{
public:
	Score();
	virtual ~Score();

	DISALLOW_COPY_AND_ASSIGN(Score);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	int32_t GetScore() const { return score_; }
	void SetScore(int32_t score);

private:
	TTFont* font_ = nullptr;
	
	std::wstring text_;
	Vec2f textPos_;
	Vec4f textColor_;

	int32_t score_ = 0;
	bool bIsUpdateScore_ = false;
};