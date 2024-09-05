#include "Assertion.h"
#include "Atlas2D.h"
#include "Camera2D.h"
#include "EntityManager.h"
#include "RenderManager2D.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "Background.h"
#include "Camera.h"
#include "GameApp.h"

GameApp::GameApp() : IApp("Runner2D", 100, 100, 800, 600, false, false)
{
}

GameApp::~GameApp()
{
}

void GameApp::Startup()
{
	LoadResource();

	camera_ = EntityManager::Get().Create<Camera>();
	
	Background* background = EntityManager::Get().Create<Background>(camera_);
	entities_.push_back(background);
}

void GameApp::Shutdown()
{
	EntityManager::Get().Destroy(camera_);
	camera_ = nullptr;
}

void GameApp::Run()
{
	RunLoop(
		[&](float deltaSeconds)
		{
			camera_->Tick(deltaSeconds);

			for (auto& entity : entities_)
			{
				entity->Tick(deltaSeconds);
			}

			BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderManager2D::Get().Begin(camera_);
			{
				for (auto& entity : entities_)
				{
					entity->Render();
				}
			}
			RenderManager2D::Get().End();
			EndFrame();
		}
	);
}

void GameApp::LoadResource()
{
	resourceRootPath_ = "Runner2D\\Res\\";

	Texture2D* background = ResourceManager::Get().Create<Texture2D>(resourceRootPath_ + "Texture\\Background.png", Texture2D::Filter::NEAREST);
	ResourceManager::Get().Register("Background", background);

	Atlas2D* floor = ResourceManager::Get().Create<Atlas2D>(
		resourceRootPath_ + "Atlas\\Floor\\Floor.png",
		resourceRootPath_ + "Atlas\\Floor\\Floor.json",
		Texture2D::Filter::NEAREST
	);
	ResourceManager::Get().Register("Floor", floor);
}