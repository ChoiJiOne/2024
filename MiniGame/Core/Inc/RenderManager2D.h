#pragma once

#include <array>
#include <map>
#include <queue>

#include "GameMath.h"
#include "IResource.h"
#include "RenderStateManager.h"

class Atlas2D;
class Camera2D;
class IEntity2D;
class ITexture;
class ResourceManager;
class Shader;
class TTFont;
class VertexBuffer;

/**
 * - 2D ���� �Ŵ����� �̱����Դϴ�.
 * - 2D ��ǥ���� ������ ī�޶� �߽����� ������ �����ϴ�.
 *     +y
 *     ��
 * ������������������x+
 *     ��
 */
class RenderManager2D
{
public:
	struct SpriteRenderOptions
	{
		Vec3f blend = Vec3f(0.0f, 0.0f, 0.0f); /** ��������Ʈ�� ȥ���� ���� �Դϴ�. */
		float factor = 0.0f; /** ��������Ʈ�� ȥ���� ������ �����Դϴ�. factor�� ���� 0�̶�� ������ ȥ�յ��� �ʽ��ϴ�. */
		float transparent = 1.0f; /** ��������Ʈ�� �����Դϴ�. 1.0 �̸� ������, 0.0 �̸� ���� �����Դϴ�. */
		bool bIsFlipH = false; /** ��������Ʈ�� ���η� ������ �� �����Դϴ�. */
		bool bIsFlipV = false; /** ��������Ʈ�� ���η� ������ �� �����Դϴ�. */
	};

public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager2D);

	static RenderManager2D& GetRef();
	static RenderManager2D* GetPtr();

	void Begin(const Camera2D* camera2D);
	void End();

	void DrawPoint(const Vec2f& point, const Vec4f& color, float pointSize);
	void DrawLine(const Vec2f& startPos, const Vec2f& endPos, const Vec4f& color);
	void DrawLine(const Vec2f& startPos, const Vec4f& startColor, const Vec2f& endPos, const Vec4f& endColor);
	void DrawTriangle(const Vec2f& fromPos, const Vec2f& byPos, const Vec2f& toPos, const Vec4f& color);
	void DrawTriangle(const Vec2f& fromPos, const Vec4f& fromColor, const Vec2f& byPos, const Vec4f& byColor, const Vec2f& toPos, const Vec4f& toColor);
	void DrawTriangleWireframe(const Vec2f& fromPos, const Vec2f& byPos, const Vec2f& toPos, const Vec4f& color);
	void DrawTriangleWireframe(const Vec2f& fromPos, const Vec4f& fromColor, const Vec2f& byPos, const Vec4f& byColor, const Vec2f& toPos, const Vec4f& toColor);
	void DrawRect(const Vec2f& center, float w, float h, const Vec4f& color, float rotate);
	void DrawRectWireframe(const Vec2f& center, float w, float h, const Vec4f& color, float rotate);
	void DrawRoundRect(const Vec2f& center, float w, float h, float side, const Vec4f& color, float rotate);
	void DrawRoundRectWireframe(const Vec2f& center, float w, float h, float side, const Vec4f& color, float rotate);
	void DrawCircle(const Vec2f& center, float radius, const Vec4f& color);
	void DrawCircleWireframe(const Vec2f& center, float radius, const Vec4f& color);

	void DrawSprite(ITexture* texture, const Vec2f& center, float w, float h, float rotate, const SpriteRenderOptions& options);
	void DrawSprite(Atlas2D* atlas, const std::string& name, const Vec2f& center, float w, float h, float rotate, const SpriteRenderOptions& options);
	
	void DrawString(TTFont* font, const std::wstring& text, const Vec2f& pos, const Vec4f& color);

private:
	friend class IApp;

	RenderManager2D() = default;
	virtual ~RenderManager2D() {}

	struct Vertex
	{
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}

		Vec2f position;
		Vec2f uv;
		Vec4f color;
		uint32_t unit; /** �ؽ�ó �����Դϴ�. */
		float transparent = 1.0f;
	};

	struct RenderCommand
	{
		static const uint32_t MAX_TEXTURE_UNIT = 10;

		enum class Type
		{
			GEOMETRY = 0x00,
			STRING   = 0x01,
			SPRITE   = 0x02,
		};

		DrawMode drawMode;
		uint32_t startVertexIndex;
		uint32_t vertexCount;
		Type type;
		ITexture* texture[MAX_TEXTURE_UNIT] = { nullptr, };
		TTFont* font[MAX_TEXTURE_UNIT] = { nullptr, };
	};

	void Startup(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */
	void Shutdown(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */

	void Flush();
	bool IsFullCommandQueue(uint32_t vertexCount);

private:
	static RenderManager2D instance_;

	RenderStateManager* renderStateMgr_ = nullptr;
	ResourceManager* resourceMgr_ = nullptr;

	bool bIsBegin_ = false;

	static const int32_t MAX_VERTEX_BUFFER_SIZE = 30000;
	std::array<Vertex, MAX_VERTEX_BUFFER_SIZE> vertices_;

	uint32_t vertexArrayObject_ = 0;
	VertexBuffer* vertexBuffer_ = nullptr;

	std::map<RenderCommand::Type, Shader*> shaders_;
	std::queue<RenderCommand> commandQueue_;

	bool originEnableDepth_ = false;
	bool originEnableCull_ = false;
};