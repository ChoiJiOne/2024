#pragma once

#include "IApp.h"

/** ���� ���ø����̼��Դϴ�. */
class GameApp : public IApp
{
public:
	GameApp();
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	/** ���� �� �������� ���� ũ���Դϴ�. */
	const uint32_t windowWidth_ = 1000;

	/** ���� �� �������� ���� ũ���Դϴ�. */
	const uint32_t windowHeight_ = 800;

	/** ���� �� �������� Ÿ��Ʋ�Դϴ�. */
	const char* windowTitle_ = "HyperCoinDash2D";

	/** ���� �� �������� ��ũ������ �߾ӿ� ��ġ�� �� �����Դϴ�. */
	const bool bIsWindowCentered_ = true;
};