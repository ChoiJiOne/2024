#pragma once

#include <array>
#include <string>

#include <glm/glm.hpp>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���漱���Դϴ�. */
class TTFont;

/** �÷��� ����� �����ִ� ��ƼƼ�Դϴ�. */
class PlayRecordViewer : public IEntity2D
{
public:
	PlayRecordViewer();
	virtual ~PlayRecordViewer();

	DISALLOW_COPY_AND_ASSIGN(PlayRecordViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** �÷��� ����� ������Ʈ�մϴ�. */
	void Update();

private:
	/** ȭ�鿡 ǥ���� ����� �����Դϴ�. */
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

	/** ȭ�鿡 ǥ���� ����Դϴ�. */
	struct PlayRecord
	{
		EType type;
		glm::vec2 basePos = glm::vec2(0.0f, 0.0f);
		glm::vec4 textColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		std::wstring text;
	};

private:
	/** �÷��� ��� ��׶����� ��ġ �� ũ���Դϴ�. */
	Rect2D background_;

	/** �÷��� ��� ��׶����� �����Դϴ�. */
	glm::vec4 backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	/** �÷��� ����� �������� �� ������ ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;
	
	/** �÷��� ����� �������� ���� ���� ��ġ�Դϴ�. */
	glm::vec2 basePos_ = glm::vec2(0.0f, 0.0f);

	/** �÷��� ��� �ؽ�Ʈ�� �ܰ��� �����Դϴ�. */
	glm::vec4 outlineColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	/** ��ϵ� ���� �����Դϴ�. */
	float stride_ = 0.0f;

	/** �÷��� ����� �����Դϴ�. */
	static const uint32_t MAX_COUNT_PLAY_RECORD = 7;

	/** ǥ���� �÷��� ����Դϴ�. */
	std::array<PlayRecord, MAX_COUNT_PLAY_RECORD> playRecords_;
};