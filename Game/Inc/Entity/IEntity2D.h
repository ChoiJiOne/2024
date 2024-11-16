#pragma once

#include "Entity/IEntity.h"

/** 2D ��ƼƼ�� �������̽��Դϴ�. */
class IEntity2D : public IEntity
{
public:
	IEntity2D();
	virtual ~IEntity2D();

	DISALLOW_COPY_AND_ASSIGN(IEntity2D);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	/** 2D ��ƼƼ�� ������ ���� ���� �����մϴ�. */
	void SetRenderOrder(uint32_t renderOrder) { renderOrder_ = renderOrder; }

	/** 2D ��ƼƼ�� ������ ���� ���� ����ϴ�. */
	uint32_t GetRenderOrder() const { return renderOrder_; }

protected:
	/** 2D ��ƼƼ�� ������ ���� ���Դϴ�. �� ���� �������� �켱������ �������ϴ�. */
	uint32_t renderOrder_ = 0;

	/** �������� �� ����� 2D �������Դϴ�. */
	class RenderManager2D* renderManager_ = nullptr;;
};