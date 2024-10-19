#pragma once

#include <string>

#include "Collision2D.h"
#include "IEntity2D.h"

class GameHistoryTracker;
class TTFont;

class HighScoreViewer : public IEntity2D
{
public:
	HighScoreViewer();
	virtual ~HighScoreViewer();

	DISALLOW_COPY_AND_ASSIGN(HighScoreViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void UpdateRecentState();

private:
	TTFont* font_ = nullptr;
	GameHistoryTracker* gameHistoryTracker_ = nullptr;

	Vec2f scoreTextPos_;
	Vec4f scoreTextColor_;
	Vec2f highScoreTextPos_;
	Vec4f highScoreTextColor_;

	Rect2D background_;
	Vec4f backgroundOutlineColor_;
	Vec4f backgroundColor_;
	float backgroundSide_;

	std::wstring scoreText_;
	std::wstring highScoreText_;
};