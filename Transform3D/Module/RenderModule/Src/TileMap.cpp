#include <glad/glad.h>

#include "Assertion.h"
#include "RenderModule.h"
#include "Shader.h"
#include "TileMap.h"

TileMap::TileMap(const ESize& size, const ESize& tileSize, const Vec4f& pattern0, const Vec4f& pattern1)
{
	CHECK(size >= tileSize);
	static Shader* tileMapGenerator = RenderModule::GetGlobalResource<Shader>("TileMapGenerator");

	width_ = static_cast<int32_t>(size);
	height_ = static_cast<int32_t>(size);

	GL_FAILED(glGenTextures(1, &textureID_));
	GL_FAILED(glBindTexture(GL_TEXTURE_2D, textureID_));
	GL_FAILED(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width_, height_, 0, GL_RGBA, GL_FLOAT, nullptr));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_FAILED(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	tileMapGenerator->Bind();
	{
		tileMapGenerator->SetUniform("tileSize", static_cast<int32_t>(tileSize));
		tileMapGenerator->SetUniform("pattern0", pattern0);
		tileMapGenerator->SetUniform("pattern1", pattern1);

		uint32_t workGroupX = static_cast<uint32_t>(width_) / 32;
		uint32_t workGroupY = static_cast<uint32_t>(height_) / 32;
		uint32_t workGroupZ = 1;
		
		GL_FAILED(glBindImageTexture(0, textureID_, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
		GL_FAILED(glDispatchCompute(workGroupX, workGroupY, workGroupZ));
	}
	tileMapGenerator->Unbind();

	GL_FAILED(glBindTexture(GL_TEXTURE_2D, 0));
}

TileMap::~TileMap()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TileMap::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteTextures(1, &textureID_));

	bIsInitialized_ = false;
}

void TileMap::Active(uint32_t unit) const
{
	GL_FAILED(glActiveTexture(GL_TEXTURE0 + unit));
	GL_FAILED(glBindTexture(GL_TEXTURE_2D, textureID_));
}