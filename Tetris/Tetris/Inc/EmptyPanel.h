#pragma once

#include "Collision2D.h"
#include "IEntity2D.h"

class EmptyPanel : public IEntity2D
{
public:
	EmptyPanel();
	virtual ~EmptyPanel();

	DISALLOW_COPY_AND_ASSIGN(EmptyPanel);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Rect2D bound_;
	float side_ = 0.0f;
	Vec4f color_;
};