#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/compatibility.hpp>

#include <json/json.h>

#include "Entity/EntityManager.h"
#include "Entity/UISkill.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"

UISkill::UISkill(const std::string& skillPath, TTFont* font)
	: font_(font)
{
	InitProperties(skillPath);

	bIsInitialized_ = true;
}

UISkill::~UISkill()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UISkill::Tick(float deltaSeconds)
{
	if (!bIsRemainCoolTime_)
	{
		return;
	}

	if (skillCoolTime_ <= 0.0f)
	{
		bIsRemainCoolTime_ = false;
		return;
	}

	skillCoolTime_ -= deltaSeconds;
	skillCoolTime_ = glm::clamp<float>(skillCoolTime_, 0.0f, maxSkillCoolTime_);

	float timeScale = 1.0f - glm::clamp<float>(skillCoolTime_ / maxSkillCoolTime_, 0.0f, 1.0f);
	float radian = glm::lerp(glm::pi<float>() / 2.0f, -3.0f * glm::pi<float>() / 2.0f, timeScale);
	float x = coolTimeBound_.center.x + coolTimeBound_.radius * glm::cos(radian);
	float y = coolTimeBound_.center.y + coolTimeBound_.radius * glm::sin(radian);

	skillCoolTimePos_.x = glm::clamp<float>(x, skillIcon_.center.x - skillIcon_.size.x * 0.5f, skillIcon_.center.x + skillIcon_.size.x * 0.5f);
	skillCoolTimePos_.y = glm::clamp<float>(y, skillIcon_.center.y - skillIcon_.size.y * 0.5f, skillIcon_.center.y + skillIcon_.size.y * 0.5f);
	skillCoolTimeRadian_ = radian;

	if (static_cast<int32_t>(skillCoolTime_) != remainTime_)
	{
		remainTime_ = static_cast<int32_t>(skillCoolTime_);
		remainTimeText_ = PrintF(L"%d", remainTime_);
	}
}

void UISkill::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, skillIconName_, skillIcon_.center, skillIcon_.size.x, skillIcon_.size.y, 0.0f);

	if (!bIsRemainCoolTime_)
	{
		return;
	}

	bool bIsStartSkillCoolTime = false;
	for (const auto& skillCoolTimeRange : skillCoolTimeRanges_)
	{
		if (!bIsStartSkillCoolTime)
		{
			if (skillCoolTimeRange.endRadian <= skillCoolTimeRadian_ && skillCoolTimeRadian_ <= skillCoolTimeRange.startRadian)
			{
				renderManager_->DrawTriangle(skillIcon_.center, skillCoolTimePos_, skillCoolTimeRange.endPos, skillCoolTimeColor_);
				bIsStartSkillCoolTime = true;
			}
		}
		else
		{
			renderManager_->DrawTriangle(skillIcon_.center, skillCoolTimeRange.startPos, skillCoolTimeRange.endPos, skillCoolTimeColor_);
		}
	}

	glm::vec2 basePos = font_->MeasureBasePos(remainTimeText_, skillIcon_.center);
	renderManager_->DrawString(font_, remainTimeText_, basePos, remainTimeTextColor_);
}

void UISkill::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;
	font_ = nullptr;

	bIsInitialized_ = false;
}

void UISkill::Start()
{
	bIsRemainCoolTime_ = true;
	skillCoolTime_ = maxSkillCoolTime_;
}

void UISkill::InitProperties(const std::string& skillPath)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(skillPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", skillPath.c_str());

	CHECK(root["TextureAtlas"].isString() && !root["TextureAtlas"].isNull());
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>(root["TextureAtlas"].asString());

	CHECK(root["SkillIconName"].isString() && !root["SkillIconName"].isNull());
	skillIconName_ = root["SkillIconName"].asString();

	CHECK(root["Icon"].isObject() && !root["Icon"].isNull());
	const Json::Value& icon = root["Icon"];

	CHECK(icon["x"].isDouble() && !icon["x"].isNull());
	CHECK(icon["y"].isDouble() && !icon["y"].isNull());
	CHECK(icon["w"].isDouble() && !icon["w"].isNull());
	CHECK(icon["h"].isDouble() && !icon["h"].isNull());
	skillIcon_.center.x = icon["x"].asFloat();
	skillIcon_.center.y = icon["y"].asFloat();
	skillIcon_.size.x = icon["w"].asFloat();
	skillIcon_.size.y = icon["h"].asFloat();
	
	float x2 = (skillIcon_.size.x * 0.5f) * (skillIcon_.size.x * 0.5f);
	float y2 = (skillIcon_.size.y * 0.5f) * (skillIcon_.size.y * 0.5f);
	coolTimeBound_ = Circle2D(skillIcon_.center, glm::sqrt(x2 + y2));

	CHECK(root["SkillCoolTime"].isDouble() && !root["SkillCoolTime"].isNull());
	maxSkillCoolTime_ = root["SkillCoolTime"].asFloat();
	skillCoolTime_ = 0.0f;

	glm::vec2 skillCoolSize = skillIcon_.size * 0.5f;
	skillCoolTimeRanges_ =
	{
		{ skillIcon_.center + glm::vec2(0.0f,             +skillCoolSize.y), skillIcon_.center + glm::vec2(+skillCoolSize.x, +skillCoolSize.y), +2.0f * glm::pi<float>() / 4.0f, +1.0f * glm::pi<float>() / 4.0f },
		{ skillIcon_.center + glm::vec2(+skillCoolSize.x, +skillCoolSize.y), skillIcon_.center + glm::vec2(+skillCoolSize.x, -skillCoolSize.y), +1.0f * glm::pi<float>() / 4.0f, -1.0f * glm::pi<float>() / 4.0f },
		{ skillIcon_.center + glm::vec2(+skillCoolSize.x, -skillCoolSize.y), skillIcon_.center + glm::vec2(-skillCoolSize.x, -skillCoolSize.y), -1.0f * glm::pi<float>() / 4.0f, -3.0f * glm::pi<float>() / 4.0f },
		{ skillIcon_.center + glm::vec2(-skillCoolSize.x, -skillCoolSize.y), skillIcon_.center + glm::vec2(-skillCoolSize.x, +skillCoolSize.y), -3.0f * glm::pi<float>() / 4.0f, -5.0f * glm::pi<float>() / 4.0f },
		{ skillIcon_.center + glm::vec2(-skillCoolSize.x, +skillCoolSize.y), skillIcon_.center + glm::vec2(0.0f, +skillCoolSize.y), -5.0f * glm::pi<float>() / 4.0f, -6.0f * glm::pi<float>() / 4.0f },
	};

	CHECK(root["SkillCoolTimeColor"].isObject() && !root["SkillCoolTimeColor"].isNull());
	skillCoolTimeColor_.x = root["SkillCoolTimeColor"]["r"].asFloat();
	skillCoolTimeColor_.y = root["SkillCoolTimeColor"]["g"].asFloat();
	skillCoolTimeColor_.z = root["SkillCoolTimeColor"]["b"].asFloat();
	skillCoolTimeColor_.w = root["SkillCoolTimeColor"]["a"].asFloat();

	CHECK(root["RemainTimeTextColor"].isObject() && !root["RemainTimeTextColor"].isNull());
	remainTimeTextColor_.x = root["RemainTimeTextColor"]["r"].asFloat();
	remainTimeTextColor_.y = root["RemainTimeTextColor"]["g"].asFloat();
	remainTimeTextColor_.z = root["RemainTimeTextColor"]["b"].asFloat();
	remainTimeTextColor_.w = root["RemainTimeTextColor"]["a"].asFloat();
}