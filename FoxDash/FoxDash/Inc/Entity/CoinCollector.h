#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class Player;
class PlayerFollowCamera;
class TextureAtlas2D;
class TTFont;

/** 코인을 수집하고, 플레이어가 획득한 코인의 상태를 표시하는 엔티티입니다. */
class CoinCollector : public IEntity2D
{
public:
	CoinCollector(TTFont* font);
	virtual ~CoinCollector();

	DISALLOW_COPY_AND_ASSIGN(CoinCollector);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 코인 콜렉터의 충돌 영역을 얻습니다. */
	const Rect2D* GetCollider() const { return &background_; }

private:
	/** 코인을 획득하는 플레이어입니다. */
	Player* player_ = nullptr;

	/** 코인 콜렉터를 렌더링할 때 참조할 카메라입니다. */
	PlayerFollowCamera* playerFollowCamera_ = nullptr;

	/** 코인 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 텍스트 렌더링 시 참조할 폰트 리소스입니다. */
	TTFont* font_ = nullptr;

	/** 카메라 끝에서 떨어진 위치 값입니다. */
	glm::vec2 offset_ = glm::vec2(0.0f, 0.0f);

	/** 백그라운드 영역입니다. */
	Rect2D background_;

	/** 코인의 위치입니다. */
	Rect2D coin_;

	/** 코인 콜렉터가 추적하는 코인 수입니다. */
	int32_t countCoin_ = 0;

	/** 획득한 코인을 표시할 텍스트의 위치입니다. */
	glm::vec2 textBasePos_ = glm::vec2(0.0f, 0.0f);

	/** 획득한 코인의 텍스트입니다. */
	std::wstring coinText_;

	/** 획득한 코인의 텍스트 색상입니다. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** 백그라운드의 색상입니다. */
	glm::vec4 backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};