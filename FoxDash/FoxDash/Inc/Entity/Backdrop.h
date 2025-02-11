#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class Texture2D;

/** 게임 타이틀 씬의 배경 엔티티입니다. */
class Backdrop : public IEntity2D
{
public:
	Backdrop();
	virtual ~Backdrop();

	DISALLOW_COPY_AND_ASSIGN(Backdrop);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 배경 렌더링에 참조할 텍스처 입니다. */
	Texture2D* texture_ = nullptr;

	/** 배경의 위치 및 크기입니다. */
	Rect2D bound_;
};