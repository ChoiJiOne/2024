#pragma once

#include "Utils/Macro.h"

/** ��ƼƼ �������̽���, ���� ���� ��ƼƼ���� �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�. */
class IEntity
{
public:
	IEntity() = default;
	virtual ~IEntity() {}

	DISALLOW_COPY_AND_ASSIGN(IEntity);

	virtual void Tick(float deltaSeconds) = 0;
	virtual void Release() = 0;

	/** ��ƼƼ�� �ʱ�ȭ �Ǿ����� Ȯ���մϴ�. */
	bool IsInitialized() const { return bIsInitialized_; }

	/** ��ƼƼ�� ������Ʈ ���� ���� �����մϴ�. */
	void SetTickOrder(uint32_t tickOrder) { tickOrder_ = tickOrder; }

	/** ��ƼƼ�� ������Ʈ ���� ���� ����ϴ�. */
	uint32_t GetTickOrder() const { return tickOrder_; }

protected:
	/** ��ƼƼ�� �ʱ�ȭ �Ǿ����� Ȯ���մϴ�. */
	bool bIsInitialized_ = false;

private:
	/** ��ƼƼ�� ������Ʈ ���� ���Դϴ�. �� ���� �������� �켱������ �������ϴ�. */
	uint32_t tickOrder_ = 0;
};