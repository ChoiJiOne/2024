#pragma once

#include "Entity/IEntity.h"

/** 2D 엔티티의 인터페이스입니다. */
class IEntity2D : public IEntity
{
public:
	IEntity2D();
	virtual ~IEntity2D();

	DISALLOW_COPY_AND_ASSIGN(IEntity2D);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	/** 2D 엔티티의 렌더링 순서 값을 설정합니다. */
	void SetRenderOrder(uint32_t renderOrder) { renderOrder_ = renderOrder; }

	/** 2D 엔티티의 렌더링 순서 값을 얻습니다. */
	uint32_t GetRenderOrder() const { return renderOrder_; }

protected:
	/** 2D 엔티티의 렌더링 순위 값입니다. 이 값은 낮을수록 우선순위가 높아집니다. */
	uint32_t renderOrder_ = 0;

	/** 렌더링할 때 사용할 2D 렌더러입니다. */
	class RenderManager2D* renderManager_ = nullptr;;
};