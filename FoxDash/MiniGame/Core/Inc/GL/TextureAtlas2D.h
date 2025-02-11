#pragma once

#include <map>

#include "GL/Texture2D.h"

/** �ؽ�ó ��Ʋ�� ���ҽ��Դϴ�. �� �ؽ�ó ��Ʋ�󽺴� 2D �ؽ�ó�� ������� �մϴ�. */
class TextureAtlas2D : public Texture2D
{
public:
	/**
	 * �ؽ�ó ��Ʋ�� ���� ��� �����Դϴ�.
	 * �̶�, (x, y)�� �ؽ�ó�� ���� ����� �������� �� ��ǥ�Դϴ�.
	 */
	struct Bound
	{
		int32_t x;
		int32_t y;
		int32_t w;
		int32_t h;
	};

public:
	/** 
	 * �ؽ�ó ��Ʋ�󽺴� 2D �ؽ�ó ���� ��ҵ��� ���� ������ ������ ��Ʋ�� ������ �ʿ���մϴ�. 
	 * �� ��Ʋ�� ������ ������Ʈ ���� TrimTextureAtlas.py ��ũ��Ʈ�� �̿��ؼ� ������ �����Դϴ�.
	 */
	TextureAtlas2D(const std::string& texturePath, const std::string& atlasPath, const EFilter& filter);
	virtual ~TextureAtlas2D();

	DISALLOW_COPY_AND_ASSIGN(TextureAtlas2D);

	virtual void Release() override;

	const Bound& GetByName(const std::string& name);

private:
	/** �ؽ�ó ��Ʋ�� ���� ��ҵ� �̸��� �����ϴ� ��� �����Դϴ�. */
	std::map<std::string, Bound> elements_;
};