#pragma once

#include "GL/PostProcessor.h"

/** ������ ���ۿ� ������ ȥ���ϴ� ���̴��Դϴ�. */
class BlendColor : public PostProcessor
{
public:
	BlendColor(const std::string& vsSource, const std::string& fsSource);
	virtual ~BlendColor();

	DISALLOW_COPY_AND_ASSIGN(BlendColor);

	/**
	 * ȥ���� ������ �����մϴ�.
	 * �̶�, factor�� ���� 0.0�̸� ������ ȥ������ �ʰ�, 1.0�̸� ȥ�� ���� ǥ���մϴ�.
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
	/** ������ ���ۿ� ȥ���� �����Դϴ�. */
	BlendColorUBO blendColor_;

	/** ������ ������ ���ε� �����Դϴ�. */
	static const uint32_t UNIFORM_BUFFER_BIND_SLOT = 0;

	/** ������ ���ۿ� ������ ȥ���ϴ� ���̴������� ����� ������ �����Դϴ�.  */
	class UniformBuffer* uniformBuffer_ = nullptr;

	/** ������ ������ ������Ʈ�� �ʿ����� Ȯ���մϴ�. */
	bool bIsNeedUpdate_ = false;
};