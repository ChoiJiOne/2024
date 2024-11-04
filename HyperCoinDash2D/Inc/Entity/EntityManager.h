#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "Entity/IEntity.h"
#include "Macro.h"

/**
 * Entity�� ����/����/������ �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class EntityManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(EntityManager);

	/** ��ƼƼ �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static EntityManager& GetRef();

	/** ��ƼƼ �Ŵ����� �̱��� �����͸� ����ϴ�. */
	static EntityManager* GetPtr();

private:
	/** GameApp���� EntityManager�� ���ο� ������ �� �ֵ��� ���� */
	friend class GameApp;

	/**
	 * ��ƼƼ �Ŵ����� �⺻ �����ڿ� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	EntityManager() = default;
	virtual ~EntityManager() {}

	/** ��ƼƼ �Ŵ����� ����� GameApp ���ο����� ����˴ϴ�. */
	void Shutdown();

private:
	/** ��ƼƼ �Ŵ����� �̱��� ��ü�Դϴ�. */
	static EntityManager singleton_;
};