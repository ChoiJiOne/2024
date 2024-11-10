#pragma once

#include "GL/Shader.h"

/** 후처리를 수행하는 셰이더입니다. */
class PostProcessor : public Shader
{
public:
	PostProcessor(const std::string& vsSource, const std::string& fsSource);
	virtual ~PostProcessor();

	DISALLOW_COPY_AND_ASSIGN(PostProcessor);

	virtual void Release() override;

	/** 프레임 버퍼를 전송합니다. */
	virtual void Blit(class FrameBuffer* frameBuffer);

protected:
	/** 후처리를 수행하는 셰이더 내부에서만 사용하는 정점입니다. */
	struct Vertex
	{
		glm::vec2 position;
		glm::vec2 uv;

		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}
	};

protected:
	/** 내부에서 사용하는 정점의 최대 크기입니다. */
	static const uint32_t MAX_VERTEX_SIZE = 6;

	/** 프레임 버퍼의 바인딩 슬롯입니다. */
	static const uint32_t FRAME_BUFFER_BIND_SLOT = 0;

	/** 스크린 크기에 대응하는 정점 배열 오브젝트입니다. */
	uint32_t vertexArrayObject_ = 0;

	/** 스크린 크기에 대응하는 정점 버퍼입니다. */
	class VertexBuffer* vertexBuffer_ = nullptr;
};