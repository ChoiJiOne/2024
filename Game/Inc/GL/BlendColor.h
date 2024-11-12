#pragma once

#include "GL/PostProcessor.h"

/** 프레임 버퍼에 색상을 혼합하는 셰이더입니다. */
class BlendColor : public PostProcessor
{
public:
	BlendColor(const std::string& vsSource, const std::string& fsSource);
	virtual ~BlendColor();

	DISALLOW_COPY_AND_ASSIGN(BlendColor);

	/**
	 * 혼합할 색상을 설정합니다.
	 * 이때, factor의 값이 0.0이면 색상을 혼합하지 않고, 1.0이면 혼합 색상만 표시합니다.
	 */
	void SetBlendColor(const glm::vec3& color, float factor);

	virtual void Release() override;
	virtual void Blit(class FrameBuffer* frameBuffer) override;

protected:
	struct BlendColorUBO
	{
		glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	};

private:
	/** 프레임 버퍼와 혼합할 색상입니다. */
	BlendColorUBO blendColor_;

	/** 유니폼 버퍼의 바인딩 슬롯입니다. */
	static const uint32_t UNIFORM_BUFFER_BIND_SLOT = 0;

	/** 프레임 버퍼에 색상을 혼합하는 셰이더에서만 사용할 유니폼 버퍼입니다.  */
	class UniformBuffer* uniformBuffer_ = nullptr;

	/** 유니폼 버퍼의 업데이트가 필요한지 확인합니다. */
	bool bIsNeedUpdate_ = false;
};