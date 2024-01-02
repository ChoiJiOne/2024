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


	/**
	 * @brief 3D ���� ������ �ε��� ����� �����մϴ�.
	 * 
	 * @param radius 3D ���� ������ �����Դϴ�.
	 * @param tessellation 3D ���� ���� Ƚ���Դϴ�. ũ��� 3�̻��̿��� �մϴ�.
	 * @param outVertices ������ ���� ���� ����Դϴ�.
	 * @param outIndices  ������ ���� �ε��� ����Դϴ�.
	 */
	static void CreateSphere(float radius, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief 3D ������� ������ �ε��� ����� �����մϴ�.
	 *
	 * @param radius 3D ������� ������ �����Դϴ�.
	 * @param height 3D ������� �����Դϴ�.
	 * @param tessellation 3D ������� ���� Ƚ���Դϴ�. ũ��� 3�̻��̿��� �մϴ�.
	 * @param outVertices ������ ������� ���� ����Դϴ�.
	 * @param outIndices  ������ ������� �ε��� ����Դϴ�.
	 */
	static void CreateCylinder(float radius, float height, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief 3D ������ ������ �ε��� ����� �����մϴ�.
	 * 
	 * @param radius 3D ������ ������ �����Դϴ�.
	 * @param height 3D ������ �����Դϴ�.
	 * @param tessellation 3D ������ ���� Ƚ���Դϴ�. ũ��� 3�̻��̿��� �մϴ�.
	 * @param outVertices ������ ������ ���� ����Դϴ�.
	 * @param outIndices  ������ ������ �ε��� ����Դϴ�.
	 */
	static void CreateCone(float radius, float height, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


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
	 * @brief 3D ����� ���/�ϴ��� ������ �ε��� ����� �����մϴ�.
	 * 
	 * @param radius 3D ������� ������ �����Դϴ�.
	 * @param height 3D ������� �����Դϴ�.
	 * @param tessellation 3D ������� ���� Ƚ���Դϴ�. ũ��� 3�̻��̿��� �մϴ�.
	 * @param bIsTop ������� �ϴ����� Ȯ���մϴ�.
	 * @param outVertices ������ ����� ���/�ϴ��� ���� ����Դϴ�.
	 * @param outIndices  ������ ����� ���/�ϴ��� �ε��� ����Դϴ�.
	 */
	static void CreateCylinderCap(float radius, float height, uint32_t tessellation, bool bIsTop, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief ������ ���� ���Ϳ� �ֺ��͸� ����մϴ�.
	 *
	 * @param outVertices ���� ���Ϳ� �ֺ��͸� ����� ���� ����Դϴ�.
	 * @param outIndices ���� ���Ϳ� �ֺ��͸� ����� �ε��� ����Դϴ�.
	 */
	static void ComputeTangent(std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};