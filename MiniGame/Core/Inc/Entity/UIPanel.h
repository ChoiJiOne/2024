#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TextureAtlas2D;

/** UI �г��Դϴ�. */
class UIPanel : public IEntity2D
{
public:
	/** UI �г��� ���� �Ӽ��� �����ϱ� ���ؼ��� Json ������ ������ �ʿ��մϴ�. */
	UIPanel(const std::string& panelPath, TextureAtlas2D* textureAtlas);
	virtual ~UIPanel();

	DISALLOW_COPY_AND_ASSIGN(UIPanel);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI �г��� ���� ������Ƽ�� �ʱ�ȭ�մϴ�. */
	void InitProperties(const std::string& panelPath);

private:
	/** UI �г� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** �ؽ�ó ��Ʋ�� ���� UI �г� �ؽ�ó�� �̸��Դϴ�. */
	std::string name_;

	/** UI �г��� ��ġ �� ũ���Դϴ�. */
	Rect2D bound_;
};