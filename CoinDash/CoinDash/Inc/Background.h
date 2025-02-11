#pragma once

#include "Collision2D.h"
#include "Entity2D.h"

class Atlas2D;

class Background : public Entity2D
{
public:
	Background();
	virtual ~Background();

	DISALLOW_COPY_AND_ASSIGN(Background);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Atlas2D* atlas_ = nullptr;
	Rect2D rect_;
};