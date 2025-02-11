#pragma once

#include "Entity2D.h"

class TTFont;
class Player;

class CoinViewer : public Entity2D
{
public:
	CoinViewer();
	virtual ~CoinViewer();

	DISALLOW_COPY_AND_ASSIGN(CoinViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();

private:
	Player* player_ = nullptr;
	TTFont* font_ = nullptr;

	int32_t numCoin_ = -1;

	Vec2f textCenter_;
	Vec2f textPos_;
	Vec4f textColor_;
	Vec2f textShadowPos_;
	Vec4f textShadowColor_;
	std::wstring text_;
};