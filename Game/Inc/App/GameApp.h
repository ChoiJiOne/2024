#pragma once

#include <array>

#include "IApp.h"

class FrameBuffer;
class TextureAtlas2D;

/** ���� ���ø����̼��Դϴ�. */
class GameApp : public IApp
{
public:
	GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, bool bIsWindowCentered);
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	/** ���� �� ������ ����� ���ҽ��� �ε��մϴ�. */
	void LoadResource();

	/** ���� �� ������ ����� ���ҽ��� �ε� �����մϴ�. */
	void UnloadResource();

private:
	/** ��ü ���� ���� �������Ǵ� �����ӹ����Դϴ�. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** ���� �� ���ο��� ����ϴ� �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ���� �� ������ ����ϴ� ��Ʈ ũ���Դϴ�. */
	std::array<int32_t, 3> fontSizes_;
};