#pragma once

#include <array>
#include <memory>
#include <map>

#include "IGameScene.h"

/** 씬 매니저는 싱글턴 클래스입니다. */
class SceneManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(SceneManager);

	static SceneManager& GetRef();
	static SceneManager* GetPtr();

private:
	friend class IApp;

	SceneManager() = default;
	virtual ~SceneManager() {}

private:
	static SceneManager instance_;
};