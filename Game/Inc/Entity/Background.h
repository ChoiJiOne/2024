#pragma once

#include "Entity/IEntity2D.h"
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
	/** 벡그라운드 렌더링 시 사용할 텍스처 리소스입니다. */
	class Texture2D* texture_ = nullptr;
	
	/** 백그라운드 영역입니다. */
	Rect2D bound_;
};