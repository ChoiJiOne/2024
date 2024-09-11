#pragma once

#include <string>

#include "GameMath.h"

#include "Entity2D.h"

class Player;
class TTFont;

class PlayerMessenger : public Entity2D
{
public:
	PlayerMessenger();
	virtual ~PlayerMessenger();

	DISALLOW_COPY_AND_ASSIGN(PlayerMessenger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Send(const std::wstring& message, const GameMath::Vec4f& color, float time);
	void Reset();

private:
	void CalcMessagePosFromPlayer();

private:
	Player* player_ = nullptr;
	TTFont* font_ = nullptr;

	bool bIsDetectMessage_ = false;

	std::wstring message_;
	GameMath::Vec2f messageSize_;
	GameMath::Vec2f messagePos_;
	GameMath::Vec4f messageColor_;
	float remainTime_ = 0.0f;
	float messageTime_ = 0.0f;
};