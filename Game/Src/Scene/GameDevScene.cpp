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
#include "GL/SpriteAnimator2D.h"
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

	atlas_ = GLManager::GetRef().Create<TextureAtlas2D>("Resource\\texture.png", "Resource\\texture.atlas", Texture2D::EFilter::NEAREST);

	std::vector<std::string> names =
	{
		"idle-1",
		"idle-2",
		"idle-3",
		"idle-4",
	};
	animator_ = GLManager::GetRef().Create<SpriteAnimator2D>(atlas_, names, 0.3f, true);
}

GameDevScene::~GameDevScene()
{
	EntityManager::GetRef().Destroy(mainCamera_);
}

void GameDevScene::Tick(float deltaSeconds)
{
	animator_->Update(deltaSeconds);
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

			renderMgr.DrawTextureAtlas(animator_->GetTextureAtlas(), animator_->GetCurrentClipName(), glm::vec2(), 200.0f, 190.0f, 0.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
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
