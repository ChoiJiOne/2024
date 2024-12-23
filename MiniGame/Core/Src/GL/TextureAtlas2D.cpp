#include <json/json.h>

#include "GL/GLAssertion.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

TextureAtlas2D::TextureAtlas2D(const std::string& texturePath, const std::string& atlasPath, const EFilter& filter)
	: Texture2D(texturePath, filter)
{
	std::vector<uint8_t> buffer;
	std::string errMsg;
	ASSERTION(ReadFile(atlasPath, buffer, errMsg), "%s", errMsg.c_str());

	std::string jsonString(buffer.begin(), buffer.end());
	Json::Value root;
	Json::Reader reader;
	ASSERTION(reader.parse(jsonString, root), "Failed to parse '%s' file.", atlasPath.c_str());

	for (const auto& key : root.getMemberNames())
	{
		const Json::Value& element = root[key];

		CHECK(element["x"].isInt() && !element["x"].isNull());
		CHECK(element["y"].isInt() && !element["y"].isNull());
		CHECK(element["w"].isInt() && !element["w"].isNull());
		CHECK(element["h"].isInt() && !element["h"].isNull());

		Bound bound;
		bound.x = element["x"].asInt();
		bound.y = element["y"].asInt();
		bound.w = element["w"].asInt();
		bound.h = element["h"].asInt();

		elements_.insert({ key.c_str(), bound });
	}
}

TextureAtlas2D::~TextureAtlas2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TextureAtlas2D::Release()
{
	Texture2D::Release();
}

const TextureAtlas2D::Bound& TextureAtlas2D::GetByName(const std::string& name)
{
	auto it = elements_.find(name);
	CHECK(it != elements_.end());

	return it->second;
}