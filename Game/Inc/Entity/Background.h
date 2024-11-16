#pragma once

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 백그라운드 엔티티입니다. */
class Background : public IEntity2D
{
public:
	Background();
	virtual ~Background();

	DISALLOW_COPY_AND_ASSIGN(Background);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이 영역을 얻습니다. */
	Circle2D* GetPlayground() { return &playground_; }

private:
	/** 벡그라운드 렌더링 시 사용할 텍스처 아틀라스 리소스입니다. */
	class TextureAtlas2D* textureAtlas_ = nullptr;

	/** 백그라운드의 위치를 조정할 때 참조할 플레이어입니다. */
	class Player* player_ = nullptr;
	
	/** 화면 크기에 대응하는 백그라운드 영역입니다. */
	Rect2D screenBound_;

	/** 게임 플레이 가능한 영역입니다. */
	Circle2D playground_;

	/** 게임 플레이 가능한 영역의 색상입니다. */
	glm::vec4 playgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};