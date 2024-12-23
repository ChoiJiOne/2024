#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "GL/ITexture.h"

/** 문자 글리프입니다. */
struct Glyph
{
	int32_t codePoint;
	glm::ivec2 pos0;
	glm::ivec2 pos1;
	float xoff;
	float yoff;
	float xoff2;
	float yoff2;
	float xadvance;
};

/** 트루 타입 폰트 리소스입니다. */
class TTFont : public ITexture
{
public:
	TTFont(const std::string& path, int32_t beginCodePoint, int32_t endCodePoint, float fontSize, const EFilter& filter);
	virtual ~TTFont();

	DISALLOW_COPY_AND_ASSIGN(TTFont);

	virtual void Release() override;
	virtual void Active(uint32_t unit) const override;
	virtual int32_t GetWidth() const override { return atlasWidth_; }
	virtual int32_t GetHeight() const override { return atlasHeight_; }

	/** 코드 포인트에 대응하는 글리프를 얻습니다. */
	const Glyph& GetGlyph(int32_t codePoint) const;

	/** 코드 포인트가 현재 트루 타입 폰트 리소스 내에서 유효한지 검사합니다. */
	bool IsValidCodePoint(int32_t codePoint) const;

	/** 텍스트의 크기를 측정합니다. */
	void MeasureText(const std::wstring& text, float& outWidth, float& outHeight) const;

	/** 텍스트의 중앙 위치로부터 텍스트의 기본 위치를 계산합니다. */
	glm::vec2 MeasureBasePos(const std::wstring& text, const glm::vec2& center);
	
private:
	/** 글리프 아틀라스의 비트맵을 생성합니다. */
	std::shared_ptr<uint8_t[]> CreateGlyphAtlasBitmap(const std::vector<uint8_t>& buffer);

	/** 글리프 아틀라스의 비트맵을 이용해서 텍스처 리소스를 생성합니다. */
	uint32_t CreateGlyphTextureAtlas(const std::shared_ptr<uint8_t[]>& bitmap, const EFilter& filter);

private:
	/** 글리프 아틀라스의 최소 크기입니다. */
	static const uint32_t MIN_GLYPH_ATLAS_SIZE = 16;

	/** 글리프 아틀라스의 최대 크기입니다. */
	static const uint32_t MAX_GLYPH_ATLAS_SIZE = 4096;

	/** 글리프 아틀라스 내의 문자열 간격입니다. */
	static const uint32_t GLYPH_PADDING_SIZE = 4;

	/** 폰트의 크기입니다. */
	float fontSize_ = 0.0f;

	/** 폰트의 시작 코드 포인트입니다. 이때, 시작은 전체 범위에 포함됩니다. */
	int32_t beginCodePoint_ = 0;

	/** 폰트의 끝 코드 포인트입니다. 이때 끝은 전체 범위에 포함됩니다. */
	int32_t endCodePoint_ = 0;

	/** 텍스처 아틀라스의 가로 크기입니다. */
	int32_t atlasWidth_ = 0;

	/** 텍스처 아틀라스의 세로 크기입니다. */
	int32_t atlasHeight_ = 0;

	/** 코드 포인트 범위에 대응하는 글리프입니다. */
	std::vector<Glyph> glyphs_;

	/** 텍스처 아틀라스의 리소스입니다. */
	uint32_t atlasID_ = 0;
};