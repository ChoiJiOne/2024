#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26819)
#pragma warning(disable: 26451)
#pragma warning(disable: 6031)

#include <glad/glad.h>
#include <glm/gtc/constants.hpp>

#include "Entity/Camera2D.h"
#include "GL/FrameBuffer.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/ITexture.h"
#include "GL/PostProcessor.h"
#include "GL/RenderManager2D.h"
#include "GL/Shader.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "GL/UniformBuffer.h"
#include "GL/VertexBuffer.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

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

	const glm::mat4& ortho = camera2D->GetOrtho();
	if (perFrameUBO_.ortho != ortho) /** 행렬이 변경되었을 때만 업데이트. */
	{
		perFrameUBO_.ortho = ortho;
		uniformBuffer_->SetBufferData(&perFrameUBO_, sizeof(PerFrameUBO));
	}

	GL_API_CHECK(glGetIntegerv(GL_VIEWPORT, originContext_.viewport));
	GL_API_CHECK(glGetBooleanv(GL_DEPTH_TEST, reinterpret_cast<GLboolean*>(&originContext_.bEnableDepth)));
	GL_API_CHECK(glGetBooleanv(GL_CULL_FACE, reinterpret_cast<GLboolean*>(&originContext_.bEnableCull)));

	glManager_->SetDepthMode(false);
	glManager_->SetCullFaceMode(false);
	glManager_->SetViewport(0, 0, static_cast<int32_t>(camera2D->GetWidth()), static_cast<int32_t>(camera2D->GetHeight()));

	bIsBegin_ = true;
}

void RenderManager2D::Begin(const Camera2D* camera2D, FrameBuffer* renderTargetBuffer, const RenderTargetOption& option)
{
	CHECK(!bIsBegin_ && camera2D && renderTargetBuffer);

	const glm::mat4& ortho = camera2D->GetOrtho();
	if (perFrameUBO_.ortho != ortho) /** 행렬이 변경되었을 때만 업데이트. */
	{
		perFrameUBO_.ortho = ortho;
		uniformBuffer_->SetBufferData(&perFrameUBO_, sizeof(PerFrameUBO));
	}

	GL_API_CHECK(glGetIntegerv(GL_VIEWPORT, originContext_.viewport));
	GL_API_CHECK(glGetBooleanv(GL_DEPTH_TEST, reinterpret_cast<GLboolean*>(&originContext_.bEnableDepth)));
	GL_API_CHECK(glGetBooleanv(GL_CULL_FACE, reinterpret_cast<GLboolean*>(&originContext_.bEnableCull)));

	renderTargetBuffer_ = renderTargetBuffer;

	glManager_->SetDepthMode(false);
	glManager_->SetCullFaceMode(false);
	glManager_->SetViewport(0, 0, renderTargetBuffer_->GetWidth(), renderTargetBuffer_->GetHeight());

	renderTargetBuffer_->Bind();

	if (option.bIsClearBuffer)
	{
		renderTargetBuffer_->Clear(option.clearColor.x, option.clearColor.y, option.clearColor.z, option.clearColor.a);
	}

	bIsBegin_ = true;
}

void RenderManager2D::End()
{
	CHECK(bIsBegin_);

	Flush();

	glManager_->SetCullFaceMode(originContext_.bEnableCull);
	glManager_->SetDepthMode(originContext_.bEnableDepth);
	glManager_->SetViewport(originContext_.viewport[0], originContext_.viewport[1], originContext_.viewport[2], originContext_.viewport[3]);

	if (renderTargetBuffer_)
	{
		renderTargetBuffer_->Unbind();
		renderTargetBuffer_ = nullptr;
	}

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
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
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

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawLine(const glm::vec2& startPos, const glm::vec4& startColor, const glm::vec2& endPos, const glm::vec4& endColor)
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

	std::array<glm::vec4, MAX_VERTEX_SIZE> colors =
	{
		startColor,
		endColor,
	};

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = colors[index];
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = colors[index];
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTriangle(const glm::vec2& fromPos, const glm::vec2& byPos, const glm::vec2& toPos, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 3;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		fromPos + PIXEL_OFFSET,
		  byPos + PIXEL_OFFSET,
		  toPos + PIXEL_OFFSET,
	};

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTriangle(const glm::vec2& fromPos, const glm::vec4& fromColor, const glm::vec2& byPos, const glm::vec4& byColor, const glm::vec2& toPos, const glm::vec4& toColor)
{
	static const uint32_t MAX_VERTEX_SIZE = 3;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		fromPos + PIXEL_OFFSET,
		  byPos + PIXEL_OFFSET,
		  toPos + PIXEL_OFFSET,
	};

	std::array<glm::vec4, MAX_VERTEX_SIZE> colors =
	{
		fromColor,
		  byColor,
		  toColor,
	};

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = colors[index];
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
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = colors[index];
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTriangleWireframe(const glm::vec2& fromPos, const glm::vec2& byPos, const glm::vec2& toPos, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		fromPos + PIXEL_OFFSET,   byPos + PIXEL_OFFSET,
		  byPos + PIXEL_OFFSET,   toPos + PIXEL_OFFSET,
		  toPos + PIXEL_OFFSET, fromPos + PIXEL_OFFSET,
	};

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTriangleWireframe(const glm::vec2& fromPos, const glm::vec4& fromColor, const glm::vec2& byPos, const glm::vec4& byColor, const glm::vec2& toPos, const glm::vec4& toColor)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		fromPos + PIXEL_OFFSET,   byPos + PIXEL_OFFSET,
		  byPos + PIXEL_OFFSET,   toPos + PIXEL_OFFSET,
		  toPos + PIXEL_OFFSET, fromPos + PIXEL_OFFSET,
	};

	std::array<glm::vec4, MAX_VERTEX_SIZE> colors =
	{
		fromColor,   byColor,
		  byColor,   toColor,
		  toColor, fromColor,
	};

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = colors[index];
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = colors[index];
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawRect(const glm::vec2& center, float w, float h, const glm::vec4& color, float rotate)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);
	for (auto& vertex : vertices)
	{
		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawRectWireframe(const glm::vec2& center, float w, float h, const glm::vec4& color, float rotate)
{
	static const uint32_t MAX_VERTEX_SIZE = 8;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2), glm::vec2(+w2, -h2),
		glm::vec2(+w2, -h2), glm::vec2(+w2, +h2),
		glm::vec2(+w2, +h2), glm::vec2(-w2, +h2),
		glm::vec2(-w2, +h2), glm::vec2(-w2, -h2),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);
	for (auto& vertex : vertices)
	{
		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 300;
	static const uint32_t MAX_SLICE_SIZE = 100;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	uint32_t vertexCount = 0;
	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices;

	for (int32_t slice = 0; slice < MAX_SLICE_SIZE; ++slice)
	{
		float radian0 = (static_cast<float>(slice + 0) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);
		float radian1 = (static_cast<float>(slice + 1) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);

		vertices[vertexCount + 0] = center + PIXEL_OFFSET;
		vertices[vertexCount + 1] = center + glm::vec2(radius * glm::cos(radian0), radius * glm::sin(radian0)) + PIXEL_OFFSET;
		vertices[vertexCount + 2] = center + glm::vec2(radius * glm::cos(radian1), radius * glm::sin(radian1)) + PIXEL_OFFSET;

		vertexCount += 3;
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawCircleWireframe(const glm::vec2& center, float radius, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 200;
	static const uint32_t MAX_SLICE_SIZE = 100;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	uint32_t vertexCount = 0;
	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices;

	for (int32_t slice = 0; slice < MAX_SLICE_SIZE; ++slice)
	{
		float radian0 = (static_cast<float>(slice + 0) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);
		float radian1 = (static_cast<float>(slice + 1) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);

		vertices[vertexCount + 0] = center + glm::vec2(radius * glm::cos(radian0), radius * glm::sin(radian0)) + PIXEL_OFFSET;
		vertices[vertexCount + 1] = center + glm::vec2(radius * glm::cos(radian1), radius * glm::sin(radian1)) + PIXEL_OFFSET;

		vertexCount += 2;
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawEllipse(const glm::vec2& center, float xHalfAxis, float yHalfAxis, float rotate, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 300;
	static const uint32_t MAX_SLICE_SIZE = 100;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	uint32_t vertexCount = 0;
	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices;

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);
	
	for (int32_t slice = 0; slice < MAX_SLICE_SIZE; ++slice)
	{
		float radian0 = (static_cast<float>(slice + 0) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);
		float radian1 = (static_cast<float>(slice + 1) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);

		vertices[vertexCount + 0] = glm::vec2(0.0f, 0.0f);
		vertices[vertexCount + 1] = glm::vec2(xHalfAxis * glm::cos(radian0), yHalfAxis * glm::sin(radian0)) * rotateMat;
		vertices[vertexCount + 2] = glm::vec2(xHalfAxis * glm::cos(radian1), yHalfAxis * glm::sin(radian1)) * rotateMat;

		for (uint32_t index = 0; index < 3; ++index)
		{
			vertices[vertexCount + index] += (center + PIXEL_OFFSET);
		}

		vertexCount += 3;
	}
	
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);

}

void RenderManager2D::DrawEllipseWireframe(const glm::vec2& center, float xHalfAxis, float yHalfAxis, float rotate, const glm::vec4& color)
{
	static const uint32_t MAX_VERTEX_SIZE = 200;
	static const uint32_t MAX_SLICE_SIZE = 100;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	uint32_t vertexCount = 0;
	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices;

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (int32_t slice = 0; slice < MAX_SLICE_SIZE; ++slice)
	{
		float radian0 = (static_cast<float>(slice + 0) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);
		float radian1 = (static_cast<float>(slice + 1) * glm::pi<float>() * 2.0f) / static_cast<float>(MAX_SLICE_SIZE);

		vertices[vertexCount + 0] = glm::vec2(xHalfAxis * glm::cos(radian0), yHalfAxis * glm::sin(radian0)) * rotateMat;
		vertices[vertexCount + 1] = glm::vec2(xHalfAxis * glm::cos(radian1), yHalfAxis * glm::sin(radian1)) * rotateMat;

		for (uint32_t index = 0; index < 2; ++index)
		{
			vertices[vertexCount + index] += (center + PIXEL_OFFSET);
		}

		vertexCount += 2;
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::LINES && prevCommand.type == RenderCommand::EType::GEOMETRY)
		{
			uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
			prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

			for (uint32_t index = 0; index < vertices.size(); ++index)
			{
				vertices_[startVertexIndex + index].position = vertices[index];
				vertices_[startVertexIndex + index].color0 = color;
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
	command.drawMode = EDrawMode::LINES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::GEOMETRY;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].color0 = color;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == texture)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = texture;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE;
	command.textures[textureUnit] = texture;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = 1.0f;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	float xoffset = 1.0f / static_cast<float>(texture->GetWidth());
	float yoffset = 1.0f / static_cast<float>(texture->GetHeight());
	
	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(0.0f - xoffset, 1.0f + yoffset),
		glm::vec2(1.0f + xoffset, 0.0f - yoffset),
		glm::vec2(0.0f - xoffset, 0.0f - yoffset),
		glm::vec2(0.0f - xoffset, 1.0f + yoffset),
		glm::vec2(1.0f + xoffset, 1.0f + yoffset),
		glm::vec2(1.0f + xoffset, 0.0f - yoffset),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE_EX)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == texture)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = texture;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE_EX;
	command.textures[textureUnit] = texture;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		vertices_[command.startVertexIndex + index].color1 = outlineColor;
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = 1.0f;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate, const TextureDrawOption& option)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex.x = option.bIsFlipH ? -vertex.x : vertex.x;
		vertex.y = option.bIsFlipV ? -vertex.y : vertex.y;

		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == texture)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = texture;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE;
	command.textures[textureUnit] = texture;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = option.transparent;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTexture(ITexture* texture, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor, const TextureDrawOption& option)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	float xoffset = 1.0f / static_cast<float>(texture->GetWidth());
	float yoffset = 1.0f / static_cast<float>(texture->GetHeight());

	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(0.0f - xoffset, 1.0f + yoffset),
		glm::vec2(1.0f + xoffset, 0.0f - yoffset),
		glm::vec2(0.0f - xoffset, 0.0f - yoffset),
		glm::vec2(0.0f - xoffset, 1.0f + yoffset),
		glm::vec2(1.0f + xoffset, 1.0f + yoffset),
		glm::vec2(1.0f + xoffset, 0.0f - yoffset),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex.x = option.bIsFlipH ? -vertex.x : vertex.x;
		vertex.y = option.bIsFlipV ? -vertex.y : vertex.y;

		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE_EX)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == texture)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = texture;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE_EX;
	command.textures[textureUnit] = texture;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
		vertices_[command.startVertexIndex + index].color1 = outlineColor;
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = option.transparent;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	const TextureAtlas2D::Bound& bound = textureAtlas->GetByName(name);
	float x0 = static_cast<float>(bound.x);
	float y0 = static_cast<float>(bound.y);
	float x1 = static_cast<float>(bound.x + bound.w);
	float y1 = static_cast<float>(bound.y + bound.h);
	float atlasWidth = static_cast<float>(textureAtlas->GetWidth());
	float atlasHeight = static_cast<float>(textureAtlas->GetHeight());
	
	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(x0 / atlasWidth, y1 / atlasHeight),
		glm::vec2(x1 / atlasWidth, y0 / atlasHeight),
		glm::vec2(x0 / atlasWidth, y0 / atlasHeight),
		glm::vec2(x0 / atlasWidth, y1 / atlasHeight),
		glm::vec2(x1 / atlasWidth, y1 / atlasHeight),
		glm::vec2(x1 / atlasWidth, y0 / atlasHeight),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == textureAtlas)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = textureAtlas;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE;
	command.textures[textureUnit] = textureAtlas;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = 1.0f;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	const TextureAtlas2D::Bound& bound = textureAtlas->GetByName(name);
	float x0 = static_cast<float>(bound.x);
	float y0 = static_cast<float>(bound.y);
	float x1 = static_cast<float>(bound.x + bound.w);
	float y1 = static_cast<float>(bound.y + bound.h);
	float atlasWidth = static_cast<float>(textureAtlas->GetWidth());
	float atlasHeight = static_cast<float>(textureAtlas->GetHeight());
	float xoffset = 1.0f / atlasWidth;
	float yoffset = 1.0f / atlasHeight;

	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(x0 / atlasWidth - xoffset, y1 / atlasHeight + yoffset),
		glm::vec2(x1 / atlasWidth + xoffset, y0 / atlasHeight - yoffset),
		glm::vec2(x0 / atlasWidth - xoffset, y0 / atlasHeight - yoffset),
		glm::vec2(x0 / atlasWidth - xoffset, y1 / atlasHeight + yoffset),
		glm::vec2(x1 / atlasWidth + xoffset, y1 / atlasHeight + yoffset),
		glm::vec2(x1 / atlasWidth + xoffset, y0 / atlasHeight - yoffset),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE_EX)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == textureAtlas)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = textureAtlas;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = 1.0f;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE_EX;
	command.textures[textureUnit] = textureAtlas;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		vertices_[command.startVertexIndex + index].color1 = outlineColor;
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = 1.0f;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate, const TextureDrawOption& option)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	const TextureAtlas2D::Bound& bound = textureAtlas->GetByName(name);
	float x0 = static_cast<float>(bound.x);
	float y0 = static_cast<float>(bound.y);
	float x1 = static_cast<float>(bound.x + bound.w);
	float y1 = static_cast<float>(bound.y + bound.h);
	float atlasWidth = static_cast<float>(textureAtlas->GetWidth());
	float atlasHeight = static_cast<float>(textureAtlas->GetHeight());

	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(x0 / atlasWidth, y1 / atlasHeight),
		glm::vec2(x1 / atlasWidth, y0 / atlasHeight),
		glm::vec2(x0 / atlasWidth, y0 / atlasHeight),
		glm::vec2(x0 / atlasWidth, y1 / atlasHeight),
		glm::vec2(x1 / atlasWidth, y1 / atlasHeight),
		glm::vec2(x1 / atlasWidth, y0 / atlasHeight),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex.x = option.bIsFlipH ? -vertex.x : vertex.x;
		vertex.y = option.bIsFlipV ? -vertex.y : vertex.y;

		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == textureAtlas)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = textureAtlas;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE;
	command.textures[textureUnit] = textureAtlas;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = option.transparent;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawTextureAtlas(TextureAtlas2D* textureAtlas, const std::string& name, const glm::vec2& center, float w, float h, float rotate, const glm::vec4& outlineColor, const TextureDrawOption& option)
{
	static const uint32_t MAX_VERTEX_SIZE = 6;
	if (IsFullCommandQueue(MAX_VERTEX_SIZE))
	{
		Flush();
	}

	float w2 = w * 0.5f;
	float h2 = h * 0.5f;

	std::array<glm::vec2, MAX_VERTEX_SIZE> vertices =
	{
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, +h2),
		glm::vec2(-w2, +h2),
		glm::vec2(-w2, -h2),
		glm::vec2(+w2, -h2),
		glm::vec2(+w2, +h2),
	};

	const TextureAtlas2D::Bound& bound = textureAtlas->GetByName(name);
	float x0 = static_cast<float>(bound.x);
	float y0 = static_cast<float>(bound.y);
	float x1 = static_cast<float>(bound.x + bound.w);
	float y1 = static_cast<float>(bound.y + bound.h);
	float atlasWidth = static_cast<float>(textureAtlas->GetWidth());
	float atlasHeight = static_cast<float>(textureAtlas->GetHeight());
	float xoffset = 1.0f / atlasWidth;
	float yoffset = 1.0f / atlasHeight;

	std::array<glm::vec2, MAX_VERTEX_SIZE> uvs =
	{
		glm::vec2(x0 / atlasWidth - xoffset, y1 / atlasHeight + yoffset),
		glm::vec2(x1 / atlasWidth + xoffset, y0 / atlasHeight - yoffset),
		glm::vec2(x0 / atlasWidth - xoffset, y0 / atlasHeight - yoffset),
		glm::vec2(x0 / atlasWidth - xoffset, y1 / atlasHeight + yoffset),
		glm::vec2(x1 / atlasWidth + xoffset, y1 / atlasHeight + yoffset),
		glm::vec2(x1 / atlasWidth + xoffset, y0 / atlasHeight - yoffset),
	};

	glm::mat2 rotateMat = glm::mat2(
		+glm::cos(rotate), -glm::sin(rotate),
		+glm::sin(rotate), +glm::cos(rotate)
	);

	for (auto& vertex : vertices)
	{
		vertex.x = option.bIsFlipH ? -vertex.x : vertex.x;
		vertex.y = option.bIsFlipV ? -vertex.y : vertex.y;

		vertex = vertex * rotateMat;
		vertex += (center + PIXEL_OFFSET);
	}

	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::TEXTURE_EX)
		{
			int32_t textureUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == textureAtlas)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.textures[unit] == nullptr)
				{
					textureUnit = unit;
					break;
				}
			}

			if (textureUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += static_cast<uint32_t>(vertices.size());
				prevCommand.textures[textureUnit] = textureAtlas;

				for (uint32_t index = 0; index < vertices.size(); ++index)
				{
					vertices_[startVertexIndex + index].position = vertices[index];
					vertices_[startVertexIndex + index].uv = uvs[index];
					vertices_[startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
					vertices_[startVertexIndex + index].color1 = outlineColor;
					vertices_[startVertexIndex + index].unit = textureUnit;
					vertices_[startVertexIndex + index].transparent = option.transparent;
				}

				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t textureUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = static_cast<uint32_t>(vertices.size());
	command.type = RenderCommand::EType::TEXTURE_EX;
	command.textures[textureUnit] = textureAtlas;

	for (uint32_t index = 0; index < command.vertexCount; ++index)
	{
		vertices_[command.startVertexIndex + index].position = vertices[index];
		vertices_[command.startVertexIndex + index].uv = uvs[index];
		vertices_[command.startVertexIndex + index].color0 = glm::vec4(option.blend.x, option.blend.y, option.blend.z, option.factor);
		vertices_[command.startVertexIndex + index].color1 = outlineColor;
		vertices_[command.startVertexIndex + index].unit = textureUnit;
		vertices_[command.startVertexIndex + index].transparent = option.transparent;
	}

	commandQueue_.push(command);
}

void RenderManager2D::DrawString(TTFont* font, const std::wstring& text, const glm::vec2& basePos, const glm::vec4& color)
{
	/** 문자 하나당 정점 6개. */
	uint32_t vertexCount = 6 * static_cast<uint32_t>(text.size());
	if (IsFullCommandQueue(vertexCount))
	{
		Flush();
	}

	float atlasWidth = static_cast<float>(font->GetWidth());
	float atlasHeight = static_cast<float>(font->GetHeight());
	glm::vec2 currPos = glm::vec2(basePos.x, basePos.y);

	auto composeVertexData = [&](uint32_t vertexIndex, uint32_t unit)
		{
			for (const auto& unicode : text)
			{
				const Glyph& glyph = font->GetGlyph(static_cast<int32_t>(unicode));

				float w = static_cast<float>(glyph.pos1.x - glyph.pos0.x);
				float h = static_cast<float>(glyph.pos1.y - glyph.pos0.y);
				float ux0 = static_cast<float>(glyph.pos0.x) / atlasWidth;
				float uy0 = static_cast<float>(glyph.pos0.y) / atlasHeight;
				float ux1 = static_cast<float>(glyph.pos1.x) / atlasWidth;
				float uy1 = static_cast<float>(glyph.pos1.y) / atlasHeight;

				vertices_[vertexIndex + 0].position = glm::vec2(currPos.x + glyph.xoff, currPos.y - glyph.yoff2);
				vertices_[vertexIndex + 0].uv = glm::vec2(ux0, uy1);
				vertices_[vertexIndex + 0].color0 = color;
				vertices_[vertexIndex + 0].unit = unit;

				vertices_[vertexIndex + 1].position = glm::vec2(currPos.x + w + glyph.xoff, currPos.y - glyph.yoff);
				vertices_[vertexIndex + 1].uv = glm::vec2(ux1, uy0);
				vertices_[vertexIndex + 1].color0 = color;
				vertices_[vertexIndex + 1].unit = unit;

				vertices_[vertexIndex + 2].position = glm::vec2(currPos.x + glyph.xoff, currPos.y - glyph.yoff);
				vertices_[vertexIndex + 2].uv = glm::vec2(ux0, uy0);
				vertices_[vertexIndex + 2].color0 = color;
				vertices_[vertexIndex + 2].unit = unit;

				vertices_[vertexIndex + 3].position = glm::vec2(currPos.x + glyph.xoff, currPos.y - glyph.yoff2);
				vertices_[vertexIndex + 3].uv = glm::vec2(ux0, uy1);
				vertices_[vertexIndex + 3].color0 = color;
				vertices_[vertexIndex + 3].unit = unit;

				vertices_[vertexIndex + 4].position = glm::vec2(currPos.x + w + glyph.xoff, currPos.y - glyph.yoff2);
				vertices_[vertexIndex + 4].uv = glm::vec2(ux1, uy1);
				vertices_[vertexIndex + 4].color0 = color;
				vertices_[vertexIndex + 4].unit = unit;

				vertices_[vertexIndex + 5].position = glm::vec2(currPos.x + w + glyph.xoff, currPos.y - glyph.yoff);
				vertices_[vertexIndex + 5].uv = glm::vec2(ux1, uy0);
				vertices_[vertexIndex + 5].color0 = color;
				vertices_[vertexIndex + 5].unit = unit;

				currPos.x += glyph.xadvance;
				vertexIndex += 6;
			}
		};


	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::STRING)
		{
			int32_t atlasUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.fonts[unit] == font)
				{
					atlasUnit = unit;
					break;
				}
			}

			if (atlasUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += vertexCount;

				composeVertexData(startVertexIndex, atlasUnit);
				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.fonts[unit] == nullptr)
				{
					atlasUnit = unit;
					break;
				}
			}

			if (atlasUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += vertexCount;
				prevCommand.fonts[atlasUnit] = font;

				composeVertexData(startVertexIndex, atlasUnit);
				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t atlasUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = vertexCount;
	command.type = RenderCommand::EType::STRING;
	command.fonts[atlasUnit] = font;

	composeVertexData(command.startVertexIndex, atlasUnit);

	commandQueue_.push(command);
}

void RenderManager2D::DrawString(TTFont* font, const std::wstring& text, const glm::vec2& basePos, const glm::vec4& textColor, const glm::vec4& outlineColor)
{	
	/** 문자 하나당 정점 6개. */
	uint32_t vertexCount = 6 * static_cast<uint32_t>(text.size());
	if (IsFullCommandQueue(vertexCount))
	{
		Flush();
	}

	float atlasWidth = static_cast<float>(font->GetWidth());
	float atlasHeight = static_cast<float>(font->GetHeight());
	glm::vec2 currPos = glm::vec2(basePos.x, basePos.y);

	auto composeVertexData = [&](uint32_t vertexIndex, uint32_t unit)
		{
			for (const auto& unicode : text)
			{
				const Glyph& glyph = font->GetGlyph(static_cast<int32_t>(unicode));

				float w = static_cast<float>(glyph.pos1.x - glyph.pos0.x);
				float h = static_cast<float>(glyph.pos1.y - glyph.pos0.y);
				float ux0 = static_cast<float>(glyph.pos0.x - 1) / atlasWidth;
				float uy0 = static_cast<float>(glyph.pos0.y - 1) / atlasHeight;
				float ux1 = static_cast<float>(glyph.pos1.x + 1) / atlasWidth;
				float uy1 = static_cast<float>(glyph.pos1.y + 1) / atlasHeight;

				vertices_[vertexIndex + 0].position = glm::vec2(currPos.x + glyph.xoff, currPos.y - glyph.yoff2);
				vertices_[vertexIndex + 0].uv = glm::vec2(ux0, uy1);
				vertices_[vertexIndex + 0].color0 = textColor;
				vertices_[vertexIndex + 0].color1 = outlineColor;
				vertices_[vertexIndex + 0].unit = unit;

				vertices_[vertexIndex + 1].position = glm::vec2(currPos.x + w + glyph.xoff, currPos.y - glyph.yoff);
				vertices_[vertexIndex + 1].uv = glm::vec2(ux1, uy0);
				vertices_[vertexIndex + 1].color0 = textColor;
				vertices_[vertexIndex + 1].color1 = outlineColor;
				vertices_[vertexIndex + 1].unit = unit;

				vertices_[vertexIndex + 2].position = glm::vec2(currPos.x + glyph.xoff, currPos.y - glyph.yoff);
				vertices_[vertexIndex + 2].uv = glm::vec2(ux0, uy0);
				vertices_[vertexIndex + 2].color0 = textColor;
				vertices_[vertexIndex + 2].color1 = outlineColor;
				vertices_[vertexIndex + 2].unit = unit;

				vertices_[vertexIndex + 3].position = glm::vec2(currPos.x + glyph.xoff, currPos.y - glyph.yoff2);
				vertices_[vertexIndex + 3].uv = glm::vec2(ux0, uy1);
				vertices_[vertexIndex + 3].color0 = textColor;
				vertices_[vertexIndex + 3].color1 = outlineColor;
				vertices_[vertexIndex + 3].unit = unit;

				vertices_[vertexIndex + 4].position = glm::vec2(currPos.x + w + glyph.xoff, currPos.y - glyph.yoff2);
				vertices_[vertexIndex + 4].uv = glm::vec2(ux1, uy1);
				vertices_[vertexIndex + 4].color0 = textColor;
				vertices_[vertexIndex + 4].color1 = outlineColor;
				vertices_[vertexIndex + 4].unit = unit;

				vertices_[vertexIndex + 5].position = glm::vec2(currPos.x + w + glyph.xoff, currPos.y - glyph.yoff);
				vertices_[vertexIndex + 5].uv = glm::vec2(ux1, uy0);
				vertices_[vertexIndex + 5].color0 = textColor;
				vertices_[vertexIndex + 5].color1 = outlineColor;
				vertices_[vertexIndex + 5].unit = unit;

				currPos.x += glyph.xadvance;
				vertexIndex += 6;
			}
		};


	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();

		if (prevCommand.drawMode == EDrawMode::TRIANGLES && prevCommand.type == RenderCommand::EType::STRING_EX)
		{
			int32_t atlasUnit = -1;
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.fonts[unit] == font)
				{
					atlasUnit = unit;
					break;
				}
			}

			if (atlasUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += vertexCount;

				composeVertexData(startVertexIndex, atlasUnit);
				return;
			}

			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (prevCommand.fonts[unit] == nullptr)
				{
					atlasUnit = unit;
					break;
				}
			}

			if (atlasUnit != -1)
			{
				uint32_t startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
				prevCommand.vertexCount += vertexCount;
				prevCommand.fonts[atlasUnit] = font;

				composeVertexData(startVertexIndex, atlasUnit);
				return;
			}
		}
	}

	uint32_t startVertexIndex = 0;
	if (!commandQueue_.empty())
	{
		RenderCommand& prevCommand = commandQueue_.back();
		startVertexIndex = prevCommand.startVertexIndex + prevCommand.vertexCount;
	}

	uint32_t atlasUnit = 0;

	RenderCommand command;
	command.drawMode = EDrawMode::TRIANGLES;
	command.startVertexIndex = startVertexIndex;
	command.vertexCount = vertexCount;
	command.type = RenderCommand::EType::STRING_EX;
	command.fonts[atlasUnit] = font;

	composeVertexData(command.startVertexIndex, atlasUnit);

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
	if (postProcessor_)
	{
		glManager_->Destroy(postProcessor_);
		postProcessor_ = nullptr;
	}

	for (auto& shader : shaders_)
	{
		if (shader.second)
		{
			glManager_->Destroy(shader.second);
			shader.second = nullptr;
		}
	}

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

		GL_API_CHECK(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, color0))));
		GL_API_CHECK(glEnableVertexAttribArray(2));

		GL_API_CHECK(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, color1))));
		GL_API_CHECK(glEnableVertexAttribArray(3));

		GL_API_CHECK(glVertexAttribIPointer(4, 1, GL_INT, Vertex::GetStride(), (void*)(offsetof(Vertex, unit))));
		GL_API_CHECK(glEnableVertexAttribArray(4));

		GL_API_CHECK(glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, transparent))));
		GL_API_CHECK(glEnableVertexAttribArray(5));

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
	std::string vsSource;
	std::string fsSource;
	std::string outErrMsg;

	ASSERTION(ReadFile("MiniGame\\Shader\\Geometry.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("MiniGame\\Shader\\Geometry.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	vsSource = std::string(vsBuffer.begin(), vsBuffer.end());
	fsSource = std::string(fsBuffer.begin(), fsBuffer.end());
	
	shaders_.insert({ RenderCommand::EType::GEOMETRY, glManager_->Create<Shader>(vsSource, fsSource) });

	ASSERTION(ReadFile("MiniGame\\Shader\\Texture.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("MiniGame\\Shader\\Texture.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	vsSource = std::string(vsBuffer.begin(), vsBuffer.end());
	fsSource = std::string(fsBuffer.begin(), fsBuffer.end());

	shaders_.insert({ RenderCommand::EType::TEXTURE, glManager_->Create<Shader>(vsSource, fsSource) });

	ASSERTION(ReadFile("MiniGame\\Shader\\TextureEx.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("MiniGame\\Shader\\TextureEx.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	vsSource = std::string(vsBuffer.begin(), vsBuffer.end());
	fsSource = std::string(fsBuffer.begin(), fsBuffer.end());

	shaders_.insert({ RenderCommand::EType::TEXTURE_EX, glManager_->Create<Shader>(vsSource, fsSource) });

	ASSERTION(ReadFile("MiniGame\\Shader\\String.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("MiniGame\\Shader\\String.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	vsSource = std::string(vsBuffer.begin(), vsBuffer.end());
	fsSource = std::string(fsBuffer.begin(), fsBuffer.end());

	shaders_.insert({ RenderCommand::EType::STRING, glManager_->Create<Shader>(vsSource, fsSource) });

	ASSERTION(ReadFile("MiniGame\\Shader\\StringEx.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("MiniGame\\Shader\\StringEx.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	vsSource = std::string(vsBuffer.begin(), vsBuffer.end());
	fsSource = std::string(fsBuffer.begin(), fsBuffer.end());

	shaders_.insert({ RenderCommand::EType::STRING_EX, glManager_->Create<Shader>(vsSource, fsSource) });

	ASSERTION(ReadFile("MiniGame\\Shader\\PostProcessing.vert", vsBuffer, outErrMsg), "%s", outErrMsg.c_str());
	ASSERTION(ReadFile("MiniGame\\Shader\\PostProcessing.frag", fsBuffer, outErrMsg), "%s", outErrMsg.c_str());

	vsSource = std::string(vsBuffer.begin(), vsBuffer.end());
	fsSource = std::string(fsBuffer.begin(), fsBuffer.end());

	postProcessor_ = glManager_->Create<PostProcessor>(vsSource, fsSource);
}

void RenderManager2D::Flush()
{
	if (commandQueue_.empty()) /** Command Queue가 비어있으면 동작X */
	{
		return;
	}

	void* vertexPtr = reinterpret_cast<void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(Vertex::GetStride() * vertices_.size());
	vertexBuffer_->SetBufferData(vertexPtr, bufferByteSize);
	uniformBuffer_->BindSlot(PerFrameUBO::SHADER_BIND_SLOT);

	GL_API_CHECK(glBindVertexArray(vertexArrayObject_));

	while (!commandQueue_.empty())
	{
		RenderCommand command = commandQueue_.front();
		commandQueue_.pop();

		switch (command.type)
		{
		case RenderCommand::EType::TEXTURE:
		case RenderCommand::EType::TEXTURE_EX:
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (command.textures[unit])
				{
					command.textures[unit]->Active(unit);
				}
			}
			break;

		case RenderCommand::EType::STRING:
		case RenderCommand::EType::STRING_EX:
			for (uint32_t unit = 0; unit < RenderCommand::MAX_TEXTURE_UNIT; ++unit)
			{
				if (command.fonts[unit])
				{
					command.fonts[unit]->Active(unit);
				}
			}
			break;
		}

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