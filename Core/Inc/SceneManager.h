#pragma once

#include <array>
#include <memory>
#include <map>

#include "IGameScene.h"

/** �� �Ŵ����� �̱��� Ŭ�����Դϴ�. */
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