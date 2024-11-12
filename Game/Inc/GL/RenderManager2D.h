#pragma once

#include <array>
#include <map>
#include <queue>

#include <glm/glm.hpp>

#include "GL/GLManager.h"
#include "Utils/Macro.h"

/** Ŭ���� ���� ����. */
class Camera2D;
class FrameBuffer;
class ITexture;
class Shader;
class TextureAtlas2D;
class TTFont;
class UniformBuffer;
class VertexBuffer;

/** �ؽ�ó ������ �� �߰��� �� �ִ� �ɼ��Դϴ�. */
struct TextureDrawOption
{
	glm::vec3 blend = glm::vec3(0.0f, 0.0f, 0.0f); /** �ؽ�ó�Ϳ� ȥ���� ���� �Դϴ�. */
	float factor = 0.0f; /** �ؽ�ó�Ϳ� ȥ���� ������ �����Դϴ�. factor�� ���� 0�̶�� ������ ȥ�յ��� �ʽ��ϴ�. */
	float transparent = 1.0f; /** �ؽ�ó���� �����Դϴ�. 1.0 �̸� ������, 0.0 �̸� ���� �����Դϴ�. */
	bool bIsFlipH = false; /** �ؽ�ó�͸� ���η� ������ �� �����Դϴ�. */
	bool bIsFlipV = false; /** �ؽ�ó�͸� ���η� ������ �� �����Դϴ�. */
};

/** ������ ����� �Ǵ� ������ ������ �ɼ��Դϴ�. */
struct RenderTargetOption
{
	glm::vec4 clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f); /** ���� Ÿ�� ���� �ʱ�ȭ �� ������ �����Դϴ�. */
	bool bIsClearBuffer = true; /** ���� Ÿ�� ���� �ʱ�ȭ �����Դϴ�. */
};

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

	/** 2D ī�޶� �������� �������� ����/�����մϴ�. */
	void Begin(const Camera2D* camera2D);
	void Begin(const Camera2D* camera2D, FrameBuffer* renderTargetBuffer, const RenderTargetOption& option);
	void End();
	
	/**
	 * 2D ���� ���� (��, ��, �ﰢ��, �簢��, �� ���)�� �������մϴ�.
	 * �̶�, �޼��� �ڿ� Wireframe�̶�� ������ ���̾� ������ �������� �����մϴ�.
	 */
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
	void DrawEllipse(const glm::vec2& center, float xHalfAxis, float yHalfAxis, float rotate, const glm::vec4& color);
	void DrawEllipseWireframe(const glm::vec2& center, float xHalfAxis, float yHalfAxis, float rotate, const glm::vec4& color);
	
	/** 2D �ؽ�ó�� �������մϴ�. */
	void DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate);
	void DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor);
	void DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate, const TextureDrawOption& option);
	void DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor, const TextureDrawOption& option);

	/** 2D �ؽ�ó ��Ʋ���� ��Ҹ� �������մϴ�. */
	void DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate);
	void DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor);
	void DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate, const TextureDrawOption& option);
	void DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor, const TextureDrawOption& option);

	/** 2D ���ڿ��� �������մϴ�. */
	void DrawString(TTFont* font, const std::wstring& text, const glm::vec2& basePos, const glm::vec4& color);
	void DrawString(TTFont* font, const std::wstring& text, const glm::vec2& basePos, const glm::vec4& textColor, const glm::vec4& outlineColor);

private:
	/** IApp���� 2D ���� �Ŵ����� ���ο� ������ �� �ֵ��� ����. */
	friend class IApp;

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
		glm::vec4 color0;
		glm::vec4 color1;
		uint32_t unit; /** �ؽ�ó �����Դϴ�. */
		float transparent = 1.0f; /** �����Դϴ�. 1.0�� ������ �������ϰ� 0.0�� ������ �����մϴ�. */
	};

	/** 2D ���� �Ŵ��� ���ο��� ����� ������ ����Դϴ�. */
	struct RenderCommand
	{
		static const uint32_t MAX_TEXTURE_UNIT = 10;

		enum class EType
		{
			GEOMETRY   = 0x00,
			TEXTURE    = 0x01,
			TEXTURE_EX = 0x02,
			STRING     = 0x03,
			STRING_EX  = 0x04,
		};

		EDrawMode drawMode;
		uint32_t startVertexIndex;
		uint32_t vertexCount;
		EType type;
		ITexture* textures[MAX_TEXTURE_UNIT] = { nullptr, };
		TTFont* fonts[MAX_TEXTURE_UNIT] = { nullptr, };
	};
	
	/** ���̴� ���� �� ������ �ٲ�� ������ �����Դϴ�. */
	struct PerFrameUBO
	{
		static const uint32_t SHADER_BIND_SLOT = 0;
		glm::mat4 ortho;
	};

	/** ������ ���� ������ �����Դϴ�. */
	struct OriginGLContext
	{
		int32_t viewport[4];
		bool bEnableDepth;
		bool bEnableCull;
	};

	/** 2D ���� �Ŵ����� �ʱ�ȭ �� ������ IApp ���ο����� ����˴ϴ�. */
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
	VertexBuffer* vertexBuffer_ = nullptr;

	/** ���̴� ���� ���� ������ ������ �����Դϴ�. */
	UniformBuffer* uniformBuffer_ = nullptr;

	/** ���̴� ���� �� ������ �ٲ�� ������ ���� �����Դϴ�. */
	PerFrameUBO perFrameUBO_;

	/** ���� ������ �ִ� �����Դϴ�. */
	static const int32_t MAX_VERTEX_BUFFER_SIZE = 3000;

	/** ���� �����Դϴ�. */
	std::array<Vertex, MAX_VERTEX_BUFFER_SIZE> vertices_;

	/** 2D �������� ���۵Ǿ����� Ȯ���մϴ�. */
	bool bIsBegin_ = false;

	/** ������ ��� ������ �����Դϴ�. */
	FrameBuffer* renderTargetBuffer_ = nullptr;
	
	/** 2D ������ ���� ������ ���ؽ�Ʈ�Դϴ�. */
	OriginGLContext originContext_;
	
	/** 2D �������� �� ����� ���̴��Դϴ�. */
	std::map<RenderCommand::EType, Shader*> shaders_;

	/** 2D ������ ����� �����ϴ� Ŀ�ǵ� ť�Դϴ�. */
	std::queue<RenderCommand> commandQueue_;
};