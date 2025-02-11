#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 백그라운드 엔티티입니다. */
class Background : public IEntity2D
{
public:
	Background();
	virtual ~Background();

	DISALLOW_COPY_AND_ASSIGN(Background);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 벡그라운드 렌더링 시 사용할 텍스처 아틀라스 리소스입니다. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** 백그라운드의 위치를 조정할 때 참조할 카메라입니다. */
	class PlayerFollowCamera* camera_ = nullptr;
	
	/** 화면 크기에 대응하는 백그라운드 영역입니다. */
	Rect2D screenBound_;
};