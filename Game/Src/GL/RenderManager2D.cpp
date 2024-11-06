#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26819)
#pragma warning(disable: 26451)
#pragma warning(disable: 6031)

#include <glad/glad.h>

#include "Entity/Camera2D.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Shader.h"
#include "GL/UniformBuffer.h"
#include "GL/VertexBuffer.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

/**
 * 셰이더 상의 매 프레임 바뀌는 유니폼 버퍼입니다.
 * 이 구조체는 2D 렌더 매니저 내부에서만 사용됩니다.
 */
struct PerFrameUBO
{
	glm::mat4 ortho;
};

RenderManager2D RenderManager2D::singleton_;

RenderManager2D& RenderManager2D::GetRef()
{
	return singleton_;
}

RenderManager2D* RenderManager2D::GetPtr()
{
	return &singleton_;
}

void RenderManager2D::Begin(const Camera2D* camera2D)
{
	CHECK(!bIsBegin_ && !camera2D);

	GLboolean originEnableDepth;
	GL_API_CHECK(glGetBooleanv(GL_DEPTH_TEST, &originEnableDepth));

	GLboolean originEnableCull;
	GL_API_CHECK(glGetBooleanv(GL_CULL_FACE, &originEnableCull));

	originEnableDepth_ = static_cast<bool>(originEnableDepth);
	originEnableCull_ = static_cast<bool>(originEnableCull);

	glManager_->SetDepthMode(false);
	glManager_->SetCullFaceMode(false);

	bIsBegin_ = true;
}

void RenderManager2D::End()
{
	CHECK(bIsBegin_);

	glManager_->SetCullFaceMode(originEnableCull_);
	glManager_->SetDepthMode(originEnableDepth_);

	bIsBegin_ = false;
}

void RenderManager2D::Startup()
{
	glManager_ = GLManager::GetPtr();

	LoadBuffers();
	LoadShaders();
}

void RenderManager2D::Shutdown()
{
	if (vertexBuffer_)
	{
		glManager_->Destroy(vertexBuffer_);
		vertexBuffer_ = nullptr;
	}

	if (uniformBuffer_)
	{
		glManager_->Destroy(uniformBuffer_);
		uniformBuffer_ = nullptr;
	}
	
	GL_API_CHECK(glDeleteVertexArrays(1, &vertexArrayObject_));

	glManager_ = nullptr;
}

void RenderManager2D::LoadBuffers()
{
	uint32_t vertexBufferByteSize = static_cast<uint32_t>(Vertex::GetStride() * vertices_.size());
	VertexBuffer::EUsage usage = VertexBuffer::EUsage::DYNAMIC;
	vertexBuffer_ = glManager_->Create<VertexBuffer>(vertexBufferByteSize, usage);

	GL_API_CHECK(glGenVertexArrays(1, &vertexArrayObject_));
	GL_API_CHECK(glBindVertexArray(vertexArrayObject_));
	{
		vertexBuffer_->Bind();

		GL_API_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, position))));
		GL_API_CHECK(glEnableVertexAttribArray(0));

		GL_API_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, uv))));
		GL_API_CHECK(glEnableVertexAttribArray(1));

		GL_API_CHECK(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, color))));
		GL_API_CHECK(glEnableVertexAttribArray(2));

		vertexBuffer_->Unbind();
	}
	GL_API_CHECK(glBindVertexArray(0));

	uint32_t uniformBufferByteSize = static_cast<uint32_t>(sizeof(PerFrameUBO));
	UniformBuffer::EUsage usage = UniformBuffer::EUsage::DYNAMIC;
	uniformBuffer_ = glManager_->Create<UniformBuffer>(uniformBufferByteSize, usage);
}

void RenderManager2D::LoadShaders()
{
	std::vector<uint8_t> vsBuffer;
	std::vector<uint8_t> fsBuffer;
	std::string outErrMsg;

	ASSERTION(ReadFile("Shader\\Geometry.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("Shader\\Geometry.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	std::string vsSource(vsBuffer.begin(), vsBuffer.end());
	std::string fsSource(fsBuffer.begin(), fsBuffer.end());

	Shader* geometry = glManager_->Create<Shader>(vsSource, fsSource);

	shaders_.insert({ RenderCommand::EType::GEOMETRY, geometry });
}

void RenderManager2D::Flush()
{
}

bool RenderManager2D::IsFullCommandQueue(uint32_t vertexCount)
{
	return false;
}

#pragma warning(pop)