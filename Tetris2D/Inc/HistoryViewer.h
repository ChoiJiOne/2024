#pragma once

#include <array>

#include "Collision2D.h"
#include "IEntity2D.h"

class GameHistoryTracker;
class TTFont;

class HistoryViewer : public IEntity2D
{
public:
	HistoryViewer();
	virtual ~HistoryViewer();

	DISALLOW_COPY_AND_ASSIGN(HistoryViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void UpdateRecentHistory();

private:
	TTFont* font_ = nullptr;
	GameHistoryTracker* gameHistoryTracker_ = nullptr;

	Rect2D background_;
	Vec4f backgroundColor_;
	float backgroundSide_ = 0.0f;

	Vec2f startHistoryTextPos_;
	Vec4f historyTextColor_;
	float historyTextStride_ = 0.0f;

	static const uint32_t MAX_VIEW_HISTORY = 10;
	uint32_t currentHistoryTextSize_ = 0;
	std::array<std::wstring, MAX_VIEW_HISTORY> historyTexts_;
};