#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;

/** UI 바 엔티티입니다. */
class UIBar : public IEntity2D
{
public:
	/** UI 바의 내부 속성을 설정하기 위해서는 Json 포멧의 파일이 필요합니다. */
	UIBar(const std::string& barPath, TTFont* font);
	virtual ~UIBar();

	DISALLOW_COPY_AND_ASSIGN(UIBar);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** UI내의 현재 Bar를 얻습니다. */
	float GetBar() const { return bar_; }

	/** UI내의 Bar 값을 설정합니다. */
	void SetBar(float bar);

	/** UI내 Bar의 최대 값을 얻습니다. */
	float GetMaxBar() const { return maxBar_; }
	
	/** UI내 Bar의 최대 값을 설정합니다. */
	void SetMaxBar(float maxBar);

private:
	/** UI바 내의 속성들을 초기화합니다. */
	void InitProperties(const std::string& barPath);

private:
	/** UI바에 텍스트를 렌더링할 때 참조할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** UI바의 백그라운드 크기입니다. */
	Rect2D background_;

	/** UI바의 영역입니다. */
	Rect2D barBound_;

	/** UI바의 백그라운드 색상입니다. */
	glm::vec4 backgroundColor_;

	/** UI바의 색상입니다. */
	glm::vec4 barColor_;

	/** UI바 내의 텍스트 색상입니다. */
	glm::vec4 textColor_;

	/** UI바 내의 Bar입니다. */
	float bar_ = 0.0f;

	/** 부드러운 전환을 위한 마크입니다. */
	float barMark_ = 0.0f;

	/** UI바 내의 Bar 최대 값입니다.. */
	float maxBar_ = 0.0f;

	/** 부드러운 전환을 위한 속도입니다. */
	float barSlideSpeed_ = 0.0f;

	/** UI바에 표시할 텍스트입니다. */
	std::wstring text_;
};