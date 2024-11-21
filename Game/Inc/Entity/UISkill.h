#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class TTFont;
class TextureAtlas2D;
class UICamera;

/** UI ��ų ��ƼƼ�Դϴ�. */
class UISkill : public IEntity2D
{
public:
	/** UI ��ų�� ���� �Ӽ��� �����ϱ� ���ؼ��� Json ������ ������ �ʿ��մϴ�. */
	UISkill(UICamera* uiCamera, TTFont* font, const std::string& skillPath);
	virtual ~UISkill();

	DISALLOW_COPY_AND_ASSIGN(UISkill);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ��ų ��Ÿ���� �����մϴ�. */
	void Start();

	/** ��ų ��Ÿ�� ���� ����ϴ�. */
	float GetSkillCoolTime() const { return skillCoolTime_; }

	/** �ִ� ��ų ��Ÿ�� ���� ����ϴ�. */
	float GetMaxSkillCoolTime() const { return maxSkillCoolTime_; }
	
	/** ��ų ��Ÿ���� ���Ҵ��� Ȯ���մϴ�. */
	bool IsRemainCoolTime() { return bIsRemainCoolTime_; }

private:
	/** ��ų ��Ÿ���� ǥ���� ���� �����Դϴ�. */
	struct SkillCoolTimeRange
	{
		glm::vec2 startPos;
		glm::vec2 endPos;
		float startRadian;
		float endRadian;
	};

	/** UI ��ų ���� �Ӽ����� �ʱ�ȭ�մϴ�. */
	void InitProperties(const std::string& skillPath);

private:
	/** UI ��ų �������� ������ �� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** UI ��ų�� ���� ��Ÿ�� �ð��� ǥ���� �� ����� ��Ʈ�Դϴ�. */
	TTFont* font_ = nullptr;

	/** UI ��ų ������ ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ��Ʋ�� ���� ��ų ������ �ؽ�ó�� �̸��Դϴ�. */
	std::string skillIconName_;

	/** UI ��ų �������� �����Դϴ�. */
	Rect2D skillIcon_;

	/** UI ��ų�� ��Ÿ�� ����� ���� �����Դϴ�. */
	Circle2D coolTimeBound_;

	/** �� Ÿ���� ���Ҵ��� Ȯ���մϴ�. */
	bool bIsRemainCoolTime_ = false;

	/** ��ų ��Ÿ���Դϴ�. */
	float skillCoolTime_ = 0.0f;

	/** �ִ� ��ų ��Ÿ���Դϴ�. */
	float maxSkillCoolTime_ = 0.0f;

	/** ��ų �� Ÿ���� ǥ���� �� ������ ��ġ�Դϴ�. */
	glm::vec2 skillCoolTimePos_ = glm::vec2(0.0f, 0.0f);

	/** ��ų �� Ÿ���� ǥ���� �� ������ ȸ�� �����Դϴ�. */
	float skillCoolTimeRadian_ = 0.0f;

	/** ��ų �� Ÿ���� ǥ���� �� ������ ��ġ�� ȸ�� ���� �����Դϴ�. */
	std::vector<SkillCoolTimeRange> skillCoolTimeRanges_;

	/** ��ų ��Ÿ�� �����Դϴ�. */
	glm::vec4 skillCoolTimeColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** ��ų ��Ÿ���� ���� �ð��Դϴ�. */
	int32_t remainTime_ = -1;

	/** ��ų ��Ÿ���� ���� �ð��� �ؽ�Ʈ �����Դϴ�. */
	std::wstring remainTimeText_;

	/** ��ų ��Ÿ���� ���� �ð� �ؽ�Ʈ�� �����Դϴ�. */
	glm::vec4 remainTimeTextColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};