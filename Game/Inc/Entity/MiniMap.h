#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"

/** 클래스 전방 선언입니다. */
class UICamera;
class RandomChest;
class Player;
class TextureAtlas2D;

/** 전체 게임 월드를 축소해서 보여주는 미니맵 엔티티입니다. */
class MiniMap : public IEntity2D
{
public:
	MiniMap();
	virtual ~MiniMap();

	DISALLOW_COPY_AND_ASSIGN(MiniMap);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:

};