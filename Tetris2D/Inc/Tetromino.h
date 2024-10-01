#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

class Board;

class Tetromino : public IEntity2D
{
public:
	Tetromino();
	virtual ~Tetromino();

	DISALLOW_COPY_AND_ASSIGN(Tetromino);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	Board* board_ = nullptr;
};