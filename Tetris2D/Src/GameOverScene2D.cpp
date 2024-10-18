#include "Assertion.h"
#include "EntityManager.h"
#include "IApp.h"
#include "IEntity.h"
#include "IEntity2D.h"
#include "IEntityUI.h"
#include "PanelUI.h"
#include "ResourceManager.h"
#include "RenderManager2D.h"
#include "TextUI.h"
#include "TTFont.h"
#include "UIManager.h"

#include "Block.h"
#include "Board.h"
#include "GameOverScene2D.h"
#include "GamePlayScene2D.h"
#include "GameTitleScene2D.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "Particle.h"
#include "ParticleScheduler.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GameOverScene2D::GameOverScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	ParticleScheduler* particleScheduler = entityMgr_->GetByName<ParticleScheduler>("ParticleScheduler");
	Next* next = entityMgr_->GetByName<Next>("Next");
	Board* board = entityMgr_->GetByName<Board>("Board");
	TetrominoController* tetrominoController = entityMgr_->GetByName<TetrominoController>("TetrominoController");

	renderEntities_.push_back(board);
	renderEntities_.push_back(next);
	renderEntities_.push_back(tetrominoController);
	renderEntities_.push_back(particleScheduler);
}

GameOverScene2D::~GameOverScene2D()
{
}

void GameOverScene2D::Tick(float deltaSeconds)
{
	for (auto& entity : updateEntities_)
	{
		entity->Tick(deltaSeconds);
	}

	for (auto& uiEntity : uiEntities_)
	{
		uiEntity->Tick(deltaSeconds);
	}
}

void GameOverScene2D::Render()
{
	renderStateMgr_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{// 2D ��ƼƼ ������
		render2dMgr_->Begin(mainCamera_);
		{
			for (auto& entity : renderEntities_)
			{
				entity->Render();
			}
		}
		render2dMgr_->End();
	}
	{// UI ������
		IEntityUI** uiEntities = uiEntities_.data();
		uint32_t uiEntityCount = static_cast<uint32_t>(uiEntities_.size());
		uiMgr_->BatchRenderUIEntity(uiEntities, uiEntityCount);
	}
	renderStateMgr_->EndFrame();
}

void GameOverScene2D::Enter()
{
	bIsEnter_ = true;
}

void GameOverScene2D::Exit()
{
	bIsSwitched_ = false;
	bIsEnter_ = false;
}