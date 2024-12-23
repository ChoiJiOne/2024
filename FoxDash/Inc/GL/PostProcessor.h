#pragma once

#include "GL/Shader.h"

/** ��ó���� �����ϴ� ���̴��Դϴ�. */
class PostProcessor : public Shader
{
public:
	/** ��ó�� ����Դϴ�. */
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
	 * ȥ���� ������ �����մϴ�. 
	 * �̶�, factor�� ���� 0.0�̸� ������ ȥ������ �ʰ�, 1.0�̸� ȥ�� ���� ǥ���մϴ�.
	 */
	void SetBlendColor(const glm::vec3& color, float factor);

	/** ������ ���۸� �����մϴ�. */
	virtual void Blit(const EType& type, class FrameBuffer* frameBuffer);

protected:
	/** ��ó���� �����ϴ� ���̴� ���ο����� ����ϴ� �����Դϴ�. */
	struct Vertex
	{
		glm::vec2 position;
		glm::vec2 uv;

		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}
	};

	/** ��ó�� ���̴� ���� ������ �����Դϴ�. */
	struct PerFrameUBO
	{
		glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		int32_t type = 0; /** ��ó�� ����Դϴ�. */
	};

protected:
	/** ���ο��� ����ϴ� ������ �ִ� ũ���Դϴ�. */
	static const uint32_t MAX_VERTEX_SIZE = 6;

	/** ������ ������ ���ε� �����Դϴ�. */
	static const uint32_t FRAME_BUFFER_BIND_SLOT = 0;

	/** ��ũ�� ũ�⿡ �����ϴ� ���� �迭 ������Ʈ�Դϴ�. */
	uint32_t vertexArrayObject_ = 0;

	/** ��ũ�� ũ�⿡ �����ϴ� ���� �����Դϴ�. */
	class VertexBuffer* vertexBuffer_ = nullptr;

	/** �� ������ ����Ǵ� ������ �����Դϴ�. */
	PerFrameUBO perFrameUBO_;

	/** ������ ������ ���ε� �����Դϴ�. */
	static const uint32_t UNIFORM_BUFFER_BIND_SLOT = 0;

	/** ������ ���ۿ� ������ ȥ���ϴ� ���̴������� ����� ������ �����Դϴ�.  */
	class UniformBuffer* uniformBuffer_ = nullptr;

	/** ������ ������ ������Ʈ�� �ʿ����� Ȯ���մϴ�. */
	bool bIsNeedUpdate_ = false;
};