#pragma once

#include <string>

#include "Entity2D.h"

class Player;
class TTFont;

class CountDowner : public Entity2D
{
public:
	CountDowner();
	virtual ~CountDowner();

	DISALLOW_COPY_AND_ASSIGN(CountDowner);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Start();

private:
	Player* player_ = nullptr;
	TTFont* font_ = nullptr;

	bool bIsStart_ = false;
	float time_ = 0.0f;
	int32_t remainTime_ = 0;

	Vec2f messageCenter_;
	Vec2f messagePos_;
	Vec4f messageColor_;
	std::wstring message_;
};