#pragma once

#include <string>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

/** 클래스의 전방 선언입니다. */
class TTFont;
class TextureAtlas2D;

/** UI 스킬 엔티티입니다. */
class UISkill : public IEntity2D
{
public:
	/** UI 스킬의 내부 속성을 설정하기 위해서는 Json 포멧의 파일이 필요합니다. */
	UISkill(const std::string& skillPath, TTFont* font);
	virtual ~UISkill();

	DISALLOW_COPY_AND_ASSIGN(UISkill);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** 스킬 쿨타임을 시작합니다. */
	void Start();

	/** 스킬 쿨타임 값을 얻습니다. */
	float GetSkillCoolTime() const { return skillCoolTime_; }

	/** 최대 스킬 쿨타임 값을 얻습니다. */
	float GetMaxSkillCoolTime() const { return maxSkillCoolTime_; }
	
	/** 스킬 쿨타임이 남았는지 확인합니다. */
	bool IsRemainCoolTime() { return bIsRemainCoolTime_; }

private:
	/** 스킬 쿨타임을 표시할 때의 범위입니다. */
	struct SkillCoolTimeRange
	{
		glm::vec2 startPos;
		glm::vec2 endPos;
		float startRadian;
		float endRadian;
	};

	/** UI 스킬 내의 속성들을 초기화합니다. */
	void InitProperties(const std::string& skillPath);

private:
	/** UI 스킬의 남은 쿨타임 시간을 표시할 때 사용할 폰트입니다. */
	TTFont* font_ = nullptr;

	/** UI 스킬 아이콘 렌더링 시 참조할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 아틀라스 내에 스킬 아이콘 텍스처의 이름입니다. */
	std::string skillIconName_;

	/** UI 스킬 아이콘의 영역입니다. */
	Rect2D skillIcon_;

	/** UI 스킬의 쿨타임 계산을 위한 영역입니다. */
	Circle2D coolTimeBound_;

	/** 쿨 타임이 남았는지 확인합니다. */
	bool bIsRemainCoolTime_ = false;

	/** 스킬 쿨타임입니다. */
	float skillCoolTime_ = 0.0f;

	/** 최대 스킬 쿨타임입니다. */
	float maxSkillCoolTime_ = 0.0f;

	/** 스킬 쿨 타임을 표시할 때 참조할 위치입니다. */
	glm::vec2 skillCoolTimePos_ = glm::vec2(0.0f, 0.0f);

	/** 스킬 쿨 타임을 표시할 때 참조할 회전 각도입니다. */
	float skillCoolTimeRadian_ = 0.0f;

	/** 스킬 쿨 타임을 표시할 때 참조할 위치별 회전 각도 영역입니다. */
	std::vector<SkillCoolTimeRange> skillCoolTimeRanges_;

	/** 스킬 쿨타임 색상입니다. */
	glm::vec4 skillCoolTimeColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** 스킬 쿨타임의 남은 시간입니다. */
	int32_t remainTime_ = -1;

	/** 스킬 쿨타임의 남은 시간의 텍스트 형식입니다. */
	std::wstring remainTimeText_;

	/** 스킬 쿨타임의 남은 시간 텍스트의 색상입니다. */
	glm::vec4 remainTimeTextColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};