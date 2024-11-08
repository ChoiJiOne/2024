#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "Entity/Camera2D.h"
#include "Entity/EntityManager.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/Shader.h"
#include "GL/Texture2D.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "GL/VertexBuffer.h"
#include "Scene/GameDevScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GameDevScene::GameDevScene()
{
	mainCamera_ = EntityManager::GetRef().Create<Camera2D>(glm::vec2(0.0f, 0.0f), glm::vec2(1000.0f, 800.0f));

	atlas_ = GLManager::GetRef().Create<TextureAtlas2D>("Resource\\texture.png", "Resource\\texture.atlas", Texture2D::EFilter::LINEAR);
}

GameDevScene::~GameDevScene()
{
	GLManager::GetRef().Destroy(atlas_);

	EntityManager::GetRef().Destroy(mainCamera_);
}

void GameDevScene::Tick(float deltaSeconds)
{
	ImGui::Begin("OPTION");
	ImGui::ColorEdit3("Blend", glm::value_ptr(option_.blend));
	ImGui::ColorEdit4("Outline", glm::value_ptr(outline_));
	ImGui::SliderFloat("Factor", &option_.factor, 0.0f, 1.0f);
	ImGui::SliderFloat("Transparent", &option_.transparent, 0.0f, 1.0f);
	ImGui::Checkbox("bIsFlipH", &option_.bIsFlipH);
	ImGui::Checkbox("bIsFlipV", &option_.bIsFlipV);
	ImGui::End();
}

void GameDevScene::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::GetRef();

	GLManager::GetRef().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderMgr.Begin(mainCamera_);
		{
			for (float x = -500; x <= 500.0f; x += 10.0f)
			{
				glm::vec4 color = (x == 0.0f) ? glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.1f);
				renderMgr.DrawLine(glm::vec2(x, 400.0f), glm::vec2(x, -400.0f), color);
			}

			for (float y = -400; y <= 400.0f; y += 10.0f)
			{
				glm::vec4 color = (y == 0.0f) ? glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.1f);
				renderMgr.DrawLine(glm::vec2(-500.0f, y), glm::vec2(500.0f, y), color);
			}

			TextureDrawOption option;
			option.blend = glm::vec3(1.0f, 0.0f, 0.0f);
			option.factor = 0.5f;
			renderMgr.DrawTextureAtlas(atlas_, "AlienBeige", glm::vec2(-200.0f, 0.0f), 66.0f, 92.0f, 0.0f, outline_, option_);
			renderMgr.DrawTextureAtlas(atlas_, "AlienBlue", glm::vec2(-100.0f, 0.0f), 66.0f, 92.0f, 0.0f, outline_, option_);
			renderMgr.DrawTextureAtlas(atlas_, "AlienGreen", glm::vec2(+100.0f, 0.0f), 66.0f, 92.0f, 0.0f, outline_, option_);
			renderMgr.DrawTextureAtlas(atlas_, "AlienPink", glm::vec2(+200.0f, 0.0f), 66.0f, 92.0f, 0.0f, outline_, option_);
		}
		renderMgr.End();
	}
	GLManager::GetRef().EndFrame();
}

void GameDevScene::Enter()
{
}

void GameDevScene::Exit()
{
}
