#include "MathModule.h"

#include "Assertion.h"
#include "GeometryGenerator.h"

void GeometryGenerator::CreateCube(const Vec3f& size, std::vector<VertexPositionNormalUv3D>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);

	static const uint32_t faceCount = 6;
	static const Vec3f faceNormals[faceCount] =
	{
		Vec3f(+0.0f, +0.0f, +1.0f),
		Vec3f(+0.0f, +0.0f, -1.0f),
		Vec3f(+1.0f, +0.0f, +0.0f),
		Vec3f(-1.0f, +0.0f, +0.0f),
		Vec3f(+0.0f, +1.0f, +0.0f),
		Vec3f(+0.0f, -1.0f, +0.0f),
	};

	static const Vec2f uvs[4] =
	{
		Vec2f(1.0f, 1.0f),
		Vec2f(1.0f, 0.0f),
		Vec2f(0.0f, 0.0f),
		Vec2f(0.0f, 1.0f),
	};

	Vec3f tsize = Vec3f(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

	for (uint32_t face = 0; face < faceCount; ++face)
	{
		const Vec3f& normal = faceNormals[face];
		Vec3f basis = (face >= 4) ? Vec3f(0.0f, 0.0f, 1.0f) : Vec3f(0.0f, 1.0f, 0.0f);

		Vec3f side1 = Vec3f::Cross(normal, basis);
		Vec3f side2 = Vec3f::Cross(normal, side1);

		const size_t vbase = outVertices.size();
		outIndices.push_back(vbase + 0);
		outIndices.push_back(vbase + 2);
		outIndices.push_back(vbase + 1);

		outIndices.push_back(vbase + 0);
		outIndices.push_back(vbase + 3);
		outIndices.push_back(vbase + 2);

		outVertices.push_back(VertexPositionNormalUv3D(((normal - side1 - side2) * tsize), normal, uvs[0]));
		outVertices.push_back(VertexPositionNormalUv3D(((normal - side1 + side2) * tsize), normal, uvs[1]));
		outVertices.push_back(VertexPositionNormalUv3D(((normal + side1 + side2) * tsize), normal, uvs[2]));
		outVertices.push_back(VertexPositionNormalUv3D(((normal + side1 - side2) * tsize), normal, uvs[3]));
	}
}

void GeometryGenerator::CreateSphere(float radius, uint32_t tessellation, std::vector<VertexPositionNormalUv3D>& outVertices, std::vector<uint32_t>& outIndices)
{
	CHECK(tessellation >= 3);

	outVertices.resize(0);
	outIndices.resize(0);

	const uint32_t verticalSegments = tessellation;
	const uint32_t horizontalSegments = tessellation * 2;

	for (uint32_t vertical = 0; vertical <= verticalSegments; ++vertical)
	{
		float v = 1.0f - static_cast<float>(vertical) / static_cast<float>(verticalSegments);
		float latitude = Pi * (static_cast<float>(vertical) / static_cast<float>(verticalSegments)) - PiDiv2;
		float dy = MathModule::Sin(latitude);
		float dxz = MathModule::Cos(latitude);

		for (uint32_t horizon = 0; horizon <= horizontalSegments; ++horizon)
		{
			float u = static_cast<float>(horizon) / static_cast<float>(horizontalSegments);
			float longitude = TwoPi * static_cast<float>(horizon) / static_cast<float>(horizontalSegments);
			float dx = dxz * MathModule::Sin(longitude);
			float dz = dxz * MathModule::Cos(longitude);

			Vec3f position(radius * dx, radius * dy, radius * dz);
			Vec3f normal(dx, dy, dz);
			Vec2f uv(u, 1.0f - v);

			outVertices.push_back(VertexPositionNormalUv3D(position, normal, uv));
		}
	}

	uint32_t stride = horizontalSegments + 1;
	for (uint32_t vertical = 0; vertical < verticalSegments; ++vertical)
	{
		for (uint32_t horizon = 0; horizon <= horizontalSegments; ++horizon)
		{
			outIndices.push_back((vertical + 0) * stride + (horizon + 0) % stride);
			outIndices.push_back((vertical + 0) * stride + (horizon + 1) % stride);
			outIndices.push_back((vertical + 1) * stride + (horizon + 0) % stride);

			outIndices.push_back((vertical + 0) * stride + (horizon + 1) % stride);
			outIndices.push_back((vertical + 1) * stride + (horizon + 1) % stride);
			outIndices.push_back((vertical + 1) * stride + (horizon + 0) % stride);
		}
	}
}