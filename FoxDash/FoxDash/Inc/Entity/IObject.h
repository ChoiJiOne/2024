#pragma once

#include "Entity/IEntity2D.h"

/** Ŭ���� ���� ����. */
class Player;

/** �÷��̾ ȹ���ϰų� ���ؾ� �� ������Ʈ�� �������̽��Դϴ�. */
class IObject : public IEntity2D
{
public:
	/** �÷��̾ ȹ���ϰų� ���ؾ� �� ������Ʈ�� Ÿ���Դϴ�. */
	enum class EType
	{
		NONE   = 0x00,
		COIN   = 0x01, // �÷��̾ ȹ�� ������ �����Դϴ�.
		FIRE   = 0x02, // �÷��̾ ���ؾ� �� ���Դϴ�.
		POTION = 0x03, // �÷��̾ ȹ�� ������ �����Դϴ�.
	};

	/** ������Ʈ�� ���� �����Դϴ�. */
	enum class EState
	{
		NONE = 0x00, // �ƹ��͵� �ƴ� ����.
		MOVE = 0x01, // Ư�� ��ġ�� �̵� ��.
		WAIT = 0x02, // ��� ��.
		DONE = 0x03, // �� �̻� ������Ʈ�� ������ �� ���� ����.
	};

public:
	IObject(const EType& type);
	virtual ~IObject();

	DISALLOW_COPY_AND_ASSIGN(IObject);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render() = 0;
	virtual void Release() override;

	/** ������Ʈ�� Ÿ���� ����ϴ�. */
	const EType& GetType() const { return type_; }

	/** ������Ʈ�� ���¸� ����ϴ�. */
	const EState& GetState() const { return state_; }

protected:
	/** ������Ʈ�� Ÿ���Դϴ�. */
	EType type_ = EType::NONE;

	/** ������Ʈ�� �����Դϴ�. */
	EState state_ = EState::NONE;

	/** ������Ʈ�� ȹ���ϰų� ���� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;
};