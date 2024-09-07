#pragma once

#include <functional>

#include "Collision2D.h"

#include "Entity2D.h"

class IApp;
class TTFont;

class Button : public Entity2D
{
public:
	enum class Type
	{
		LEFT   = (1 << ((1) - 1)),
		MIDDLE = (1 << ((2) - 1)),
		RIGHT  = (1 << ((3) - 1)),
	};

public:
	Button();
	virtual ~Button();

	DISALLOW_COPY_AND_ASSIGN(Button);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	IApp* app_ = nullptr;
};