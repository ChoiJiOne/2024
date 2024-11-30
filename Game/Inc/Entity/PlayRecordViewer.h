#pragma once

#include <array>
#include <string>

#include <glm/glm.hpp>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방선언입니다. */
class TTFont;

/** 플레이 기록을 보여주는 엔티티입니다. */
class PlayRecordViewer : public IEntity2D
{
public:
	PlayRecordViewer();
	virtual ~PlayRecordViewer();

	DISALLOW_COPY_AND_ASSIGN(PlayRecordViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 플레이 기록을 업데이트합니다. */
	void Update();

private:
	/** 화면에 표시할 기록의 종류입니다. */
	enum class EType
	{
		TOTAL_PLAY_TIME = 0x00,
		TOTAL_COIN      = 0x01,
		TOTAL_USE_SKILL = 0x02,
		TOTAL_HEAL_HP   = 0x03,
		TOTAL_LOST_HP   = 0x04,
		TOTAL_HEAL_MP   = 0x05,
		TOTAL_LOST_MP   = 0x06,
	};

	/** 화면에 표시할 기록입니다. */
	struct PlayRecord
	{
		EType type;
		glm::vec2 basePos = glm::vec2(0.0f, 0.0f);
		glm::vec4 textColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		std::wstring text;
	};

private:
	/** 플레이 기록 백그라운드의 위치 및 크기입니다. */
	Rect2D background_;

	/** 플레이 기록 백그라운드의 색상입니다. */
	glm::vec4 backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	/** 플레이 기록을 렌더링할 때 참조할 폰트입니다. */
	TTFont* font_ = nullptr;
	
	/** 플레이 기록을 렌더링할 때의 기준 위치입니다. */
	glm::vec2 basePos_ = glm::vec2(0.0f, 0.0f);

	/** 플레이 기록 텍스트의 외곽선 색상입니다. */
	glm::vec4 outlineColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	/** 기록들 간의 간격입니다. */
	float stride_ = 0.0f;

	/** 플레이 기록의 개수입니다. */
	static const uint32_t MAX_COUNT_PLAY_RECORD = 7;

	/** 표시할 플레이 기록입니다. */
	std::array<PlayRecord, MAX_COUNT_PLAY_RECORD> playRecords_;
};