#pragma once

#include "IEntity2D.h"
#include "GameMath.h"

class TTFont;

class Messenger : public IEntity2D
{
public:
	Messenger();
	virtual ~Messenger();

	DISALLOW_COPY_AND_ASSIGN(Messenger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Send();

private:
	TTFont* font_ = nullptr;
};
