#pragma once

#include <map>

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"

/** �÷��̾��� �÷��� ������ ��Ÿ���� ��ƼƼ�Դϴ�. */
class Playground : public IEntity2D
{
public:
	/** �÷��̾��� ���� ��ġ ���¸� ����ϴ�. */
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

	/** ������ ������ ����ϴ�. */
	Circle2D* GetSafeBound() { return &safeBound_; }

	/** ������ ������ ����ϴ�. */
	Circle2D* GetWarnBound() { return &warnBound_; }

	/** �÷��̾� ���� ��ġ�� ���� ���¸� ����ϴ�. */
	const EPlayerState& GetPlayerState() const { return playerState_; }
	
private:
	/** ���� �����Դϴ�. */
	Circle2D safeBound_;

	/** ������ �����Դϴ�. */
	Circle2D warnBound_;

	/** �÷��̾� ���� ��ġ�� ���� �����Դϴ�. */
	EPlayerState playerState_ = EPlayerState::SAFE;

	/** ���� �� �����Դϴ�. */
	std::map<EPlayerState, glm::vec4> playerStateColors_;
};