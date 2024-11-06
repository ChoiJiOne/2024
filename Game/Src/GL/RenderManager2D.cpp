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
	static const uint32_t SHADER_BIND_SLOT = 0;
	glm::mat4 ortho;
};

/**
 * (0.5f, 0.5f) vs (0.375f, 0.375f)
 * https://community.khronos.org/t/pixel-perfect-drawing/38454
 * https://stackoverflow.com/questions/10040961/opengl-pixel-perfect-2d-drawing
 */
static const glm::vec2 PIXEL_OFFSET = glm::vec2(0.375f, 0.375f);

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
	CHECK(!bIsBegin_ && camera2D);

	PerFrameUBO ubo;
	ubo.ortho = camera2D->GetOrtho();
	uniformBuffer_->SetBufferData(&ubo, sizeof(PerFrameUBO));

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

	Flush();

	glManager_->SetCullFaceMode(originEnableCull_);
	glManager_->SetDepthMode(originEnableDepth_);

	bIsBegin_ = false;
}

void RenderManager2D::DrawPoint(const glm::vec2& point, const glm::vec4& color, float pointSize)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w = pointSize * 0.5f;
	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w, -w),
		glm::vec2(+w, +w),
		glm::vec2(-w, +w),
		glm::vec2(-w, -w),
		glm::vec2(+w, -w),
		glm::vec2(+w, +w),
	};

	for (auto& vertex : vertices)
	{
		vertex += (point + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == DrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color = color;
			}

			return;
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	RenderCommand command;
	command.drawMode = DrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawLine(const glm::vec2& startPos, const glm::vec2& endPos, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 2;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		startPos + PIXEL_OFFSET,
		  endPos + PIXEL_OFFSET,
	};

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == DrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color = color;
			}

			return;
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	RenderCommand command;
	command.drawMode = DrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color = color;
	}

	commandQueue_.push(command);
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
	VertexBuffer::EUsage vertexBufferUsage = VertexBuffer::EUsage::DYNAMIC;
	vertexBuffer_ = glManager_->Create<VertexBuffer>(vertexBufferByteSize, vertexBufferUsage);

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
	UniformBuffer::EUsage uniformBufferUsage = UniformBuffer::EUsage::DYNAMIC;
	uniformBuffer_ = glManager_->Create<UniformBuffer>(uniformBufferByteSize, uniformBufferUsage);
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
	if (commandQueue_.empty()) /** Command Queue가 비어있으면 동작X */
	{
		return;
	}

	const void* vertexPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(Vertex::GetStride() * vertices_.size());
	vertexBuffer_->SetBufferData(vertexPtr, bufferByteSize);
	uniformBuffer_->BindSlot(PerFrameUBO::SHADER_BIND_SLOT);

	GL_API_CHECK(glBindVertexArray(vertexArrayObject_));

	while (!commandQueue_.empty())
	{
		RenderCommand command = commandQueue_.front();
		commandQueue_.pop();

		Shader* shader = shaders_.at(command.type);
		shader->Bind();
		{
			GL_API_CHECK(glDrawArrays(static_cast<GLenum>(command.drawMode), command.startVertexIndex, command.vertexCount));
		}
		shader->Unbind();
	}

	GL_API_CHECK(glBindVertexArray(0));
}

bool RenderManager2D::IsFullCommandQueue(uint32_t vertexCount)
{
	if (commandQueue_.empty())
	{
		return false;
	}

	const RenderCommand& command = commandQueue_.back();
	uint32_t index = command.startVertexIndex + command.vertexCount + vertexCount;

	return index >= MAX_VERTEX_BUFFER_SIZE;
}

#pragma warning(pop)