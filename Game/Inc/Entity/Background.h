#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** ��׶��� ��ƼƼ�Դϴ�. */
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
	/** ���׶��� ������ �� ����� �ؽ�ó ���ҽ��Դϴ�. */
	class Texture2D* texture_ = nullptr;
	
	/** ��׶��� �����Դϴ�. */
	Rect2D bound_;
};