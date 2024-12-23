#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
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
	/** ���׶��� ������ �� ����� �ؽ�ó ��Ʋ�� ���ҽ��Դϴ�. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** ��׶����� ��ġ�� ������ �� ������ ī�޶��Դϴ�. */
	class PlayerFollowCamera* camera_ = nullptr;
	
	/** ȭ�� ũ�⿡ �����ϴ� ��׶��� �����Դϴ�. */
	Rect2D screenBound_;
};