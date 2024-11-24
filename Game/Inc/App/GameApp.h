#pragma once

#include "IApp.h"

class FrameBuffer;

/** 게임 애플리케이션입니다. */
class GameApp : public IApp
{
public:
	GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered);
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

	/** 게임 앱의 프레임 버퍼를 얻습니다. */
	FrameBuffer* GetFrameBuffer() { return frameBuffer_; }

private:
	/** 전체 게임 씬에 렌더링되는 프레임버퍼입니다. */
	FrameBuffer* frameBuffer_ = nullptr;
};