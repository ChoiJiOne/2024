#include <json/json.h>

#include "Entity/UIPanel.h"
#include "GL/RenderManager2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

UIPanel::UIPanel(const std::string& panelPath, TextureAtlas2D* textureAtlas)
	: textureAtlas_(textureAtlas)
{
	InitProperties(panelPath);
	bIsInitialized_ = true;
}

UIPanel::~UIPanel()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIPanel::Tick(float deltaSeconds)
{
	// Nothing...
}

void UIPanel::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, name_, bound_.center, bound_.size.x, bound_.size.y, 0.0f);
}

void UIPanel::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

void UIPanel::InitProperties(const std::string& panelPath)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(panelPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", panelPath.c_str());

	CHECK(root["Name"].isString() && !root["Name"].isNull());
	name_ = root["Name"].asString();

	CHECK(root["Bound"].isObject() && !root["Bound"].isNull());
	const Json::Value& bound = root["Bound"];

	CHECK(bound["x"].isDouble() && !bound["x"].isNull());
	CHECK(bound["y"].isDouble() && !bound["y"].isNull());
	CHECK(bound["w"].isDouble() && !bound["w"].isNull());
	CHECK(bound["h"].isDouble() && !bound["h"].isNull());

	bound_.center.x = bound["x"].asFloat();
	bound_.center.y = bound["y"].asFloat();
	bound_.size.x = bound["w"].asFloat();
	bound_.size.y = bound["h"].asFloat();
}