#pragma once

#include <map>

#include "GL/Texture2D.h"

/** 텍스처 아틀라스 리소스입니다. 이 텍스처 아틀라스는 2D 텍스처를 기반으로 합니다. */
class TextureAtlas2D : public Texture2D
{
public:
	/**
	 * 텍스처 아틀라스 내에 경계 영역입니다.
	 * 이때, (x, y)는 텍스처의 왼쪽 상단을 기준으로 한 좌표입니다.
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
	 * 텍스처 아틀라스는 2D 텍스처 내의 요소들의 대한 정보를 포함한 아틀라스 파일을 필요로합니다. 
	 * 이 아틀라스 파일은 프로젝트 내에 TrimTextureAtlas.py 스크립트를 이용해서 생성된 파일입니다.
	 */
	TextureAtlas2D(const std::string& texturePath, const std::string& atlasPath, const EFilter& filter);
	virtual ~TextureAtlas2D();

	DISALLOW_COPY_AND_ASSIGN(TextureAtlas2D);

	virtual void Release() override;

	const Bound& GetByName(const std::string& name);

private:
	/** 텍스처 아틀라스 내의 요소들 이름에 대응하는 경계 영역입니다. */
	std::map<std::string, Bound> elements_;
};