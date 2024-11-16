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

	/** �÷��� ������ ����ϴ�. */
	Circle2D* GetPlayground() { return &playground_; }

private:
	/** ���׶��� ������ �� ����� �ؽ�ó ��Ʋ�� ���ҽ��Դϴ�. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** ��׶����� ��ġ�� ������ �� ������ �÷��̾��Դϴ�. */
	class Player* player_ = nullptr;
	
	/** ȭ�� ũ�⿡ �����ϴ� ��׶��� �����Դϴ�. */
	Rect2D screenBound_;

	/** ���� �÷��� ������ �����Դϴ�. */
	Circle2D playground_;

	/** ���� �÷��� ������ ������ �����Դϴ�. */
	glm::vec4 playgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};