#pragma once

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
	Vec4f lineColor_;
	std::vector<Vec2f> lines_;
};