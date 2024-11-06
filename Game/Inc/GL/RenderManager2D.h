#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "GL/GLManager.h"
#include "Utils/Macro.h"

/**
 * 2D 렌더링을 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 * 2D 좌표계의 기준은 카메라를 중심으로 다음과 같습니다.
 *     +y
 *     │
 * ────┼────x+
 *     │
 */
class RenderManager2D
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager2D);

	/** 2D 렌더 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static RenderManager2D& GetRef();

	/** 2D 렌더 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static RenderManager2D* GetPtr();

	/** 2D 카메라를 기준으로 렌더링을 시작합니다. */
	void Begin(const class Camera2D* camera2D);

	/** 2D 렌더링을 종료합니다. */
	void End();

	/** 2D 기하 도형 (점, 선, 삼각형, 사각형, 원 등등)을 렌더링합니다. */
	void DrawPoint(const glm::vec2& point, const glm::vec4& color, float pointSize);
	void DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, const glm::vec4& color);
	void DrawLine(const glm::vec2& startPos, const glm::vec4& startColor, const glm::vec2& endPos, const glm::vec4& endColor);
	void DrawTriangle(const glm::vec2& fromPos, const glm::vec2& byPos, const glm::vec2& toPos, const glm::vec4& color);
	void DrawTriangle(const glm::vec2& fromPos, const glm::vec4& fromColor, const glm::vec2& byPos, const glm::vec4& byColor, const glm::vec2& toPos, const glm::vec4& toColor);
	void DrawTriangleWireframe(const glm::vec2& fromPos, const glm::vec2& byPos, const glm::vec2& toPos, const glm::vec4& color);
	void DrawTriangleWireframe(const glm::vec2& fromPos, const glm::vec4& fromColor, const glm::vec2& byPos, const glm::vec4& byColor, const glm::vec2& toPos, const glm::vec4& toColor);
	void DrawRect(const glm::vec2& center, float w, float h, const glm::vec4& color, float rotate);
	void DrawRectWireframe(const glm::vec2& center, float w, float h, const glm::vec4& color, float rotate);
	void DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color);
	void DrawCircleWireframe(const glm::vec2& center, float radius, const glm::vec4& color);
		
private:
	/** GameApp에서 2D 렌더 매니저의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 2D 렌더 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	RenderManager2D() = default;
	virtual ~RenderManager2D() {}

	/** 2D 렌더 매니저 내부에서만 사용하는 정점입니다. */
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

	/** 2D 렌더 매니저 내부에서 사용할 렌더링 명령입니다. */
	struct RenderCommand
	{
		enum class EType
		{
			GEOMETRY = 0x00,
		};

		EDrawMode drawMode;
		uint32_t startVertexIndex;
		uint32_t vertexCount;
		EType type;
	};
	
	/** 셰이더 상의 매 프레임 바뀌는 유니폼 버퍼입니다. */
	struct PerFrameUBO
	{
		static const uint32_t SHADER_BIND_SLOT = 0;
		glm::mat4 ortho;
	};

	/** 2D 렌더 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

	/** 2D 렌더 매니저 내부의 프로퍼티를 초기화합니다. */
	void LoadBuffers();
	void LoadShaders();

	/** 2D 렌더 매니저 내의 커멘드 큐와 관련된 기능들입니다. */
	void Flush();
	bool IsFullCommandQueue(uint32_t vertexCount);

private:
	/** 2D 렌더 매니저의 싱글턴 객체입니다. */
	static RenderManager2D singleton_;

	/** 2D 렌더 매니저 내부에서 사용할 GL 매니저입니다. */
	GLManager* glManager_ = nullptr;

	/** 정점 Array 오브젝트입니다. */
	uint32_t vertexArrayObject_ = 0;

	/** GPU 상의 정점 버퍼입니다. */
	class VertexBuffer* vertexBuffer_ = nullptr;

	/** 셰이더 끼리 공유 가능한 유니폼 버퍼입니다. */
	class UniformBuffer* uniformBuffer_ = nullptr;

	/** 셰이더 상의 매 프레임 바뀌는 유니폼 버퍼 원본입니다. */
	PerFrameUBO perFrameUBO_;

	/** 정점 버퍼의 최대 개수입니다. */
	static const int32_t MAX_VERTEX_BUFFER_SIZE = 30000;

	/** 정점 버퍼입니다. */
	std::array<Vertex, MAX_VERTEX_BUFFER_SIZE> vertices_;

	/** 2D 렌더링이 시작되었는지 확인합니다. */
	bool bIsBegin_ = false;

	/** 2D 렌더링 시작 이전의 깊이 테스트 활성화 여부입니다. */
	bool originEnableDepth_ = false;

	/** 2D 렌더링 시작 이전의 컬링 테스트 활성화 여부입니다.  */
	bool originEnableCull_ = false;

	/** 2D 렌더링할 때 사용할 셰이더입니다. */
	std::map<RenderCommand::EType, class Shader*> shaders_;

	/** 2D 렌더링 명령을 저장하는 커맨드 큐입니다. */
	std::queue<RenderCommand> commandQueue_;
};