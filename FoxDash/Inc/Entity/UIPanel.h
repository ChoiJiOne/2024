#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TextureAtlas2D;

/** UI 패널입니다. */
class UIPanel : public IEntity2D
{
public:
	/** UI 패널의 내부 속성을 설정하기 위해서는 Json 포멧의 파일이 필요합니다. */
	UIPanel(const std::string& panelPath, TextureAtlas2D* textureAtlas);
	virtual ~UIPanel();

	DISALLOW_COPY_AND_ASSIGN(UIPanel);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI 패널의 내부 프로퍼티를 초기화합니다. */
	void InitProperties(const std::string& panelPath);

private:
	/** UI 패널 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 텍스처 아틀라스 내에 UI 패널 텍스처의 이름입니다. */
	std::string name_;

	/** UI 패널의 위치 및 크기입니다. */
	Rect2D bound_;
};