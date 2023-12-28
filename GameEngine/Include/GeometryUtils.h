#pragma once

#include <vector>

#include "Vertex.h"


/**
 * @brief ���� ���� ���� Ȯ�� ����� �����մϴ�.
 * 
 * @note 
 * - �� Ŭ������ ��� ��� ������ �޼���� ��� static�Դϴ�.
 * - ���� ������ Cube/Sphere/Icosphere/Geosphere/Torus/Cone/Cylinder/Grid �Դϴ�.
 */
class GeometryUtils
{
public:
	/**
	 * @brief ��ǥ ���� ���ڸ� �����մϴ�.
	 * 
	 * @param minPosition ��ǥ ���� ������ �ּҰ��Դϴ�.
	 * @param maxPosition ��ǥ ���� ������ �ִ��Դϴ�.
	 * @param gap ������ �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 * @param outVertices ������ ��ǥ ���� ������ ���� �����Դϴ�.
	 * @param outIndices ������ ��ǥ ������ �ε��� �����Դϴ�.
	 * 
	 * @note 
	 * - X���� ������ RED, Y���� ������ GREEN, Z���� ������ BLUE�Դϴ�.
	 * - ������ �� GL_LINES �ɼ����� ���� �� �������ؾ� �մϴ�.
	 */
	static void CreateAxisGrid(
		const Vector3f& minPosition, 
		const Vector3f& maxPosition,
		const float& gap, 
		const Vector4f& color, 
		std::vector<VertexPositionColor>& outVertices,
		std::vector<uint32_t>& outIndices
	);
};