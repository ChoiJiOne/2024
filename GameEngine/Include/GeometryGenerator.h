#pragma once

#include <vector>

#include "Vertex.h"


/**
 * @brief 3D ���� ������ �����մϴ�.
 * 
 * @note �� Ŭ������ ��� ������ �޼���� ��� static �Դϴ�.
 */
class GeometryGenerator
{
public:
	/**
	 * @brief 3D ť���� ������ �ε��� ����� �����մϴ�.
	 * 
	 * @param size 3D ť���� X, Y, Z�� ���������� ũ���Դϴ�.
	 * @param outVertices ������ ť���� ���� ����Դϴ�.
	 * @param outIndices  ������ ť���� �ε��� ����Դϴ�.
	 */
	static void CreateCube(const Vector3f& size, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};