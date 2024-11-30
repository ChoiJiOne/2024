#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TTFont;

/** UI �ؽ�Ʈ ��ƼƼ�Դϴ�. */
class UIText : public IEntity2D
{
public:
	/** UI �ؽ�Ʈ�� ���� �Ӽ��� �����ϱ� ���ؼ��� Json ������ ������ �ʿ��մϴ�. */
	UIText(const std::string& textPath, TTFont* font);
	virtual ~UIText();

	DISALLOW_COPY_AND_ASSIGN(UIText);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** UI �ؽ�Ʈ ���� �Ӽ����� �ʱ�ȭ�մϴ�. */
	void InitProperties(const std::string& textPath);

private:
	/** UI �ؽ�Ʈ ������ �� ������ ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;

	/** UI �ؽ�Ʈ�Դϴ�. */
	std::wstring text_;

	/** UI �ؽ�Ʈ ������ �� ������ �Ǵ� ��ġ�Դϴ�. */
	glm::vec2 centerPos_ = glm::vec2(0.0f, 0.0f);

	/** UI �ؽ�Ʈ�� �����Դϴ�. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** UI �ؽ�Ʈ ������ �ܰ��� �����Դϴ�. */
	glm::vec4 outlineColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};