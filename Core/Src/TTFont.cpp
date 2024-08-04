#pragma warning(push)
#pragma warning(disable: 26451)

#include <glad/glad.h>
#include <stb_rect_pack.h>
#include <stb_truetype.h>

#include "Assertion.h"
#include "FileUtils.h"
#include "TTFont.h"

using namespace GameMaker;

TTFont::TTFont(const std::string& path, int32_t beginCodePoint, int32_t endCodePoint, float fontSize)
	: beginCodePoint_(beginCodePoint)
	, endCodePoint_(endCodePoint)
{
	std::vector<uint8_t> buffer = FileUtils::ReadFile(path);

	stbtt_fontinfo info;
	const uint8_t* bufferPtr = reinterpret_cast<const uint8_t*>(buffer.data());
	CHECK((stbtt_InitFont(&info, bufferPtr, stbtt_GetFontOffsetForIndex(bufferPtr, 0)) != 0));

	std::shared_ptr<uint8_t[]> glyphAtlasBitmap = GenerateGlyphAtlasBitmap(buffer, beginCodePoint_, endCodePoint_, fontSize, glyphs_, glyphAtlasSize_);
	glyphAtlasID_ = CreateGlyphAtlasFromBitmap(glyphAtlasBitmap, glyphAtlasSize_);

	bIsInitialized_ = true;
}

TTFont::~TTFont()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TTFont::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteTextures(1, &glyphAtlasID_));

	bIsInitialized_ = false;
}

const Glyph& TTFont::GetGlyph(int32_t codePoint) const
{
	CHECK(IsValidCodePoint(codePoint));

	int32_t index = codePoint - beginCodePoint_;
	return glyphs_[index];
}

bool TTFont::IsValidCodePoint(int32_t codePoint) const
{
	return (beginCodePoint_ <= codePoint) && (codePoint <= endCodePoint_);
}

void TTFont::MeasureText(const std::wstring& text, float& outWidth, float& outHeight) const
{
	float width = 0;
	float minY = +1.0f;
	float maxY = -1.0f;

	for (uint32_t index = 0; index < text.size(); ++index)
	{
		const Glyph& glyph = GetGlyph(static_cast<int32_t>(text[index]));

		if (index == text.size() - 1)
		{
			width += static_cast<float>(glyph.pos1.x - glyph.pos0.x) + glyph.xoff;
		}
		else
		{
			width += glyph.xadvance;
		}

		float y0 = glyph.yoff;
		float y1 = static_cast<float>(glyph.pos1.y - glyph.pos0.y) + glyph.yoff;

		minY = GameMaker::Min<float>(y0, minY);
		maxY = GameMaker::Max<float>(y1, maxY);
	}

	outWidth = width;
	outHeight = static_cast<float>(GameMaker::Abs(maxY - minY));
}

std::shared_ptr<uint8_t[]> TTFont::GenerateGlyphAtlasBitmap(const std::vector<uint8_t>& buffer, int32_t beginCodePoint, int32_t endCodePoint, float fontSize, std::vector<Glyph>& outGlyphs, int32_t& outGlyphAtlasSize)
{
	std::vector<stbtt_packedchar> packedchars(endCodePoint - beginCodePoint + 1);
	outGlyphs.resize(endCodePoint - beginCodePoint + 1);

	int32_t success = 0;
	stbtt_pack_context packContext;
	std::shared_ptr<uint8_t[]> bitmap = nullptr;

	for (int32_t size = 16; size < 8192; size *= 2)
	{
		bitmap = std::make_unique<uint8_t[]>(size * size);
		success = stbtt_PackBegin(&packContext, bitmap.get(), size, size, 0, 1, nullptr);
		stbtt_PackSetOversampling(&packContext, 1, 1);

		success = stbtt_PackFontRange(&packContext, buffer.data(), 0, fontSize, beginCodePoint, static_cast<int>(packedchars.size()), packedchars.data());
		if (success)
		{
			stbtt_PackEnd(&packContext);
			outGlyphAtlasSize = size;
			break;
		}
		else
		{
			stbtt_PackEnd(&packContext);
			bitmap.reset();
		}
	}

	for (std::size_t index = 0; index < packedchars.size(); ++index)
	{
		outGlyphs[index].codePoint = static_cast<int32_t>(index + beginCodePoint);
		outGlyphs[index].pos0 = Vec2i(packedchars[index].x0, packedchars[index].y0);
		outGlyphs[index].pos1 = Vec2i(packedchars[index].x1, packedchars[index].y1);
		outGlyphs[index].xoff = packedchars[index].xoff;
		outGlyphs[index].yoff = packedchars[index].yoff;
		outGlyphs[index].xoff2 = packedchars[index].xoff2;
		outGlyphs[index].yoff2 = packedchars[index].yoff2;
		outGlyphs[index].xadvance = packedchars[index].xadvance;
	}

	return bitmap;
}

uint32_t TTFont::CreateGlyphAtlasFromBitmap(const std::shared_ptr<uint8_t[]>& bitmap, const int32_t& glyphAtlasSize)
{
	uint32_t textureAtlas;

	GL_FAILED(glGenTextures(1, &textureAtlas));
	GL_FAILED(glBindTexture(GL_TEXTURE_2D, textureAtlas));

	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	const void* bufferPtr = reinterpret_cast<const void*>(&bitmap[0]);
	GL_FAILED(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyphAtlasSize, glyphAtlasSize, 0, GL_RED, GL_UNSIGNED_BYTE, bufferPtr));
	GL_FAILED(glGenerateMipmap(GL_TEXTURE_2D));

	GL_FAILED(glBindTexture(GL_TEXTURE_2D, 0));

	return textureAtlas;
}

#pragma warning(pop)