#pragma once

#include "Collision2D.h"
#include "IEntityUI.h"

class TTFont;

class TextUI : public IEntityUI
{
public:
	struct Layout
	{
		Vec4f textColor;
		Vec2f textCenterPos; /** �ؽ�Ʈ�� �߽� ��ǥ */
		TTFont* font = nullptr;
		std::wstring text;
	};

public:
	TextUI(const Layout& layout);
	virtual ~TextUI();

	DISALLOW_COPY_AND_ASSIGN(TextUI);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;
	virtual Type GetType() const override { return Type::TEXT; }

private:
	friend class UIManager;

private:
	Layout layout_;
	Vec2f textSize_;
	Vec2f textPos_; /** ������ �� ������ �ؽ�Ʈ�� ��ġ. */
};