#pragma once

#include <functional>
#include <list>
#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TTFont;
class UICamera;

/** ���� ���� �ؽ�Ʈ ����� �޽����� ǥ���ϴ� ��ƼƼ�Դϴ�. */
class Messenger : public IEntity2D
{
public:
	Messenger(UICamera* uiCamera, TTFont* font);
	virtual ~Messenger();

	DISALLOW_COPY_AND_ASSIGN(Messenger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** �޽����� �̿��ؼ� �޽����� �����մϴ�. */
	void Send(const std::wstring& text, const glm::vec2& centerPos, const glm::vec4& color, float time);

private:
	/** ȭ�鿡 ǥ���� �޽����Դϴ�. */
	struct Message
	{
		std::wstring text;
		glm::vec2 textBasePos;
		glm::vec4 textColor;
		float time = 0.0f;
		float remainTime = 0.0f;
	};

private:
	/** �޽��� �������� ������ �� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** �ؽ�Ʈ ������ �� ������ ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;

	/** ȭ�鿡 ǥ���� �޽������Դϴ�. */
	std::list<Message> messages_;

	/** �޽��� ���� �̺�Ʈ�Դϴ�. */
	std::function<bool(const Message&)> messageRemoveEvent_ = nullptr;
};