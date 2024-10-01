#include "Assertion.h"
#include "RenderManager2D.h"

#include "Board.h"

Board::Board()
{
	bIsInitialized_ = true;
}

Board::~Board()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Board::Tick(float deltaSeconds)
{
}

void Board::Render()
{
}

void Board::Release()
{
	CHECK(bIsInitialized_);

	bIsInitialized_ = false;
}
