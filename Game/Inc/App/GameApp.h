#pragma once

#include "IApp.h"

/** 게임 애플리케이션입니다. */
class GameApp : public IApp
{
public:
	GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered);
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;
};