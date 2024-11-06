#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "GL/GLManager.h"
#include "Utils/Macro.h"

/**
 * 2D �������� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 * 2D ��ǥ���� ������ ī�޶� �߽����� ������ �����ϴ�.
 *     +y
 *     ��
 * ������������������x+
 *     ��
 */
class RenderManager2D
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager2D);

	/** 2D ���� �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static RenderManager2D& GetRef();

	/** 2D ���� �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static RenderManager2D* GetPtr();

	/** 2D ī�޶� �������� �������� �����մϴ�. */
	void Begin(const Camera2D* camera2D);

	/** 2D �������� �����մϴ�. */
	void End();

	/** 2D ���� ���� (��, ��, �ﰢ��, �簢��, �� ���)�� �������մϴ�. */
	void DrawPoint(const glm::vec2& point, const glm::vec4& color, float pointSize);
	void DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, const glm::vec4& color);
		
private:
	/** GameApp���� 2D ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class GameApp;

	/**
	 * 2D ���� �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	RenderManager2D() = default;
	virtual ~RenderManager2D() {}

	/** 2D ���� �Ŵ��� ���ο����� ����ϴ� �����Դϴ�. */
	struct Vertex
	{
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}
		
		glm::vec2 position;
		glm::vec2 uv;
		glm::vec4 color;
	};

	/** 2D ���� �Ŵ��� ���ο��� ����� ������ ����Դϴ�. */
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

	/** 2D ���� �Ŵ����� �ʱ�ȭ �� ������ GameApp ���ο����� ����˴ϴ�. */
	void Startup();
	void Shutdown();

	/** 2D ���� �Ŵ��� ������ ������Ƽ�� �ʱ�ȭ�մϴ�. */
	void LoadBuffers();
	void LoadShaders();

	/** 2D ���� �Ŵ��� ���� Ŀ��� ť�� ���õ� ��ɵ��Դϴ�. */
	void Flush();
	bool IsFullCommandQueue(uint32_t vertexCount);

private:
	/** 2D ���� �Ŵ����� �̱��� ��ü�Դϴ�. */
	static RenderManager2D singleton_;

	/** 2D ���� �Ŵ��� ���ο��� ����� GL �Ŵ����Դϴ�. */
	GLManager* glManager_ = nullptr;

	/** ���� Array ������Ʈ�Դϴ�. */
	uint32_t vertexArrayObject_ = 0;

	/** GPU ���� ���� �����Դϴ�. */
	class VertexBuffer* vertexBuffer_ = nullptr;

	/** ���̴� ���� ���� ������ ������ �����Դϴ�. */
	class UniformBuffer* uniformBuffer_ = nullptr;

	/** ���� ������ �ִ� �����Դϴ�. */
	static const int32_t MAX_VERTEX_BUFFER_SIZE = 30000;

	/** ���� �����Դϴ�. */
	std::array<Vertex, MAX_VERTEX_BUFFER_SIZE> vertices_;

	/** 2D �������� ���۵Ǿ����� Ȯ���մϴ�. */
	bool bIsBegin_ = false;

	/** 2D ������ ���� ������ ���� �׽�Ʈ Ȱ��ȭ �����Դϴ�. */
	bool originEnableDepth_ = false;

	/** 2D ������ ���� ������ �ø� �׽�Ʈ Ȱ��ȭ �����Դϴ�.  */
	bool originEnableCull_ = false;

	/** 2D �������� �� ����� ���̴��Դϴ�. */
	std::map<RenderCommand::EType, class Shader*> shaders_;

	/** 2D ������ ����� �����ϴ� Ŀ�ǵ� ť�Դϴ�. */
	std::queue<RenderCommand> commandQueue_;
};