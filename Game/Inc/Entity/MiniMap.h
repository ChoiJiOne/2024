#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class UICamera;
class RandomChest;
class Player;
class Playground;
class TextureAtlas2D;

/** 전체 게임 월드를 축소해서 보여주는 미니맵 엔티티입니다. */
class MiniMap : public IEntity2D
{
public:
	MiniMap(UICamera* uiCamera);
	virtual ~MiniMap();

	DISALLOW_COPY_AND_ASSIGN(MiniMap);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 미니멥 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 미니맵 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 렌더링 영역입니다. */
	Rect2D renderBound_;
};