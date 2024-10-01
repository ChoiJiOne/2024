#pragma once

#include "IEntity2D.h"

class Board : public IEntity2D
{
public:
	Board();
	virtual ~Board();

	DISALLOW_COPY_AND_ASSIGN(Board);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:

};