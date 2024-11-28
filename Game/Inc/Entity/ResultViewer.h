#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Entity/IEntity2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class TTFont;

/** �÷��̾��� �÷��� ����� ȭ�鿡 ǥ���ϴ� ��ƼƼ�Դϴ�. */
class ResultViewer : public IEntity2D
{
public:
	/** �÷��̾��� �÷��� ����� ǥ���ϴ� ��ƼƼ�� �����Դϴ�. */
	enum class EState
	{
		WAIT   = 0x00,
		ACTIVE = 0x01,
		DONE   = 0x02,
	};

public:
	ResultViewer(TTFont* font, const glm::vec2& position, const std::wstring& text, const glm::vec4& textColor, float showTime);
	virtual ~ResultViewer();

	DISALLOW_COPY_AND_ASSIGN(ResultViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** �÷��� ��� ǥ�ø� �����մϴ�. */
	void Start(int32_t playResult);

private:
	/** ���� �÷��̾��� �÷��� ����� ǥ���ϴ� ��ƼƼ�� �����Դϴ�. */
	EState state_ = EState::WAIT;

	/** ����� ǥ���� �� ������ ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;

	/** ǥ���� �÷��� ������Դϴ�. */
	int32_t playResult_ = 0;

	/** ���� �÷��� ��� ���Դϴ�. */
	int32_t currentPlayResult_ = 0;

	/** ����� ǥ���� �߾� ��ġ�Դϴ�. */
	glm::vec2 position_;

	/** ȭ�鿡 ǥ���� �� ������ �ؽ�Ʈ�Դϴ�. */
	std::wstring text_;

	/** ��� �ؽ�Ʈ�Դϴ�. */
	std::wstring resultText_;

	/** ȭ�鿡 ǥ���� �ؽ�Ʈ�� �����Դϴ�. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** ȭ�鿡 ǥ���� �ؽ�Ʈ�� �׸��� �������Դϴ�. */
	glm::vec2 shadowOffset_ = glm::vec2(0.0f, 0.0f);
	
	/** ȭ�鿡 ǥ���� �ؽ�Ʈ�� �׸��� �����Դϴ�. */
	glm::vec4 shadowColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** ����� ǥ���� �� ������ ���� �ð� ���Դϴ�. */
	float resultShowTime_ = 0.0f;

	/** ����� ǥ���� �� ������ �ִ� ���� �ð� ���Դϴ�. */
	float maxResultShowTime_ = 0.0f;
};