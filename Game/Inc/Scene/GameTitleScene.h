#pragma once

#include "Scene/IGameScene.h"

/** ���� Ÿ��Ʋ ���Դϴ�. */
class GameTitleScene : public IGameScene
{
public:
	GameTitleScene();
	virtual ~GameTitleScene();

	DISALLOW_COPY_AND_ASSIGN(GameTitleScene);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;

private:
	/** ���� Ÿ��Ʋ ���� ��ũ�� ī�޶��Դϴ�. */
	class UICamera* uiCamera_ = nullptr;

	/** ������Ʈ�� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity*> updateUiEntities_;

	/** �������� UI ��ƼƼ�Դϴ�. */
	std::list<IEntity2D*> renderUiEntities_;
};