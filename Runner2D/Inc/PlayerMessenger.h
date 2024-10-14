#pragma once

#include <string>

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

	void Send(const std::wstring& message, const Vec4f& color, float time);

private:
	void CalcMessagePosFromPlayer();

private:
	Player* player_ = nullptr;
	TTFont* font_ = nullptr;

	bool bIsDetectMessage_ = false;

	std::wstring message_; 
	Vec2f messageSize_;
	Vec2f messagePos_;
	Vec4f messageColor_;
	float remainTime_ = 0.0f;
	float messageTime_ = 0.0f;
};