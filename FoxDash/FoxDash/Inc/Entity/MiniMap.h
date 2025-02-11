#pragma once

#include <queue>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class UICamera;
class IObject;
class RandomChest;
class Player;
class Playground;
class TextureAtlas2D;

/** 전체 게임 월드를 축소해서 보여주는 미니맵 엔티티입니다. */
class MiniMap : public IEntity2D
{
public:
	MiniMap(UICamera* uiCamera, RandomChest** randomChests, uint32_t countRandomChest);
	virtual ~MiniMap();

	DISALLOW_COPY_AND_ASSIGN(MiniMap);
	
	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** 미니맵 상의 오브젝트입니다. */
	struct MinimapObject
	{
		glm::vec2 position; // 미니맵 상의 위치입니다.
		glm::vec4 color; // 미니맵 상의 색상입니다.
	};

	/** 오브젝트를 미니맵 오브젝트로 변환합니다. */
	void ConvertMinimapObject(const IObject* object, MinimapObject& outMinimapObjec);

private:
	/** 미니멥 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 미니맵 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 렌더링 영역입니다. */
	Rect2D renderBound_;

	/** 플레이어입니다. */
	Player* player_ = nullptr;

	/** 전체 월드의 스케일 값입니다. */
	float worldScale_ = 0.0f;

	/** 플레이 영역의 반지름 길이입니다. */
	float playgroundRadius_ = 0.0f;

	/** 미니맵 반지름 길이입니다. */
	float minimapRadius_ = 0.0f;

	/** 미니맵에 표시할 점의 크기입니다. */
	float pointSize_ = 0.0f;
	
	/** 미니맵 상의 플레이어 색상입니다. */
	glm::vec4 playerColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** 미니맵 상의 코인 색상입니다. */
	glm::vec4 coinColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** 미니맵 상의 불 색상입니다. */
	glm::vec4 fireColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** 미니맵 상의 빨간색 포션 색상입니다. */
	glm::vec4 redPotionColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** 미니맵 상의 파란색 포션 색상입니다. */
	glm::vec4 bluePotionColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** 오브젝트들을 관리하는 렌덤 상자 엔티티 목록입니다. */
	std::vector<RandomChest*> randomChests_;

	/** 미니맵 상의 오브젝트 큐입니다. */
	std::queue<MinimapObject> minimapObjects_;
};