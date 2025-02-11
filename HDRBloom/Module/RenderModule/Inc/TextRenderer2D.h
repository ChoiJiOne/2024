#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex2D.h"
#include "VertexBuffer.h"

class TTFont;


/**
 * @brief �۸����� �̿��ؼ� �ؽ�Ʈ�� �������ϴ� ���̴��Դϴ�.
 *
 * @note
 * - 2D �ؽ�Ʈ ������ �� ������ �Ǵ� ��ǥ��� ������ ��ǥ���Դϴ�.
 */
class TextRenderer2D : public Shader
{
public:
	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� ���̴��� �������Դϴ�.
	 */
	explicit TextRenderer2D();


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~TextRenderer2D();


	/**
	 * @brief 2D �ؽ�Ʈ�� �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TextRenderer2D);


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� ���� ����� �����մϴ�.
	 *
	 * @param ortho ������ ���� ���� ����Դϴ�.
	 */
	void SetOrtho(const Mat4x4& ortho) { ortho_ = ortho; }


	/**
	 * @brief 2D �ؽ�Ʈ�� �׸��ϴ�.
	 * 
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param position �ؽ�Ʈ�� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void DrawText2D(const TTFont* font, const std::wstring& text, const Vec2f& position, const Vec4f& color);


private:
	/**
	 * @brief �ؽ�Ʈ�� �°� ���ؽ� ���۸� ������Ʈ�մϴ�.
	 *
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param startPosition �ؽ�Ʈ ������ ���� ��� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� �����Դϴ�.
	 *
	 * @return �ؽ�Ʈ�� �´� ���ؽ��� ���� ��ȯ�մϴ�.
	 */
	uint32_t UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vec2f& startPosition, const Vec4f& color);


private:
	/**
	 * @brief �ִ� ���ڿ��� �����Դϴ�.
	 */
	static const int32_t MAX_STRING_LEN = 1000;


	/**
	 * @brief �۸��� ���� ����� �ִ� ũ���Դϴ�.
	 *
	 * @note
	 * - ���� �ϳ� �׸��� �� �ʿ��� ������ �� : 6��
	 * - ����, �ִ� ���ڿ��� ���̰� 1000�̶��, �ʿ��� ������ �� : 6 X 1000 = 6000��
	 * - ��, �� �۸��� ���̴��� �����ϴ� �ִ� ���ڿ��� ���̴� 1000�̴�.
	 */
	static const int32_t MAX_VERTEX_SIZE = MAX_STRING_LEN * 6;


	/**
	 * @brief ���� ����Դϴ�.
	 */
	std::array<VertexPositionUvColor2D, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ���̴� ������ ����� ���� �����Դϴ�.
	 */
	VertexBuffer vertexBuffer_;


	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	Mat4x4 ortho_;
};