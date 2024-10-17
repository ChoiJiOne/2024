#pragma once

#include "IGameScene2D.h"

class TitleScene2D : public IGameScene2D
{
public:
	TitleScene2D();
	virtual ~TitleScene2D();

	DISALLOW_COPY_AND_ASSIGN(TitleScene2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;
};