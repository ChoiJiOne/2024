#pragma once

#include "GL/Shader.h"

/** 후처리를 수행하는 셰이더입니다. */
class PostProcessor : public Shader
{
public:
	/** 후처리 방식입니다. */
	enum class EType
	{
		BLIT          = 0x00,
		BLEND_COLOR   = 0x01,
		INVERSION     = 0x02,
		GRAYSCALE     = 0x03,
		GAUSSIAN_BLUR = 0x04,
	};

public:
	PostProcessor(const std::string& vsSource, const std::string& fsSource);
	virtual ~PostProcessor();

	DISALLOW_COPY_AND_ASSIGN(PostProcessor);

	virtual void Release() override;

	/**
	 * 혼합할 색상을 설정합니다. 
	 * 이때, factor의 값이 0.0이면 색상을 혼합하지 않고, 1.0이면 혼합 색상만 표시합니다.
	 */
	void SetBlendColor(const glm::vec3& color, float factor);

	/** 프레임 버퍼를 전송합니다. */
	virtual void Blit(const EType& type, class FrameBuffer* frameBuffer);

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

	/** 후처리 셰이더 내의 유니폼 버퍼입니다. */
	struct PerFrameUBO
	{
		glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		int32_t type = 0; /** 후처리 방식입니다. */
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

	/** 매 프레임 변경되는 유니폼 버퍼입니다. */
	PerFrameUBO perFrameUBO_;

	/** 유니폼 버퍼의 바인딩 슬롯입니다. */
	static const uint32_t UNIFORM_BUFFER_BIND_SLOT = 0;

	/** 프레임 버퍼에 색상을 혼합하는 셰이더에서만 사용할 유니폼 버퍼입니다.  */
	class UniformBuffer* uniformBuffer_ = nullptr;

	/** 유니폼 버퍼의 업데이트가 필요한지 확인합니다. */
	bool bIsNeedUpdate_ = false;
};