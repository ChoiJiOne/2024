#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "Macro.h"

/**
 * 2D �������� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class RenderManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager);

	/** ���� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static RenderManager& GetRef();

	/** ���� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static RenderManager* GetPtr();

private:
	/** GameApp���� ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * ���� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	RenderManager() = default;
	virtual ~RenderManager() {}

	/** ���� �Ŵ��� ���ο����� ����ϴ� ���ؽ��Դϴ�. */
	struct Vertex
	{
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}

		glm::vec2 position;
		glm::vec2 uv;
		glm::vec4 color;
		uint32_t unit; /** �ؽ�ó �����Դϴ�. */
		float transparent = 1.0f; /** �������� ����� �����Դϴ�. 1.0�� �������� �������մϴ�. */
	};

	/**
	 * ���� �Ŵ��� ���ο����� ����ϴ� �׸��� ����Դϴ�.
	 * ����: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
	 */
	enum class DrawMode : int32_t
	{
		POINTS       = 0x0000,
		LINES        = 0x0001,
		LINE_STRIP   = 0x0003,
		TRIANGLES    = 0x0004,
		TRIANGLE_FAN = 0x0006,
		NONE         = 0xFFFF,
	};

	/** ���� �Ŵ��� ���ο����� ����ϸ� �׸��� ����Դϴ�. */
	struct RenderCommand
	{
		enum class EType
		{
			GEOMETRY = 0x00,
		};

		DrawMode drawMode;
		uint32_t startVertexIndex;
		uint32_t vertexCount;
		EType type;
	};

	/** ���� �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

private:
	/** ���� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static RenderManager singleton_;

	/** ���� �Ŵ��� ���ο��� ����� GL �Ŵ����Դϴ�. */
	class GLManager* glManager_ = nullptr;

	/** ���� �Ŵ����� �������� ���۵Ǿ����� Ȯ���մϴ�. */
	bool bIsBegin_ = false;

	/** CPU ���� ���ؽ� �����Դϴ�. */
	static const int32_t MAX_VERTEX_BUFFER_SIZE = 30000;
	std::array<Vertex, MAX_VERTEX_BUFFER_SIZE> vertices_;

	/** ���ؽ� Array ������Ʈ�Դϴ�. */
	uint32_t vertexArrayObject_ = 0;

	/** GPU ���� ���ؽ� �����Դϴ�. */
	class VertexBuffer* vertexBuffer_ = nullptr;

	/** ���� Ŀ�ǵ� ť�Դϴ�. */
	std::queue<RenderCommand> commandQueue_;

	/** ������ ���� ���� ���� �׽�Ʈ ���� �����Դϴ�. */
	bool originEnableDepth_ = false;
};