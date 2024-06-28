#pragma once

#include <array>

#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;


/**
 * @brief 3D �������� �����ϴ� �������Դϴ�.
 */
class Renderer3D : public IResource
{
public:
	/**
	 * @brief 3D �������� �����ϴ� �������� ����Ʈ �������Դϴ�.
	 */
	explicit Renderer3D();


	/**
	 * @brief 3D �������� �����ϴ� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Renderer3D();


	/**
	 * @brief 3D �������� �����ϴ� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Renderer3D);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief 3D �������� �������� �����մϴ�.
	 * 
	 * @param view ������ �� ����Դϴ�.
	 * @param projection ������ ���� ����Դϴ�.
	 */
	void Begin(const Mat4x4& view, const Mat4x4& projection);


	/**
	 * @brief 3D �������� �������� �����մϴ�.
	 */
	void End();

	
	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param positions ���� �迭 �������Դϴ�.
	 * @param size ���� �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 *
	 * @note 3D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawPoint(const Vec3f* positions, uint32_t size, const Vec4f& color, float pointSize = 1.0f);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param positions ���� �迭 �������Դϴ�.
	 * @param colors ���� �迭 �������Դϴ�. �̶�, ���� ������ ���� ���ƾ� �մϴ�.
	 * @param size ���� �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 *
	 * @note 3D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawPoint(const Vec3f* positions, const Vec4f* colors, uint32_t size, float pointSize = 1.0f);


	/**
	 * @brief 3D ������ ������ ���� �׸��ϴ�.
	 *
	 * @param positions ���� �迭 �������Դϴ�.
	 * @param colors ���� �迭 �������Դϴ�. �̶�, ���� ������ ���� ���ƾ� �մϴ�.
	 * @param size ���� �����Դϴ�.
	 *
	 * @note 3D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawLine(const Vec3f* positions, const Vec4f* colors, uint32_t size);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param startPos ���� �������Դϴ�.
	 * @param endPos ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLine(const Vec3f& startPos, const Vec3f& endPos, const Vec4f& color);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param startPos ���� �������Դϴ�.
	 * @param startColor ���� ������ �����Դϴ�.
	 * @param endPos ���� �����Դϴ�.
	 * @param endColor ���� ���� �����Դϴ�.
	 */
	void DrawLine(const Vec3f& startPos, const Vec4f& startColor, const Vec3f& endPos, const Vec4f& endColor);


	/**
	 * @brief 3D ������ �׸��ϴ�.
	 *
	 * @param positions ������� ���� ���� �� ���� ����Դϴ�.
	 * @param size ������� ���� ���� �� ���� ����� ���Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawLines(const Vec3f* positions, uint32_t size, const Vec4f& color);


	/**
	 * @brief 3D ���带 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param color ������ �����Դϴ�.
	 *
	 * @note 3D ����� XY��� �����Դϴ�.
	 */
	void DrawQuad(const Mat4x4& world, float width, float height, const Vec4f& color);


	/**
	 * @brief 3D ť�긦 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param extents ť���� X/Y/Z �� ���������� ũ���Դϴ�.
	 * @param color ť���� �����Դϴ�.
	 */
	void DrawCube(const Mat4x4& world, const Vec3f& extents, const Vec4f& color);


	/**
	 * @brief 3D ���� �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void DrawSphere(const Mat4x4& world, float radius, const Vec4f& color);


	/**
	 * @brief 3D �þ� ����ü�� �׸��ϴ�.
	 * 
	 * @param view �þ� ����ü�� �þ� ����Դϴ�.
	 * @param projection �þ� ����ü�� ���� ����Դϴ�.
	 * @param color �þ� ����ü�� �����Դϴ�.
	 */
	void DrawViewfrustum(const Mat4x4& view, const Mat4x4& projection, const Vec4f& color);


	/**
	 * @brief ���ڸ� �׸��ϴ�.
	 *
	 * @param extensions ������ XYZ ���� ũ���Դϴ�.
	 * @param stride ������ �����Դϴ�.
	 */
	void DrawGrid(const Vec3f& extensions, float stride);


private:
	/**
	 * @brief 3D ���� ������ �������ϴ� ������ ���ο��� ����ϴ� �����Դϴ�.
	 */
	struct Vertex
	{
		/**
		 * @brief ������ �⺻ �������Դϴ�.
		 */
		Vertex() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		Vertex(Vec3f&& p, Vec4f&& c) noexcept
			: position(p)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param p ������ ��ġ�Դϴ�.
		 * @param c ������ �����Դϴ�.
		 */
		Vertex(const Vec3f& p, const Vec4f& c) noexcept
			: position(p)
			, color(c) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param z ��ġ�� Z��ǥ�Դϴ�.
		 * @param r ���� ������ R�Դϴ�.
		 * @param g ���� ������ G�Դϴ�.
		 * @param b ���� ������ B�Դϴ�.
		 * @param a ���� ������ A�Դϴ�.
		 */
		Vertex(
			float x, float y, float z,
			float r, float g, float b, float a
		) noexcept
			: position(x, y, z)
			, color(r, g, b, a) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		Vertex(const Vertex& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		Vertex& operator=(Vertex&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			color = instance.color;

			return *this;
		}


		/**
		 * @brief ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		Vertex& operator=(const Vertex& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			color = instance.color;

			return *this;
		}


		/**
		 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
		 *
		 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
		 */
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}


		/**
		 * @brief ������ ��ġ�Դϴ�.
		 */
		Vec3f position;


		/**
		 * @brief ������ �����Դϴ�.
		 */
		Vec4f color;
	};


private:
	/**
	 * @brief �׸��⸦ �����մϴ�.
	 *
	 * @parma world ���� ����Դϴ�.
	 * @param drawMode �׸��� Ÿ���Դϴ�.
	 * @param vertexCount ���� ���Դϴ�.
	 */
	void Draw(const Mat4x4& world, const EDrawMode& drawMode, uint32_t vertexCount);


private:
	/**
	 * @brief ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief � ��� �� �ִ� ���� Ƚ���Դϴ�.
	 */
	static const int32_t MAX_SLICE_SIZE = 7;


	/**
	 * @brief ������ ���� ����Դϴ�.
	 */
	std::array<Vertex, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief �������� ���۵Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsBegin_ = false;


	/**
	 * @brief ���� ũ���Դϴ�.
	 */
	float pointSize_ = 1.0f;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ���� �����Դϴ�.
	 */
	VertexBuffer* vertexBuffer_;


	/**
	 * @brief ������ �� ����� ���̴��Դϴ�.
	 */
	Shader* shader_ = nullptr;
	

	/**
	 * @brief ������ ���� ���� Ȱ��ȭ �����Դϴ�.
	 */
	bool bIsBeforeEnableDepth_ = true;
};