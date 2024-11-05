#include <glad/glad.h>
#include <glm/glm.hpp>
#include <imgui.h>

#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/Shader.h"
#include "GL/VertexBuffer.h"
#include "Scene/GameDevScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};

GameDevScene::GameDevScene()
{
	std::array<Vertex, 3> vertices =
	{
		Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		Vertex{glm::vec3(+0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		Vertex{glm::vec3(+0.0f, +0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
	};

	uint32_t stride = static_cast<uint32_t>(sizeof(Vertex));
	uint32_t byteSize = static_cast<uint32_t>(vertices.size()) * stride;
	vertexBuffer_ = GLManager::GetRef().Create<VertexBuffer>(vertices.data(), byteSize, VertexBuffer::EUsage::STATIC);

	GL_API_CHECK(glGenVertexArrays(1, &vao_));
	GL_API_CHECK(glBindVertexArray(vao_));
	{
		vertexBuffer_->Bind();

		GL_API_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offsetof(Vertex, position))));
		GL_API_CHECK(glEnableVertexAttribArray(0));

		GL_API_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(offsetof(Vertex, color))));
		GL_API_CHECK(glEnableVertexAttribArray(1));

		vertexBuffer_->Unbind();
	}
	GL_API_CHECK(glBindVertexArray(0));

	std::vector<uint8_t> vsBuffer;
	std::vector<uint8_t> fsBuffer;
	std::string outErrMsg;

	CHECK(ReadFile("Shader\\Shader.vert", vsBuffer, outErrMsg));
	CHECK(ReadFile("Shader\\Shader.frag", fsBuffer, outErrMsg));

	std::string vsSource(vsBuffer.begin(), vsBuffer.end());
	std::string fsSource(fsBuffer.begin(), fsBuffer.end());

	shader_ = GLManager::GetRef().Create<Shader>(vsSource, fsSource);
}

GameDevScene::~GameDevScene()
{
	GL_API_CHECK(glDeleteVertexArrays(1, &vao_));

	GLManager::GetRef().Destroy(vertexBuffer_);
	GLManager::GetRef().Destroy(shader_);
}

void GameDevScene::Tick(float deltaSeconds)
{
	ImGui::Begin("FPS");
	ImGui::Text("FPS: %f", 1.0f / deltaSeconds);
	ImGui::End();
}

void GameDevScene::Render()
{
	GLManager::GetRef().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		shader_->Bind();
		{
			GL_API_CHECK(glBindVertexArray(vao_));
			GL_API_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
			GL_API_CHECK(glBindVertexArray(0));
		}
		shader_->Unbind();
	}
	GLManager::GetRef().EndFrame();
}

void GameDevScene::Enter()
{
}

void GameDevScene::Exit()
{
}
