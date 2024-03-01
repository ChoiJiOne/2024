#include "MathModule.h"

#include "Assertion.h"
#include "Pipe.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Texture2D.h"

float Pipe::gap_ = 150.0f;
Vec2f Pipe::startLocation_;
Vec2f Pipe::endLocation_;

Pipe::Pipe(float speed)
	: bCanMove_(true)
	, speed_(speed)
	, status_(EStatus::Wait)
{
	static float pipeW = 80.0f;
	static float pipeH = 600.0f;
	static float maxHeight = 640.0f;

	float y = MathModule::GenerateRandomFloat(gap_, maxHeight - gap_);

	topBound_ = BoundBox2D(Vec2f(startLocation_.x, y - 0.5f * (gap_ + pipeH)), pipeW, pipeH);
	bottomBound_ = BoundBox2D(Vec2f(startLocation_.x, y + 0.5f * (gap_ + pipeH)), pipeW, pipeH);

	static RUID textureID = ResourceManager::Get().Create<Texture2D>("Resource/Texture/Pipe.png");
	textureID_ = textureID;

	bIsInitialized_ = true;
}

Pipe::~Pipe()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Pipe::Tick(float deltaSeconds)
{
	if (bCanMove_)
	{
		Vec2f topCenter = topBound_.GetCenter();
		topCenter.x -= speed_ * deltaSeconds;
		topBound_.SetCenter(topCenter);

		Vec2f bottomCenter = bottomBound_.GetCenter();
		bottomCenter.x -= speed_ * deltaSeconds;
		bottomBound_.SetCenter(bottomCenter);

		if (topCenter.x <= endLocation_.x || bottomCenter.x <= endLocation_.x)
		{
			status_ = EStatus::Done;
		}
	}
}

void Pipe::Render()
{
	RenderManager::Get().RenderSprite2D(textureID_, topBound_.GetCenter(), topBound_.GetWidth(), topBound_.GetHeight(), MathModule::Pi);
	RenderManager::Get().RenderSprite2D(textureID_, bottomBound_.GetCenter(), bottomBound_.GetWidth(), bottomBound_.GetHeight(), 0.0f);
}

void Pipe::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}