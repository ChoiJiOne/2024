#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

class Board;

class Tetromino : public IEntity2D
{
public:
	/** https://en.wikipedia.org/wiki/Tetromino */
	enum class EType
	{
		I = 0x00,
		O = 0x01,
		T = 0x02,
		J = 0x03,
		L = 0x04,
		S = 0x05,
		Z = 0x06,
	};

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