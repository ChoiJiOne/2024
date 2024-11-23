#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TextureAtlas2D;

/** 게임의 타이틀을 표시할 엔티티입니다. */
class Title : public IEntity2D
{
public:
	Title();
	virtual ~Title();

	DISALLOW_COPY_AND_ASSIGN(Title);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 타이틀 렌더링 시 사용할 텍스처 아틀라스 리소스입니다. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** 타이틀의 위치 및 크기입니다. */
	Rect2D bound_;
};