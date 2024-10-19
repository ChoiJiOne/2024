#pragma once

#include <array>

#include "InputManager.h"

#include "IGameScene2D.h"

class GamePlayScene2D : public IGameScene2D
{
public:
	GamePlayScene2D();
	virtual ~GamePlayScene2D();

	DISALLOW_COPY_AND_ASSIGN(GamePlayScene2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Enter() override;
	virtual void Exit() override;

	void Reset();

private:
	bool IsPauseGame();

	template <typename TGameScene2D>
	void SwitchGameScene(const std::string& sceneName)
	{
		bIsSwitched_ = true;

		TGameScene2D* scene = IApp::Get()->GetSceneByName<TGameScene2D>(sceneName);
		switchScene_ = scene;
	}

private:
	std::array<WindowEventID, 3> windowEventIDs_;

	class TetrominoController* tetrominoController_ = nullptr;
};