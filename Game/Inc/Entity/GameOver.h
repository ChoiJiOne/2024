#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TextureAtlas2D;

/** 게임 오버를 표시할 엔티티입니다. */
class GameOver : public IEntity2D
{
public:
	GameOver();
	virtual ~GameOver();

	DISALLOW_COPY_AND_ASSIGN(GameOver);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 게임 오버 렌더링 시 사용할 텍스처 아틀라스 리소스입니다. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** 게임 오버의 위치 및 크기입니다. */
	Rect2D bound_;
};