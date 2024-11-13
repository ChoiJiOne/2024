#include "Entity/Background.h"
#include "Entity/Camera2D.h"
#include "Entity/EntityManager.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/GamePlayScene.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

GamePlayScene::GamePlayScene()
{
	glm::vec2 screenSize = glm::vec2(0.0f, 0.0f);
	GLFWManager::GetRef().GetWindowSize(screenSize.x, screenSize.y);

	mainCamera_ = EntityManager::GetRef().Create<Camera2D>(glm::vec2(0.0f, 0.0f), screenSize);
	background_ = EntityManager::GetRef().Create<Background>();
}

GamePlayScene::~GamePlayScene()
{
	EntityManager::GetRef().Destroy(background_);
	EntityManager::GetRef().Destroy(mainCamera_);
}

void GamePlayScene::Tick(float deltaSeconds)
{
	background_->Tick(deltaSeconds);
}

void GamePlayScene::Render()
{
	RenderManager2D& renderMgr = RenderManager2D::GetRef();

	GLManager::GetRef().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	{
		renderMgr.Begin(mainCamera_);
		{
			background_->Render();

	/*		for (float x = -500; x <= 500.0f; x += 10.0f)
			{
				glm::vec4 color = (x == 0.0f) ? glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.1f);
				renderMgr.DrawLine(glm::vec2(x, 400.0f), glm::vec2(x, -400.0f), color);
			}

			for (float y = -400; y <= 400.0f; y += 10.0f)
			{
				glm::vec4 color = (y == 0.0f) ? glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.1f);
				renderMgr.DrawLine(glm::vec2(-500.0f, y), glm::vec2(500.0f, y), color);
			}*/
		}
		renderMgr.End();
	}
	GLManager::GetRef().EndFrame();
}

void GamePlayScene::Enter()
{
}

void GamePlayScene::Exit()
{
}