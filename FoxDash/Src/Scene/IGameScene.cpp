#include "Audio/AudioManager.h"
#include "Crash/CrashManager.h"
#include "Entity/EntityManager.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GLFW/GLFWManager.h"
#include "Scene/SceneManager.h"

IGameScene::IGameScene()
{
	audioManager_ = AudioManager::GetPtr();
	crashManager_ = CrashManager::GetPtr();
	entityManager_ = EntityManager::GetPtr();
	gameManager_ = GameManager::GetPtr();
	glManager_ = GLManager::GetPtr();
	renderManager_ = RenderManager2D::GetPtr();
	glfwManager_ = GLFWManager::GetPtr();
	sceneManager_ = SceneManager::GetPtr();
}

IGameScene::~IGameScene()
{
	sceneManager_ = nullptr;
	glfwManager_ = nullptr;
	renderManager_ = nullptr;
	glManager_ = nullptr;
	gameManager_ = nullptr;
	entityManager_ = nullptr;
	crashManager_ = nullptr;
	audioManager_ = nullptr;
}