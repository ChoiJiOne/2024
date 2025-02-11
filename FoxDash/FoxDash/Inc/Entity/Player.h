#pragma once

#include <map>
#include <list>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class GamePlayScene;
class GamePlayRecorder;
class SpriteAnimator2D;
class TextureAtlas2D;
class Sound;
class Playground;
class UIBar;
class UISkill;

/** 플레이어가 조종할 엔티티입니다. */
class Player : public IEntity2D
{
public:
	/** 플레이어의 상태입니다. */
	enum class EState
	{
		IDLE = 0x00,
		RUN  = 0x01,
		HURT = 0x02,
	};

public:
	Player();
	virtual ~Player();

	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이어의 중심 위치를 얻습니다. */
	const glm::vec2 GetPosition() const;

	/** 플레이어의 경계 충돌 영역을 얻습니다. */
	const Circle2D* GetCollider() const { return &collisionBound_; }

	/** 플레이어의 HP를 얻습니다. */
	float GetHP() const;

	/** 플레이어의 HP를 설정합니다. */
	void SetHP(float hp);

	/** 플레이어의 최대 HP를 얻습니다. */
	float GetMaxHP() const;

	/** 플레이어의 최대 HP를 설정합니다. */
	void SetMaxHP(float maxHp);

	/** 플레이어의 MP를 얻습니다. */
	float GetMP() const;

	/** 플레이어의 MP를 설정합니다. */
	void SetMP(float mp);

	/** 플레이어의 최대 MP를 얻습니다. */
	float GetMaxMP() const;

	/** 플레이어의 최대 MP를 설정합니다. */
	void SetMaxMP(float maxMP);

	/** 플레이어의 코인 수를 얻습니다. */
	int32_t GetCoin() const { return coin_; }

	/** 플레이어의 코인 수를 하나 증가시킵니다. */
	void AddCoin();

	/** 플레이어의 상태를 얻습니다. */
	const EState& GetState() const { return state_; }

private:
	/** 플레이어의 스킬 종류입니다. */
	enum class ESkill
	{
		NONE          = 0x00, // 스킬을 사용하지 않는 상태입니다. 
		DASH          = 0x01, // 플레이어의 데쉬 스킬입니다.
		INVINCIBILITY = 0x02, // 플레이어의 무적(invincibility) 스킬입니다.
	};

	/** 플레이어의 그림자입니다. */
	struct Shadow
	{
		Rect2D bound; /** 그림자 영역입니다. */
		TextureDrawOption option; /** 그림자 렌더링 시 설정할 옵션입니다. */
		float scale = 0.0f; /** 그림자의 스케일 값입니다. */
	};

	/** 플레이어의 애니메이션 상태를 초기화합니다. */
	void LoadAnimations();

	/** 플레이어의 애니메이션 상태 초기화를 해제합니다. */
	void UnloadAnimations();

	/** 플레이어의 UI 요소를 초기화합니다. */
	void LoadUIs();

	/** 플레이어의 UI 요소를 초기화 해제합니다. */
	void UnloadUIs();

	/** 플레이어의 사운드 요소를 초기화합니다. */
	void LoadSounds();

	/** 플레이어의 사운드 요소를 초기화 해제합니다. */
	void UnloadSounds();

	/** 플레이어의 대쉬 스킬을 수행합니다. */
	void UseDashSkill(float deltaSeconds);

	/** 플레이어의 체력 감소 이펙트를 수행합니다. */
	void LostHpEffect(float deltaSeconds);

	/** 플레이어를 움직입니다 */
	void Move(float deltaSeconds, float speed);
	
	/** 플레이어의 렌더링/충돌/그림자 위치를 조정합니다. */
	void AdjustPosition(const glm::vec2& position);

	/** 플레이어의 잔상을 렌더링합니다. */
	void RenderPlayerAfterImage(TextureAtlas2D* animationTexture, const std::string& animationClipName);

	/** 플레이어를 렌더링합니다. */
	void RenderPlayer(TextureAtlas2D* animationTexture, const std::string& animationClipName);

private:
	/** 플레이어 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 게임 플레이 기록을 수행하는 엔티티입니다. */
	GamePlayRecorder* gamePlayRecorder_ = nullptr;

	/** 플레이 그라운드입니다. */
	Playground* playground_ = nullptr;

	/** 게임 플레이 씬입니다. */
	GamePlayScene* gamePlayScene_ = nullptr;

	/** 렌더링 영역입니다 */
	Rect2D renderBound_;

	/** 플레이어의 렌더링 옵션입니다. */
	TextureDrawOption renderOption_;

	/** 충돌 영역입니다. */
	Circle2D collisionBound_;

	/** 플레이어의 그림자입니다. */
	Shadow shadow_;

	/** 플레이어의 이동 방향입니다. */
	glm::vec2 direction_;
	
	/** 플레이어의 속도입니다. */
	float speed_ = 0.0f;
		
	/** 현재 플레이어의 상태입니다. */
	EState state_ = EState::IDLE;

	/** 플레이어의 상태 별 애니메이션 리소스입니다. */
	std::map<EState, SpriteAnimator2D*> animations_;

	/** 플레이어의 코인 수입니다. */
	int32_t coin_ = 0;

	/** 플레이어의 체력을 나타내는 HP입니다. */
	UIBar* hpBar_ = nullptr;

	/** 플레이어의 마나를 나타내는 MP입니다. */
	UIBar* mpBar_ = nullptr;

	/** 플레이어의 스킬입니다. */
	std::map<ESkill, UISkill*> skills_;

	/** 플레이어의 스킬을 사용할 때 소모되는 마나 값입니다. */
	std::map<ESkill, float> skillMpCosts_;

	/** 플레이어가 무적일 때 표시할 색상입니다. */
	glm::vec4 invincibilityColor_;

	/** 플레이어의 대쉬 속도입니다. */
	float dashSpeed_ = 0.0f;
	
	/** 최대 대쉬 속도입니다. */
	float maxDashSpeed_ = 0.0f;

	/** 플레이어의 대쉬 거리입니다. */
	float dashLength_ = 0.0f;

	/** 플레이어의 이전 프레임 상의 위치입니다. */
	glm::vec2 prevPosition_ = glm::vec2(0.0f, 0.0f);

	/** 플레이어의 현재 프레임 상의 위치입니다. */
	glm::vec2 currPosition_ = glm::vec2(0.0f, 0.0f);

	/** 플레이어 대쉬의 잔상 표현을 위한 렌더링 카운트 수입니다. */
	static const uint32_t DASH_AFTER_IMAGE_COUNT = 10;

	/** 플레이어가 대쉬 중인지 확인합니다. */
	bool bIsDashing_ = false;

	/** 플레이어 체력이 감소했을 때 표시할 색상입니다. */
	glm::vec4 lostHpColor_;

	/** 플레이어가 체력이 감소했는지 확인합니다. */
	bool bIsLostHp_ = false;

	/** 플레이어의 체력이 감소했을 때 깜빡거리는 효과의 최대 횟수입니다. */
	int32_t maxLostHpEffectCount_ = 0;

	/** 플레이어의 체력 감소 효과 시간의 최대값입니다. */
	float maxLostHpEffectTime_ = 0.0f;

	/** 플레이어의 체력이 감소했을 때 깜빡거리는 효과의 횟수입니다. */
	int32_t lostHpEffectCount_ = 0;

	/** 현재 체력 감소 효과 시간 값입니다. */
	float lostHpEffectTime_ = 0.0f;

	/** HP/MP가 회복되었을 때 출력할 사운드입니다. */
	Sound* chargeSound_ = nullptr;

	/** 플레이어가 대쉬 스킬을 사용했을 때 출력할 사운드입니다. */
	Sound* dashSound_ = nullptr;

	/** 플레이어가 hurt 상태가 되었을 때 출력할 사운드입니다. */
	Sound* hurtSound_ = nullptr;
};
