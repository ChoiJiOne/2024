#pragma once

#include "IApp.h"
#include "IEntityUI.h"

class ButtonUI;
class Camera2D;
class TTFont;

/** UI �Ŵ����� �̱����Դϴ�. */
class UIManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(UIManager);

	static UIManager& Get();

	ButtonUI* Create(const std::string& path, const Mouse& mouse, TTFont* font, const std::function<void()>& clickEvent);

private:
	friend class IApp;

	UIManager() = default;
	virtual ~UIManager() {}

	void Startup(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */
	void Shutdown(); /** IApp ���ο����� ȣ���ؾ� �մϴ�. */

private:
	Camera2D* uiCamera_ = nullptr;
};