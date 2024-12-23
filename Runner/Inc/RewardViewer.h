#pragma once

#include <string>

#include "Entity2D.h"

class Atlas2D;
class Player;
class TTFont;

class RewardViewer : public Entity2D
{
public:
	RewardViewer();
	virtual ~RewardViewer();

	DISALLOW_COPY_AND_ASSIGN(RewardViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Atlas2D* atlas_ = nullptr;
	TTFont* font_ = nullptr;
	Player* player_ = nullptr;

	int32_t numPickupCherry_ = -1;
	int32_t numPickupGem_ = -1;

	Vec2f spriteSize_;
	Vec2f cherrySpritePos_;
	Vec2f gemSpritePos_;

	Vec4f textColor_ = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	std::wstring pickupCherryText_;
	Vec2f pickupCherryTextPos_;
	std::wstring pickupGemText_;
	Vec2f pickupGemTextPos_;

	Vec2f backgroundPos_;
	Vec2f backgroundSize_;
	Vec4f backgroundColor_;
	float backgroundSide_ = 0.0f;
};