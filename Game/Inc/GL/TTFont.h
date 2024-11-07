#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "ITexture.h"

/** ���� �۸����Դϴ�. */
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

/** Ʈ�� Ÿ�� ��Ʈ ���ҽ��Դϴ�. */
class TTFont : public ITexture
{
public:
	TTFont(const std::string& path, int32_t beginCodePoint, int32_t endCodePoint, float fontSize);
	virtual ~TTFont();

	DISALLOW_COPY_AND_ASSIGN(TTFont);

	virtual void Release() override;
	virtual void Active(uint32_t unit) const override;

	/** Ʈ�� Ÿ�� ��Ʈ ���ҽ��� ������Ƽ�� ���� Getter�Դϴ�. */
	const Glyph& GetGlyph(int32_t codePoint) const;
	int32_t GetAtlasWidth() const { return atlasWidth_; }
	int32_t GetAtlasHeight() const { return atlasHeight_; }

	/** �ڵ� ����Ʈ�� ���� Ʈ�� Ÿ�� ��Ʈ ���ҽ� ������ ��ȿ���� �˻��մϴ�. */
	bool IsValidCodePoint(int32_t codePoint) const;

private:
	/** �۸��� ��Ʋ���� ��Ʈ���� �����մϴ�. */
	std::shared_ptr<uint8_t[]> CreateGlyphAtlasBitmap(const std::vector<uint8_t>& buffer);

	/** �۸��� ��Ʋ���� ��Ʈ���� �̿��ؼ� �ؽ�ó ���ҽ��� �����մϴ�. */
	uint32_t CreateGlyphTextureAtlas(const std::shared_ptr<uint8_t[]>& bitmap);

private:
	/** �۸��� ��Ʋ���� �ּ� ũ���Դϴ�. */
	static const uint32_t MIN_GLYPH_ATLAS_SIZE = 16;

	/** �۸��� ��Ʋ���� �ִ� ũ���Դϴ�. */
	static const uint32_t MAX_GLYPH_ATLAS_SIZE = 4096;

	/** �۸��� ��Ʋ�� ���� ���ڿ� �����Դϴ�. */
	static const uint32_t GLYPH_PADDING_SIZE = 4;

	/** ��Ʈ�� ũ���Դϴ�. */
	float fontSize_ = 0.0f;

	/** ��Ʈ�� ���� �ڵ� ����Ʈ�Դϴ�. �̶�, ������ ��ü ������ ���Ե˴ϴ�. */
	int32_t beginCodePoint_ = 0;

	/** ��Ʈ�� �� �ڵ� ����Ʈ�Դϴ�. �̶� ���� ��ü ������ ���Ե˴ϴ�. */
	int32_t endCodePoint_ = 0;

	/** �ؽ�ó ��Ʋ���� ���� ũ���Դϴ�. */
	int32_t atlasWidth_ = 0;

	/** �ؽ�ó ��Ʋ���� ���� ũ���Դϴ�. */
	int32_t atlasHeight_ = 0;

	/** �ڵ� ����Ʈ ������ �����ϴ� �۸����Դϴ�. */
	std::vector<Glyph> glyphs_;

	/** �ؽ�ó ��Ʋ���� ���ҽ��Դϴ�. */
	uint32_t atlasID_ = 0;
};