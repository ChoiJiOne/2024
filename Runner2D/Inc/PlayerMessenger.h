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

private:
	Player* player_ = nullptr;
	TTFont* font_ = nullptr;

	bool bIsDetectMessage_ = false;
};