#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TextureAtlas2D;

/** ���� ������ ǥ���� ��ƼƼ�Դϴ�. */
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
	/** ���� ���� ������ �� ����� �ؽ�ó ��Ʋ�� ���ҽ��Դϴ�. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** ���� ������ ��ġ �� ũ���Դϴ�. */
	Rect2D bound_;
};