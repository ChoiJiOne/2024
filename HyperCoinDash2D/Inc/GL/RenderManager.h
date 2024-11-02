#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "Macro.h"

/**
 * 2D 렌더링을 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class RenderManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager);

	/** 렌더 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static RenderManager& GetRef();

	/** 렌더 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static RenderManager* GetPtr();

private:
	/** GameApp에서 렌더 매니저의 내부에 접근할 수 있도록 설정. */
	friend class GameApp;

	/**
	 * 렌더 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	RenderManager() = default;
	virtual ~RenderManager() {}

	/** 렌더 매니저 내부에서만 사용하는 버텍스입니다. */
	struct Vertex
	{
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}

		glm::vec2 position;
		glm::vec2 uv;
		glm::vec4 color;
		uint32_t unit; /** 텍스처 유닛입니다. */
		float transparent = 1.0f; /** 렌더링할 대상의 투명도입니다. 1.0에 가까울수록 불투명합니다. */
	};

	/**
	 * 렌더 매니저 내부에서만 사용하는 그리기 모드입니다.
	 * 참조: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
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

	/** 렌더 매니저 내부에서만 사용하면 그리기 명령입니다. */
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

	/** 렌더 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** 렌더 매니저의 싱글턴 객체입니다. */
	static RenderManager singleton_;

	/** 렌더 매니저 내부에서 사용할 GL 매니저입니다. */
	class GLManager* glManager_ = nullptr;

	/** 렌더 매니저의 렌더링이 시작되었는지 확인합니다. */
	bool bIsBegin_ = false;

	/** CPU 상의 버텍스 버퍼입니다. */
	static const int32_t MAX_VERTEX_BUFFER_SIZE = 30000;
	std::array<Vertex, MAX_VERTEX_BUFFER_SIZE> vertices_;

	/** 버텍스 Array 오브젝트입니다. */
	uint32_t vertexArrayObject_ = 0;

	/** GPU 상의 버텍스 버퍼입니다. */
	class VertexBuffer* vertexBuffer_ = nullptr;

	/** 렌더 커맨드 큐입니다. */
	std::queue<RenderCommand> commandQueue_;

	/** 렌더링 시작 전의 깊이 테스트 상태 여부입니다. */
	bool originEnableDepth_ = false;
};