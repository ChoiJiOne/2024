#pragma once

#include <memory>
#include <string>
#include <vector>

#include "GameMath.h"
#include "IResource.h"


namespace GameMaker
{
struct Glyph
{
	int32_t codePoint;
	Vec2i pos0;
	Vec2i pos1;
	float xoff;
	float yoff;
	float xoff2;
	float yoff2;
	float xadvance;
};

/** Ʈ�� Ÿ�� ��Ʈ�� .ttf �� �����մϴ�. */
class TTFont : public IResource
{
public:
	explicit TTFont(const std::string& path, int32_t beginCodePoint, int32_t endCodePoint, float fontSize);
	virtual ~TTFont();

	DISALLOW_COPY_AND_ASSIGN(TTFont);

	virtual void Release() override;

	uint32_t GetGlyphAtlasID() const { return glyphAtlasID_; }
	const Glyph& GetGlyph(int32_t codePoint) const;
	int32_t GetGlyphAtlasSize() const { return glyphAtlasSize_; }
	bool IsValidCodePoint(int32_t codePoint) const;
	void MeasureText(const std::wstring& text, float& outWidth, float& outHeight) const;

private:
	std::shared_ptr<uint8_t[]> GenerateGlyphAtlasBitmap(const std::vector<uint8_t>& buffer, int32_t beginCodePoint, int32_t endCodePoint, float fontSize, std::vector<Glyph>& outGlyphs, int32_t& outGlyphAtlasSize);
	uint32_t CreateGlyphAtlasFromBitmap(const std::shared_ptr<uint8_t[]>& bitmap, const int32_t& glyphAtlasSize);

private:
	int32_t beginCodePoint_ = 0;
	int32_t endCodePoint_ = 0;
	int32_t glyphAtlasSize_ = 0;
	std::vector<Glyph> glyphs_;
	uint32_t glyphAtlasID_ = 0;
};

}