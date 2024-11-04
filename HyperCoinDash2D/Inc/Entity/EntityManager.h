#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "Entity/IEntity.h"
#include "Macro.h"

/**
 * Entity를 생성/질의/삭제를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class EntityManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(EntityManager);

	/** 엔티티 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static EntityManager& GetRef();

	/** 엔티티 매니저의 싱글턴 포인터를 얻습니다. */
	static EntityManager* GetPtr();

private:
	/** GameApp에서 EntityManager의 내부에 접근할 수 있도록 설정 */
	friend class GameApp;

	/**
	 * 엔티티 매니저의 기본 생성자와 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	EntityManager() = default;
	virtual ~EntityManager() {}

	/** 엔티티 매니저의 종료는 GameApp 내부에서만 수행됩니다. */
	void Shutdown();

private:
	/** 엔티티 매니저의 싱글턴 객체입니다. */
	static EntityManager singleton_;
};