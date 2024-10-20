#pragma once

#include "Collision2D.h"
#include "IEntity2D.h"
#include "GameMath.h"

class Next : public IEntity2D
{
public:
	Next();
	virtual ~Next();

	DISALLOW_COPY_AND_ASSIGN(Next);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Vec4f backgroundColor_;
	Vec4f lineColor_;
	Rect2D background_;
	std::vector<Vec2f> lines_;
};