#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"

/** 플레이어의 플레이 영역을 나타내는 엔티티입니다. */
class Playground : public IEntity2D
{
public:
	/** 플레이어의 현재 위치 상태를 얻습니다. */
	enum class EPlayerState
	{
		SAFE = 0x00,
		WARN = 0x01,
		DEAD = 0x02,
	};

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

	/** 플레이어 현재 위치에 대한 상태를 얻습니다. */
	const EPlayerState& GetPlayerState() const { return playerState_; }
	
private:
	/** 안전 영역입니다. */
	Circle2D safeBound_;

	/** 위험한 영역입니다. */
	Circle2D warnBound_;

	/** 플레이어 현재 위치에 대한 상태입니다. */
	EPlayerState playerState_ = EPlayerState::SAFE;

	/** 상태 별 색상입니다. */
	std::map<EPlayerState, glm::vec4> playerStateColors_;
};