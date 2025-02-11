#include <glad/glad.h>

#include "Assertion.h"
#include "MeshRenderer.h"
#include "RenderModule.h"
#include "TileMap.h"

MeshRenderer::MeshRenderer()
	: Shader("Resource/Shader/MeshRenderer.vert", "Resource/Shader/MeshRenderer.frag")
{
}

MeshRenderer::~MeshRenderer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MeshRenderer::Release()
{
	CHECK(bIsInitialized_);
	Shader::Release();
}

void MeshRenderer::DrawMesh(StaticMesh<VertexPositionNormalUv3D>* mesh, const Mat4x4& world, IResource* texture)
{
	TileMap* tileMap = reinterpret_cast<TileMap*>(texture);

	Shader::Bind();
	{
		tileMap->Active(0);

		Shader::SetUniform("world", world);
		Shader::SetUniform("view", view_);
		Shader::SetUniform("projection", projection_);

		mesh->Bind();
		RenderModule::ExecuteDrawIndex(mesh->GetIndexCount(), EDrawMode::Triangles);
		mesh->Unbind();
	}
	Shader::Unbind();
}