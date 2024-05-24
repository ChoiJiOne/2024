#include <glad/glad.h>

#include "GLAssertion.h"
#include "RenderModule.h"
#include "SkinnedMesh.h"

SkinnedMesh::SkinnedMesh(const std::vector<VertexPositionNormalUvSkin3D>& vertices, const std::vector<uint32_t>& indices)
	: vertices_(vertices)
	, indices_(indices)
{
	vertexBuffer_ = RenderModule::CreateResource<VertexBuffer>(vertices_.data(), static_cast<uint32_t>(vertices_.size()) * VertexPositionNormalUvSkin3D::GetStride(), VertexBuffer::EUsage::Static);
	indexBuffer_ = RenderModule::CreateResource<IndexBuffer>(indices_.data(), static_cast<uint32_t>(indices_.size()));

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_->Bind();
		indexBuffer_->Bind();

		GL_FAILED(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionNormalUvSkin3D::GetStride(), (void*)(offsetof(VertexPositionNormalUvSkin3D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));

		GL_FAILED(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexPositionNormalUvSkin3D::GetStride(), (void*)(offsetof(VertexPositionNormalUvSkin3D, normal))));
		GL_FAILED(glEnableVertexAttribArray(1));

		GL_FAILED(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexPositionNormalUvSkin3D::GetStride(), (void*)(offsetof(VertexPositionNormalUvSkin3D, uv))));
		GL_FAILED(glEnableVertexAttribArray(2));

		GL_FAILED(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, VertexPositionNormalUvSkin3D::GetStride(), (void*)(offsetof(VertexPositionNormalUvSkin3D, weight))));
		GL_FAILED(glEnableVertexAttribArray(3));

		GL_FAILED(glVertexAttribIPointer(4, 4, GL_INT, VertexPositionNormalUvSkin3D::GetStride(), (void*)(offsetof(VertexPositionNormalUvSkin3D, joints))));
		GL_FAILED(glEnableVertexAttribArray(4));

		vertexBuffer_->Unbind();
	}
	GL_FAILED(glBindVertexArray(0));

	bIsInitialized_ = true;
}

SkinnedMesh::~SkinnedMesh()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void SkinnedMesh::Release()
{
	CHECK(bIsInitialized_);

	if (indexBuffer_)
	{
		RenderModule::DestroyResource(indexBuffer_);
		indexBuffer_ = nullptr;
	}

	if (vertexBuffer_)
	{
		RenderModule::DestroyResource(vertexBuffer_);
		vertexBuffer_ = nullptr;
	}

	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	bIsInitialized_ = false;
}

void SkinnedMesh::Bind()
{
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
}

void SkinnedMesh::Unbind()
{
	GL_FAILED(glBindVertexArray(0));
}
