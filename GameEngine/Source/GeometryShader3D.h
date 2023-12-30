#pragma once

#include <array>
#include <vector>

#include "Shader.h"


/**
 * @brief 3D �⺻ ������ �������ϴ� ���̴��Դϴ�.
 */
class GeometryShader3D : public Shader
{
public:
	/**
	 * @brief 3D �⺻ ������ �������ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	GeometryShader3D() = default;


	/**
	 * @brief 3D �⺻ ������ �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GeometryShader3D();


	/**
	 * @brief 3D �⺻ ������ �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryShader3D);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 */
	virtual void Initialize(const std::wstring & vsPath, const std::wstring & fsPath) override;


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ȭ�鿡 3D ������ �׸��ϴ�.
	 * 
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param positions ȭ�� ���� 3D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 * 
	 * @note 3D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 */
	void DrawPoints3D(const Matrix4x4f& view, const Matrix4x4f& projection, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 3D ��ǥ ������ �׸��ϴ�.
	 * 
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param minPosition ��ǥ ������ �ּҰ��Դϴ�.
	 * @param maxPosition ��ǥ ������ �ִ밪�Դϴ�.
	 * @param gap ���� �� �����Դϴ�.
	 * @param color X,Y,Z �� �̿��� ���� �����Դϴ�.
	 *
	 * @note X���� ������ Red, Y���� ������ Green, Z���� ������ Blue�Դϴ�.
	 */
	void DrawAxisGrid3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& minPosition, const Vector3f& maxPosition, float gap, const Vector4f& color);

	
private:
	/**
	 * @brief 3D �⺻ ���� �׸��⸦ �����ϴ� ���̴� ���ο��� ����ϴ� �����Դϴ�.
	 */
	struct VertexPositionColor
	{
		/**
		 * @brief ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
		 */
		VertexPositionColor() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f) {}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param position ������ ��ġ�Դϴ�.
		 * @param color ������ �����Դϴ�.
		 */
		VertexPositionColor(Vector3f&& position, Vector4f&& color) noexcept
			: position(position)
			, color(color) {}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param position ������ ��ġ�Դϴ�.
		 * @param color ������ �����Դϴ�.
		 */
		VertexPositionColor(const Vector3f& position, const Vector4f& color) noexcept
			: position(position)
			, color(color) {}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param x ��ġ�� X��ǥ�Դϴ�.
		 * @param y ��ġ�� Y��ǥ�Դϴ�.
		 * @param z ��ġ�� Z��ǥ�Դϴ�.
		 * @param r ���� ������ R�Դϴ�.
		 * @param g ���� ������ G�Դϴ�.
		 * @param b ���� ������ B�Դϴ�.
		 * @param a ���� ������ A�Դϴ�.
		 */
		VertexPositionColor(
			float x, float y, float z,
			float r, float g, float b, float a
		) noexcept
			: position(x, y, z)
			, color(r, g, b, a) {}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionColor(VertexPositionColor&& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 */
		VertexPositionColor(const VertexPositionColor& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		VertexPositionColor& operator=(VertexPositionColor&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			color = instance.color;

			return *this;
		}


		/**
		 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
		 *
		 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
		 *
		 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
		 */
		VertexPositionColor& operator=(const VertexPositionColor& instance) noexcept
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
			return sizeof(VertexPositionColor);
		}


		/**
		 * @brief ������ ��ġ�Դϴ�.
		 */
		Vector3f position;


		/**
		 * @brief ������ �����Դϴ�.
		 */
		Vector4f color;
	};


private:
	/**
	 * @brief ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief ������ ���� ����Դϴ�.
	 */
	std::array<VertexPositionColor, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief ���� ������ ������Ʈ�Դϴ�.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;
};