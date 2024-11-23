#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class Texture2D;

/** ���� Ÿ��Ʋ ���� ��� ��ƼƼ�Դϴ�. */
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
	/** ��� �������� ������ �ؽ�ó �Դϴ�. */
	Texture2D* texture_ = nullptr;

	/** ����� ��ġ �� ũ���Դϴ�. */
	Rect2D bound_;
};