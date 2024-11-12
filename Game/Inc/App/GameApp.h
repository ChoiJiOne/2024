#pragma once

#include "IApp.h"

/** 게임 애플리케이션입니다. */
class GameApp : public IApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	/** 게임 앱 윈도우의 가로 크기입니다. */
	static const uint32_t windowWidth_ = 1000;

	/** 게임 앱 윈도우의 세로 크기입니다. */
	static const uint32_t windowHeight_ = 800;

	/** 게임 앱 윈도우의 스크린에서 중앙에 위치할 지 여부입니다. */
	static const bool bIsWindowCentered_ = true;
};