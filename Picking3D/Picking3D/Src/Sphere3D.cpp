#include "GeometryGenerator.h"
#include "RenderModule.h"

#include "Sphere3D.h"

Sphere3D::Sphere3D()
{
	static StaticMesh<VertexPositionNormalUv3D>* mesh = nullptr;
	if (!mesh)
	{
		std::vector<VertexPositionNormalUv3D> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);

		mesh = RenderModule::CreateResource<StaticMesh<VertexPositionNormalUv3D>>(vertices, indices);
	}

	static Checkboard* material = nullptr;
	if (!material)
	{
		material = RenderModule::CreateResource<Checkboard>(Checkboard::ESize::Size_1024x1024, Checkboard::ESize::Size_64x64, Vec4f(1.0f, 1.0f, 1.0f, 1.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	}

	mesh_ = mesh;
	material_ = material;
	bound_ = Sphere(transform_.position, 1.0f);
}

Sphere3D::~Sphere3D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Sphere3D::Tick(float deltaSeconds)
{
	bound_.center = transform_.position;
}

void Sphere3D::Release()
{
	if (bIsInitialized_)
	{
		bIsInitialized_ = false;
	}
}