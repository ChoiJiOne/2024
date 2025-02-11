#include <glad/glad.h>

#include "Assertion.h"
#include "StaticMesh.h"

template StaticMesh<VertexPosition3D>;
template StaticMesh<VertexPositionColor3D>;
template StaticMesh<VertexPositionUv3D>;
template StaticMesh<VertexPositionNormal3D>;
template StaticMesh<VertexPositionNormalUv3D>;

template<>
StaticMesh<VertexPosition3D>::StaticMesh(const std::vector<VertexPosition3D>& vertices, const std::vector<uint32_t>& indices)
	: vertices_(vertices)
	, indices_(indices)
	, vertexBuffer_(vertices_.data(), static_cast<uint32_t>(vertices_.size())* VertexPosition3D::GetStride(), VertexBuffer::EUsage::Static)
{
	const void* indexBufferPtr = reinterpret_cast<const void*>(indices_.data());
	uint32_t indexBufferSize = static_cast<uint32_t>(indices_.size()) * sizeof(uint32_t);

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_.Bind();
		GL_FAILED(glGenBuffers(1, &indexBufferID_));

		GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
		GL_FAILED(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferPtr, GL_STATIC_DRAW));

		GL_FAILED(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPosition3D::GetStride(), (void*)(offsetof(VertexPosition3D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));

		vertexBuffer_.Unbind();
	}

	GL_FAILED(glBindVertexArray(0));

	bIsInitialized_ = true;
}

template<>
StaticMesh<VertexPositionColor3D>::StaticMesh(const std::vector<VertexPositionColor3D>& vertices, const std::vector<uint32_t>& indices)
	: vertices_(vertices)
	, indices_(indices)
	, vertexBuffer_(vertices_.data(), static_cast<uint32_t>(vertices_.size()) * VertexPositionColor3D::GetStride(), VertexBuffer::EUsage::Static)
{
	const void* indexBufferPtr = reinterpret_cast<const void*>(indices_.data());
	uint32_t indexBufferSize = static_cast<uint32_t>(indices_.size()) * sizeof(uint32_t);

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_.Bind();
		GL_FAILED(glGenBuffers(1, &indexBufferID_));

		GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
		GL_FAILED(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferPtr, GL_STATIC_DRAW));

		GL_FAILED(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionColor3D::GetStride(), (void*)(offsetof(VertexPositionColor3D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));

		GL_FAILED(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexPositionColor3D::GetStride(), (void*)(offsetof(VertexPositionColor3D, color))));
		GL_FAILED(glEnableVertexAttribArray(1));

		vertexBuffer_.Unbind();
	}

	GL_FAILED(glBindVertexArray(0));

	bIsInitialized_ = true;
}

template<>
StaticMesh<VertexPositionUv3D>::StaticMesh(const std::vector<VertexPositionUv3D>& vertices, const std::vector<uint32_t>& indices)
	: vertices_(vertices)
	, indices_(indices)
	, vertexBuffer_(vertices_.data(), static_cast<uint32_t>(vertices_.size()) * VertexPositionUv3D::GetStride(), VertexBuffer::EUsage::Static)
{
	const void* indexBufferPtr = reinterpret_cast<const void*>(indices_.data());
	uint32_t indexBufferSize = static_cast<uint32_t>(indices_.size()) * sizeof(uint32_t);

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_.Bind();
		GL_FAILED(glGenBuffers(1, &indexBufferID_));

		GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
		GL_FAILED(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferPtr, GL_STATIC_DRAW));

		GL_FAILED(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionUv3D::GetStride(), (void*)(offsetof(VertexPositionUv3D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));

		GL_FAILED(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionUv3D::GetStride(), (void*)(offsetof(VertexPositionUv3D, uv))));
		GL_FAILED(glEnableVertexAttribArray(2));

		vertexBuffer_.Unbind();
	}

	GL_FAILED(glBindVertexArray(0));

	bIsInitialized_ = true;
}

template<>
StaticMesh<VertexPositionNormal3D>::StaticMesh(const std::vector<VertexPositionNormal3D>& vertices, const std::vector<uint32_t>& indices)
	: vertices_(vertices)
	, indices_(indices)
	, vertexBuffer_(vertices_.data(), static_cast<uint32_t>(vertices_.size()) * VertexPositionNormal3D::GetStride(), VertexBuffer::EUsage::Static)
{
	const void* indexBufferPtr = reinterpret_cast<const void*>(indices_.data());
	uint32_t indexBufferSize = static_cast<uint32_t>(indices_.size()) * sizeof(uint32_t);

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_.Bind();
		GL_FAILED(glGenBuffers(1, &indexBufferID_));

		GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
		GL_FAILED(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferPtr, GL_STATIC_DRAW));

		GL_FAILED(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionNormal3D::GetStride(), (void*)(offsetof(VertexPositionNormal3D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));

		GL_FAILED(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexPositionNormal3D::GetStride(), (void*)(offsetof(VertexPositionNormal3D, normal))));
		GL_FAILED(glEnableVertexAttribArray(1));

		vertexBuffer_.Unbind();
	}

	GL_FAILED(glBindVertexArray(0));

	bIsInitialized_ = true;
}

template<>
StaticMesh<VertexPositionNormalUv3D>::StaticMesh(const std::vector<VertexPositionNormalUv3D>& vertices, const std::vector<uint32_t>& indices)
	: vertices_(vertices)
	, indices_(indices)
	, vertexBuffer_(vertices_.data(), static_cast<uint32_t>(vertices_.size()) * VertexPositionNormalUv3D::GetStride(), VertexBuffer::EUsage::Static)
{
	const void* indexBufferPtr = reinterpret_cast<const void*>(indices_.data());
	uint32_t indexBufferSize = static_cast<uint32_t>(indices_.size()) * sizeof(uint32_t);

	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_.Bind();
		GL_FAILED(glGenBuffers(1, &indexBufferID_));

		GL_FAILED(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
		GL_FAILED(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferPtr, GL_STATIC_DRAW));

		GL_FAILED(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionNormalUv3D::GetStride(), (void*)(offsetof(VertexPositionNormalUv3D, position))));
		GL_FAILED(glEnableVertexAttribArray(0));

		GL_FAILED(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexPositionNormalUv3D::GetStride(), (void*)(offsetof(VertexPositionNormalUv3D, normal))));
		GL_FAILED(glEnableVertexAttribArray(1));

		GL_FAILED(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexPositionNormalUv3D::GetStride(), (void*)(offsetof(VertexPositionNormalUv3D, uv))));
		GL_FAILED(glEnableVertexAttribArray(2));
		
		vertexBuffer_.Unbind();
	}

	GL_FAILED(glBindVertexArray(0));

	bIsInitialized_ = true;
}

template <typename VertexType>
StaticMesh<VertexType>::~StaticMesh()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

template <typename VertexType>
void StaticMesh<VertexType>::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteBuffers(1, &indexBufferID_));
	vertexBuffer_.~VertexBuffer();
	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	bIsInitialized_ = false;
}

template <typename VertexType>
void StaticMesh<VertexType>::Bind()
{
	GL_FAILED(glBindVertexArray(vertexArrayObject_));
}

template <typename VertexType>
void StaticMesh<VertexType>::Unbind()
{
	GL_FAILED(glBindVertexArray(0));
}