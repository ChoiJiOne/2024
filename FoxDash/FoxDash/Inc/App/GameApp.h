#pragma once

#include <array>
#include <string>

#include "App/IApp.h"

class FrameBuffer;
class TextureAtlas2D;

/** 게임 애플리케이션입니다. */
class GameApp : public IApp
{
public:
	GameApp(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle, const char* windowIcon, bool bIsWindowCentered);
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	/** 게임 앱 내에서 사용할 리소스를 로딩합니다. */
	void LoadResource();

	/** 게임 앱 내에서 사용한 리소스를 로딩 해제합니다. */
	void UnloadResource();

private:
	/** 전체 게임 씬에 렌더링되는 프레임버퍼입니다. */
	FrameBuffer* frameBuffer_ = nullptr;

	/** 게임 앱 내부에서 사용하는 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 게임 앱 내에서 사용하는 폰트 크기입니다. */
	std::array<int32_t, 3> fontSizes_;

	/** 게임 앱 내에서 사용하는 사운드 리소스 이름입니다. */
	std::array<std::string, 7> soundNames_;

	/** 게임 매니저 포인터입니다. */
	class GameManager* gameManager_ = nullptr;
};