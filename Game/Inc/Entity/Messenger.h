#pragma once

#include <functional>
#include <list>
#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;
class UICamera;

/** 게임 내에 텍스트 기반의 메시지를 표시하는 엔티티입니다. */
class Messenger : public IEntity2D
{
public:
	Messenger(UICamera* uiCamera, TTFont* font);
	virtual ~Messenger();

	DISALLOW_COPY_AND_ASSIGN(Messenger);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 메신저를 이용해서 메시지를 전송합니다. */
	void Send(const std::wstring& text, const glm::vec2& centerPos, const glm::vec4& color, float time);

private:
	/** 화면에 표시할 메시지입니다. */
	struct Message
	{
		std::wstring text;
		glm::vec2 textBasePos;
		glm::vec4 textColor;
		float time = 0.0f;
		float remainTime = 0.0f;
	};

private:
	/** 메시지 렌더링에 기준이 될 UI 카메라입니다. */
	UICamera* uiCamera_ = nullptr;

	/** 텍스트 렌더링 시 참조할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** 화면에 표시할 메시지들입니다. */
	std::list<Message> messages_;

	/** 메시지 삭제 이벤트입니다. */
	std::function<bool(const Message&)> messageRemoveEvent_ = nullptr;
};