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

	GameMath::Vec2f spriteSize_;
	GameMath::Vec2f cherrySpritePos_;
	GameMath::Vec2f gemSpritePos_;

	GameMath::Vec4f textColor_ = GameMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	std::wstring pickupCherryText_;
	GameMath::Vec2f pickupCherryTextPos_;
	std::wstring pickupGemText_;
	GameMath::Vec2f pickupGemTextPos_;

	GameMath::Vec2f backgroundPos_;
	GameMath::Vec2f backgroundSize_;
	GameMath::Vec4f backgroundColor_;
	float backgroundSide_ = 0.0f;
};