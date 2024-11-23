#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TextureAtlas2D;

/** ������ Ÿ��Ʋ�� ǥ���� ��ƼƼ�Դϴ�. */
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
	/** Ÿ��Ʋ ������ �� ����� �ؽ�ó ��Ʋ�� ���ҽ��Դϴ�. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** Ÿ��Ʋ�� ��ġ �� ũ���Դϴ�. */
	Rect2D bound_;
};