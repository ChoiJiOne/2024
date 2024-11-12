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
	static const uint32_t windowWidth_ = 1000;

	/** ���� �� �������� ���� ũ���Դϴ�. */
	static const uint32_t windowHeight_ = 800;

	/** ���� �� �������� ��ũ������ �߾ӿ� ��ġ�� �� �����Դϴ�. */
	static const bool bIsWindowCentered_ = true;
};