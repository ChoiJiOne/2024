#pragma once

#include <map>

#include "Entity/IObject.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class TextureAtlas2D;

/** 플레이어가 획득할 포션입니다. */
class Potion : public IObject
{
public:
	/** 포션의 색상입니다. 색상 종류에 따라 효과가 다릅니다. */
	enum class EColor
	{
		NONE       = 0x00,
		RED        = 0x01,
		BLUE       = 0x02,
		RED_POWER  = 0x03,
		BLUE_POWER = 0x04,
	};

public:
	Potion(const glm::vec2& startPos, const glm::vec2& endPos, const EColor& color);
	virtual ~Potion();

	DISALLOW_COPY_AND_ASSIGN(Potion);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 포션의 충돌 영역을 얻습니다. */
	const Circle2D* GetCollisionBound() const { return &collisionBound_; }

	/** 포션의 색상 종류를 얻습니다. */
	const EColor& GetColor() const { return color_; }

private:
	/** 포션의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 포션을 움직입니다. */
	void Move(float deltaSeconds);

private:
	/** 포션 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 포션의 이동 시작 위치입니다. */
	glm::vec2 moveStartPos_ = glm::vec2(0.0f, 0.0f);

	/** 포션의 이동 끝 위치입니다. */
	glm::vec2 moveEndPos_ = glm::vec2(0.0f, 0.0f);

	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 포션의 그림자입니다. */
	Shadow shadow_;

	/** 포션의 이동 시간입니다. */
	float moveTime_ = 0.0f;

	/** 포션의 최대 이동 시간입니다. */
	float maxMoveTime_ = 0.0f;

	/** 포션의 회복량입니다. */
	float heal_ = 0.0f;

	/** 포션의 색상입니다. */
	EColor color_ = EColor::NONE;

	/** 포션 색상에 대응하는 아틀라스 내의 이름입니다. */
	static std::map<EColor, std::string> colorNames_;
};