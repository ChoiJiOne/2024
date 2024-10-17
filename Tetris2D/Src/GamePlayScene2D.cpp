#include "Assertion.h"
#include "EntityManager.h"
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
#include "GamePlayScene2D.h"
#include "MainCamera2D.h"
#include "Messenger.h"
#include "Next.h"
#include "Particle.h"
#include "ParticleScheduler.h"
#include "Tetromino.h"
#include "TetrominoController.h"

GamePlayScene2D::GamePlayScene2D()
{
	mainCamera_ = entityMgr_->GetByName<MainCamera2D>("MainCamera");

	ParticleScheduler* particleScheduler = entityMgr_->Create<ParticleScheduler>();
	entityMgr_->Register("ParticleScheduler", particleScheduler);

	Next* next = entityMgr_->Create<Next>();
	entityMgr_->Register("Next", next);

	Messenger* messenger = entityMgr_->Create<Messenger>();
	entityMgr_->Register("Messenger", messenger);

	Board* board = entityMgr_->Create<Board>(Vec2f(-50.0f, 0.0f), 30.0f, 10, 20);
	entityMgr_->Register("Board", board);

	TetrominoController* tetrominoController = entityMgr_->Create<TetrominoController>();
	entityMgr_->Register("TetrominoController", tetrominoController);

	TTFont* font32 = resourceMgr_->GetByName<TTFont>("Font32");
	TextUI* nextText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\Next.ui", font32);
	TextUI* scoreText = uiMgr_->CreateTextUI("Tetris2D\\Res\\UI\\ScoreText.ui", font32);
	PanelUI* score = uiMgr_->CreatePanelUI("Tetris2D\\Res\\UI\\ScorePanel.ui", font32);
	entityMgr_->Register("Score", score);

	updateEntities_.push_back(mainCamera_);
	updateEntities_.push_back(tetrominoController);
	updateEntities_.push_back(board);
	updateEntities_.push_back(particleScheduler);
	updateEntities_.push_back(messenger);

	renderEntities_.push_back(board);
	renderEntities_.push_back(next);
	renderEntities_.push_back(tetrominoController);
	renderEntities_.push_back(particleScheduler);
	renderEntities_.push_back(messenger);

	uiEntities_.push_back(nextText);
	uiEntities_.push_back(scoreText);
	uiEntities_.push_back(score);
}

GamePlayScene2D::~GamePlayScene2D()
{
}

void GamePlayScene2D::Tick(float deltaSeconds)
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

void GamePlayScene2D::Render()
{
	renderStateMgr_->BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{// 2D ¿£Æ¼Æ¼ ·»´õ¸µ
		render2dMgr_->Begin(mainCamera_);
		{
			for (auto& entity : renderEntities_)
			{
				entity->Render();
			}
		}
		render2dMgr_->End();
	}
	{// UI ·»´õ¸µ
		IEntityUI** uiEntities = uiEntities_.data();
		uint32_t uiEntityCount = static_cast<uint32_t>(uiEntities_.size());
		uiMgr_->BatchRenderUIEntity(uiEntities, uiEntityCount);
	}
	renderStateMgr_->EndFrame();
}

void GamePlayScene2D::Enter()
{
	bIsEnter_ = true;
}

void GamePlayScene2D::Exit()
{
	bIsEnter_ = false;
}