#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;

/** UI 텍스트 엔티티입니다. */
class UIText : public IEntity2D
{
public:
	/** UI 텍스트의 내부 속성을 설정하기 위해서는 Json 포멧의 파일이 필요합니다. */
	UIText(const std::string& textPath, TTFont* font);
	virtual ~UIText();

	DISALLOW_COPY_AND_ASSIGN(UIText);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI 텍스트 내의 속성들을 초기화합니다. */
	void InitProperties(const std::string& textPath);

private:
	/** UI 텍스트 렌더링 시 참조할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** UI 텍스트입니다. */
	std::wstring text_;

	/** UI 텍스트 렌더링 시 기준이 되는 위치입니다. */
	glm::vec2 centerPos_ = glm::vec2(0.0f, 0.0f);

	/** UI 텍스트의 색상입니다. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** UI 텍스트 문자의 외곽선 색상입니다. */
	glm::vec4 outlineColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};