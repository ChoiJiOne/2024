#pragma once

#include <array>
#include <map>

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

class TextureAtlas2D;

/** 플레이어의 플레이 영역을 나타내는 엔티티입니다. */
class Playground : public IEntity2D
{
public:
	Playground();
	virtual ~Playground();

	DISALLOW_COPY_AND_ASSIGN(Playground);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 안전한 영역을 얻습니다. */
	Circle2D* GetSafeBound() { return &safeBound_; }

	/** 위험한 영역을 얻습니다. */
	Circle2D* GetWarnBound() { return &warnBound_; }

private:
	/** 플레이 영역 내의 장식물입니다. */
	struct Ornament
	{
		std::string name;
		Rect2D rect;
	};

private:
	/** 플레이그라운드 내의 장식물 렌더링에 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 안전 영역입니다. */
	Circle2D safeBound_;

	/** 위험한 영역입니다. */
	Circle2D warnBound_;

	/** 플레이 영역을 명확하게 표시하기 위한 색상입니다. */
	glm::vec4 outlineColor_;

	/** 플레이 영역 내의 최대 장식물 개수입니다. */
	static const uint32_t MAX_COUNT_ORNAMENT = 100;

	/** 플레이 영역 내의 장식물들입니다. */
	std::array<Ornament, MAX_COUNT_ORNAMENT> ornaments_;
};