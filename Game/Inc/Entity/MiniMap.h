#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class UICamera;
class RandomChest;
class Player;
class TextureAtlas2D;

/** ��ü ���� ���带 ����ؼ� �����ִ� �̴ϸ� ��ƼƼ�Դϴ�. */
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