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


	/**
	 * @brief 3D ���� �����մϴ�.
	 * 
	 * @param radius ���� ������ �����Դϴ�.
	 * @param sliceCount ���� Y��� ������ �������� �ڸ� Ƚ���Դϴ�.
	 * @param stackCount ���� XZ���� ������ �������� �ڸ� Ƚ���Դϴ�.
	 * @param outVertices ������ ���� ���� ����Դϴ�.
	 * @param outIndices ������ ���� �ε��� ����Դϴ�.	 
	 */
	static void CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief 3D ������� �����մϴ�.
	 * 
	 * @param radius ������� ������ ���Դϴ�.
	 * @param height ������� �����Դϴ�.
	 * @param sliceCount ������� Y��� ������ �������� �ڸ� Ƚ���Դϴ�.
	 * @param stackCount ������� XZ���� ������ �������� �ڸ� Ƚ���Դϴ�.
	 * @param outVertices ������ ������� ���� ����Դϴ�.
	 * @param outIndices ������ ������� �ε��� ����Դϴ�.
	 */
	static void CreateCylinder(float radius, float height, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief XY ����� ���带 �����մϴ�.
	 * 
	 * @param xsize ������ X�� ���������� ũ���Դϴ�.
	 * @param ysize ������ y�� ���������� ũ���Դϴ�.
	 * @param outVertices ������ ������ ���� ����Դϴ�.
	 * @param outIndices ������ ������ �ε��� ����Դϴ�.
	 */
	static void CreateXYQuad(float xsize, float ysize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief YZ ����� ���带 �����մϴ�.
	 * 
	 * @param ysize ������ Y�� ���������� ũ���Դϴ�.
	 * @param zsize ������ Z�� ���������� ũ���Դϴ�.
	 * @param outVertices ������ ������ ���� ����Դϴ�.
	 * @param outIndices ������ ������ �ε��� ����Դϴ�.
	 */
	static void CreateYZQuad(float ysize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief XZ ����� ���带 �����մϴ�.
	 * 
	 * @param xsize ������ X�� ���������� ũ���Դϴ�.
	 * @param zsize ������ Z�� ���������� ũ���Դϴ�.
	 * @param outVertices ������ ������ ���� ����Դϴ�.
	 * @param outIndices ������ ������ �ε��� ����Դϴ�.
	 */
	static void CreateXZQuad(float xsize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


private:
	/**
	 * @brief ������ ���� ���Ϳ� �ֺ��͸� ����մϴ�.
	 * 
	 * @param outVertices ���� ���Ϳ� �ֺ��͸� ����� ���� ����Դϴ�.
	 * @param outIndices ���� ���Ϳ� �ֺ��͸� ����� �ε��� ����Դϴ�.
	 */
	static void ComputeTangent(std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};