#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스 전방 선언입니다. */
class TTFont;

/** 플레이어의 플레이 결과를 화면에 표시하는 엔티티입니다. */
class ResultViewer : public IEntity2D
{
public:
	/** 플레이어의 플레이 결과를 표시하는 엔티티의 상태입니다. */
	enum class EState
	{
		WAIT   = 0x00,
		ACTIVE = 0x01,
		DONE   = 0x02,
	};

public:
	ResultViewer(TTFont* font, const glm::vec2& basePos, const std::wstring& text, const glm::vec4& textColor, float showTime);
	virtual ~ResultViewer();

	DISALLOW_COPY_AND_ASSIGN(ResultViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이 결과 표시를 시작합니다. */
	void Start(int32_t playResult);

private:
	/** 현재 플레이어의 플레이 결과를 표시하는 엔티티의 상태입니다. */
	EState state_ = EState::WAIT;

	/** 결과를 표시할 때 참조할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** 표시할 플레이 결과값입니다. */
	int32_t playResult_ = 0;

	/** 현재 플레이 결과 값입니다. */
	int32_t currentPlayResult_ = 0;

	/** 결과를 표시할 텍스트의 위치입니다. */
	glm::vec2 basePos_;

	/** 화면에 표시할 때 참조할 텍스트입니다. */
	std::wstring text_;

	/** 결과 텍스트입니다. */
	std::wstring resultText_;

	/** 화면에 표시할 텍스트의 색상입니다. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** 화면에 표시할 텍스트의 그림자 오프셋입니다. */
	glm::vec2 shadowOffset_ = glm::vec2(0.0f, 0.0f);
	
	/** 화면에 표시할 텍스트의 그림자 색상입니다. */
	glm::vec4 shadowColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** 결과를 표시할 때 참조할 누적 시간 값입니다. */
	float resultShowTime_ = 0.0f;

	/** 결과를 표시할 때 참조할 최대 누적 시간 값입니다. */
	float maxResultShowTime_ = 0.0f;
};