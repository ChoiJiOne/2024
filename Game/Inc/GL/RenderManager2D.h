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
		enum class Type
		{
			GEOMETRY = 0x00,
		};

		DrawMode drawMode;
		uint32_t startVertexIndex;
		uint32_t vertexCount;
		Type type;
	};

	/** 2D 렌더 매니저의 초기화 및 해제는 GameApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** 2D 렌더 매니저의 싱글턴 객체입니다. */
	static RenderManager2D singleton_;

	/** 렌더 매니저 내부에서 사용할 GL 매니저입니다. */
	GLManager* glManager_ = nullptr;
};