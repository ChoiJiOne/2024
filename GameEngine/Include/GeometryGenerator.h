#pragma once

#include <vector>

#include "Vertex.h"



/**
 * @brief 3D ���� ������ �����մϴ�.
 * 
 * @note �� Ŭ������ ��� ��� ������ �޼���� static�Դϴ�.
 */
class GeometryGenerator
{
public:
	/**
	 * @brief 3D ť�긦 �����մϴ�.
	 * 
	 * @param xsize X�� ���������� ũ���Դϴ�.
	 * @param ysize Y�� ���������� ũ���Դϴ�.
	 * @param zsize Z�� ���������� ũ���Դϴ�.
	 * @param outVertices ������ ť���� ���� ����Դϴ�.
	 * @param outIndices ������ ť���� �ε��� ����Դϴ�.
	 */
	static void CreateCube(float xsize, float ysize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};