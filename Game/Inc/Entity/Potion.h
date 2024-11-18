#pragma once

#include <map>

#include "Entity/IObject.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class TextureAtlas2D;

/** �÷��̾ ȹ���� �����Դϴ�. */
class Potion : public IObject
{
public:
	/** ������ �����Դϴ�. ���� ������ ���� ȿ���� �ٸ��ϴ�. */
	enum class EColor
	{
		NONE = 0x00,
		RED  = 0x01,
		BLUE = 0x02,
	};

public:
	Potion(const glm::vec2& startPos, const glm::vec2& endPos, const EColor& color);
	virtual ~Potion();

	DISALLOW_COPY_AND_ASSIGN(Potion);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ������ �浹 ������ ����ϴ�. */
	const Circle2D* GetCollisionBound() const { return &collisionBound_; }

	/** ������ ���� ������ ����ϴ�. */
	const EColor& GetColor() const { return color_; }

private:
	/** ������ �׸����Դϴ�. */
	struct Shadow
	{
		Rect2D bound; /** �׸��� �����Դϴ�. */
		TextureDrawOption option; /** �׸��� ������ �� ������ �ɼ��Դϴ�. */
		float scale = 0.0f; /** �׸����� ������ ���Դϴ�. */
	};

	/** ������ �����Դϴ�. */
	void Move(float deltaSeconds);

private:
	/** ���� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ������ �̵� ���� ��ġ�Դϴ�. */
	glm::vec2 moveStartPos_ = glm::vec2(0.0f, 0.0f);

	/** ������ �̵� �� ��ġ�Դϴ�. */
	glm::vec2 moveEndPos_ = glm::vec2(0.0f, 0.0f);

	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �浹 �����Դϴ�. */
	Circle2D collisionBound_;

	/** ������ �׸����Դϴ�. */
	Shadow shadow_;

	/** ������ �̵� �ð��Դϴ�. */
	float moveTime_ = 0.0f;

	/** ������ �ִ� �̵� �ð��Դϴ�. */
	float maxMoveTime_ = 0.0f;

	/** ������ �����Դϴ�. */
	EColor color_ = EColor::NONE;

	/** ���� ���� �����ϴ� ��Ʋ�� ���� �̸��Դϴ�. */
	std::map<EColor, std::string> colorNames_;
};