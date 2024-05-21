#include <glad/glad.h>

#include "GLAssertion.h"
#include "RenderModule.h"
#include "SkinnedMesh.h"

SkinnedMesh::SkinnedMesh(const std::vector<VertexPositionNormalUvSkin3D>& vertices, const std::vector<uint32_t>& indices, bool bIsUploadedToGPU)
	: vertices_(vertices)
	, skinnedVertices_(vertices)
	, indices_(indices)
	, bIsUploadedToGPU_(bIsUploadedToGPU)
{
	VertexBuffer::EUsage usage = bIsUploadedToGPU_ ? VertexBuffer::EUsage::Dynamic : VertexBuffer::EUsage::Static;

	vertexBuffer_ = RenderModule::CreateResource<VertexBuffer>(vertices_.data(), static_cast<uint32_t>(vertices_.size()) * VertexPositionNormalUvSkin3D::GetStride(), usage);
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

void SkinnedMesh::Skin(const std::vector<Mat4x4>& posePalette, const std::vector<Mat4x4>& invPosePalette)
{
	for (int32_t index = 0; index < vertices_.size(); ++index)
	{
		Vec4f& weight = vertices_[index].weight;
		Vec4i& joints = vertices_[index].joints;

		Mat4x4 m0 = (invPosePalette[joints.x] * posePalette[joints.x]) * weight.x;
		Mat4x4 m1 = (invPosePalette[joints.y] * posePalette[joints.y]) * weight.y;
		Mat4x4 m2 = (invPosePalette[joints.z] * posePalette[joints.z]) * weight.z;
		Mat4x4 m3 = (invPosePalette[joints.w] * posePalette[joints.w]) * weight.w;

		Mat4x4 skin = m0 + m1 + m2 + m3;

		skinnedVertices_[index].position = Vec3f
		(
			vertices_[index].position.x * skin.e00 + vertices_[index].position.y * skin.e10 + vertices_[index].position.z * skin.e20 + skin.e30,
			vertices_[index].position.x * skin.e01 + vertices_[index].position.y * skin.e11 + vertices_[index].position.z * skin.e21 + skin.e31,
			vertices_[index].position.x * skin.e02 + vertices_[index].position.y * skin.e12 + vertices_[index].position.z * skin.e22 + skin.e32
		);

		skinnedVertices_[index].normal = Vec3f
		(
			vertices_[index].normal.x * skin.e00 + vertices_[index].normal.y * skin.e10 + vertices_[index].normal.z * skin.e20,
			vertices_[index].normal.x * skin.e01 + vertices_[index].normal.y * skin.e11 + vertices_[index].normal.z * skin.e21,
			vertices_[index].normal.x * skin.e02 + vertices_[index].normal.y * skin.e12 + vertices_[index].normal.z * skin.e22
		);
	}

	if (bIsUploadedToGPU_)
	{
		const void* vertexPtr = reinterpret_cast<const void*>(skinnedVertices_.data());
		uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionNormalUvSkin3D::GetStride() * skinnedVertices_.size());

		vertexBuffer_->SetBufferData(vertexPtr, bufferByteSize);
	}
}