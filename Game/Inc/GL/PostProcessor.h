#pragma once

#include "GL/Shader.h"

/** ��ó���� �����ϴ� ���̴��Դϴ�. */
class PostProcessor : public Shader
{
public:
	PostProcessor(const std::string& vsSource, const std::string& fsSource);
	virtual ~PostProcessor();

	DISALLOW_COPY_AND_ASSIGN(PostProcessor);

	virtual void Release() override;

	/** ������ ���۸� �����մϴ�. */
	virtual void Blit(class FrameBuffer* frameBuffer);

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

protected:
	/** ���ο��� ����ϴ� ������ �ִ� ũ���Դϴ�. */
	static const uint32_t MAX_VERTEX_SIZE = 6;

	/** ������ ������ ���ε� �����Դϴ�. */
	static const uint32_t FRAME_BUFFER_BIND_SLOT = 0;

	/** ��ũ�� ũ�⿡ �����ϴ� ���� �迭 ������Ʈ�Դϴ�. */
	uint32_t vertexArrayObject_ = 0;

	/** ��ũ�� ũ�⿡ �����ϴ� ���� �����Դϴ�. */
	class VertexBuffer* vertexBuffer_ = nullptr;
};