#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "GLFW/GLFWManager.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class Player;
class TextureAtlas2D;

/** 플레이어 방향 키 입력 상태를 보여주는 엔티티입니다. */
class KeyArrowPressViewer : public IEntity2D
{
public:
	KeyArrowPressViewer();
	virtual ~KeyArrowPressViewer();

	DISALLOW_COPY_AND_ASSIGN(KeyArrowPressViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 방향 키 입력 상태입니다. */
	struct KeyArrowState
	{
		EKey key;
		EPress press;
		Rect2D renderBound;
		std::map<EPress, std::string> names;
	};

private:
	/** 키 입력 상태 렌더링에 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 키 입력 상태 렌더링에 참조할 플레이어입니다. */
	Player* player_ = nullptr;

	/** 방향 키 입력 상태의 목록입니다. */
	std::list<KeyArrowState> keyArrowStates_;
};