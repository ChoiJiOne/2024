#pragma once

#include "IApp.h"

class FrameBuffer;

/** ���� ���ø����̼��Դϴ�. */
class GameApp : public IApp
{
public:
	GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered);
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

	/** ���� ���� ������ ���۸� ����ϴ�. */
	FrameBuffer* GetFrameBuffer() { return frameBuffer_; }

private:
	/** ��ü ���� ���� �������Ǵ� �����ӹ����Դϴ�. */
	FrameBuffer* frameBuffer_ = nullptr;
};