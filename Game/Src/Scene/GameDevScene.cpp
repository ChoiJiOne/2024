#include <glad/glad.h>
#include <glm/glm.hpp>
#include <imgui.h>

#include "Entity/Camera2D.h"
#include "Entity/EntityManager.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/Shader.h"
#include "GL/VertexBuffer.h"
#include "Scene/GameDevScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GameDevScene::GameDevScene()
{
	mainCamera_ = EntityManager::GetRef().Create<Camera2D>(glm::vec2(0.0f, 0.0f), glm::vec2(1000.0f, 800.0f));
}

GameDevScene::~GameDevScene()
{
	EntityManager::GetRef().Destroy(mainCamera_);
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
	}
	GLManager::GetRef().EndFrame();
}

void GameDevScene::Enter()
{
}

void GameDevScene::Exit()
{
}
