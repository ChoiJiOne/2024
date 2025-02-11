#include "GeometryRenderer3D.h"
#include "RenderModule.h"

#include "Grid.h"

Grid::Grid(GeometryRenderer3D* renderer)
	: renderer_(renderer)
	, size_(Vec3f(100.0f, 100.0f, 100.0f))
	, stride_(1.0f)
{
}

Grid::~Grid()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Grid::Tick(float deltaSeconds)
{
}

void Grid::Render()
{
	renderer_->DrawGrid3D(size_, stride_);
}

void Grid::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}