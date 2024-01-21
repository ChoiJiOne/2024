#include "GameScene.h"

#include "InputManager.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "StringUtils.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Window.h"

#include "BulletSpawner.h"
#include "EastWall.h"
#include "Floor.h"
#include "NorthWall.h"
#include "Player.h"
#include "SouthWall.h"
#include "WestWall.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Tick(float deltaSeconds)
{
	UpdateScene(deltaSeconds);

	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	RenderManager::Get().SetDepthMode(true);
	RenderDepthScene();
	RenderScene();
	RenderManager::Get().EndFrame();
}

void GameScene::EnterScene()
{
	sceneState_ = ESceneState::Ready;
	bIsCollisionToPlayer_ = false;

	LoadResources();
	LoadObjects();

	auto gameSceneResizeEvent = [&]()
	{
		int32_t bufferWidth;
		int32_t bufferHeight;
		RenderManager::Get().GetRenderTargetWindow()->GetSize(bufferWidth, bufferHeight);

		camera_->SetAspectRatio(static_cast<float>(bufferWidth) / static_cast<float>(bufferHeight));

		ResourceManager::Get().DestroyResource("GameScene_Framebuffer");
		framebuffer_ = ResourceManager::Get().CreateResource<Framebuffer>("GameScene_Framebuffer");
		framebuffer_->Initialize(bufferWidth, bufferHeight);
	};

	InputManager::Get().AddWindowEventAction("GameScene_ResizeEvent", EWindowEvent::Resize, gameSceneResizeEvent, true);
	InputManager::Get().AddWindowEventAction("GameScene_ExitMinimize", EWindowEvent::ExitMinimize, gameSceneResizeEvent, true);
	InputManager::Get().AddWindowEventAction("GameScene_EnterMaximize", EWindowEvent::EnterMaximize, gameSceneResizeEvent, true);
	InputManager::Get().AddWindowEventAction("GameScene_ExitMaximize", EWindowEvent::ExitMaximize, gameSceneResizeEvent, true);

	bulletRemoveEvent_ = [](Bullet* bullet)
	{
		return bullet->IsCollisionToPlayer() || bullet->IsCollisionToWall();
	};

	stepTime_ = 0.0f;
	fadeInStepTime_ = 1.0f;

	bIsEnterScene_ = true;
	bDetectSwitchScene_ = false;
}

void GameScene::ExitScene()
{
	InputManager::Get().DeleteWindowEventAction("GameScene_ResizeEvent");
	InputManager::Get().DeleteWindowEventAction("GameScene_ExitMinimize");
	InputManager::Get().DeleteWindowEventAction("GameScene_EnterMaximize");
	InputManager::Get().DeleteWindowEventAction("GameScene_ExitMaximize");

	bIsEnterScene_ = false;
}

void GameScene::LoadResources()
{
	shadowMap_ = ResourceManager::Get().GetResource<ShadowMap>("GameScene_ShadowMap");
	if(!shadowMap_)
	{
		shadowMap_ = ResourceManager::Get().CreateResource<ShadowMap>("GameScene_ShadowMap");
		shadowMap_->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);
	}

	framebuffer_ = ResourceManager::Get().GetResource<Framebuffer>("GameScene_Framebuffer");
	if (!framebuffer_)
	{
		int32_t bufferWidth;
		int32_t bufferHeight;
		RenderManager::Get().GetRenderTargetWindow()->GetSize(bufferWidth, bufferHeight);

		framebuffer_ = ResourceManager::Get().CreateResource<Framebuffer>("GameScene_Framebuffer");
		framebuffer_->Initialize(bufferWidth, bufferHeight);
	}

	shadowShader_ = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
	lightShader_ = ResourceManager::Get().GetResource<LightShader>("LightShader");
	grayscaleEffectShader_ = ResourceManager::Get().GetResource<PostEffectShader>("GrayscaleEffect");
	fadeEffectShader_ = ResourceManager::Get().GetResource<PostEffectShader>("FadeEffect");
}

void GameScene::LoadObjects()
{
	camera_ = ObjectManager::Get().CreateObject<MovableCamera>("MainCamera");
	camera_->Initialize();

	light_ = ObjectManager::Get().CreateObject<StaticLight>("GlobalLight");
	light_->Initialize();

	player_ = ObjectManager::Get().CreateObject<Player>("Player");
	player_->Initialize();

	floor_ = ObjectManager::Get().CreateObject<Floor>("Floor");
	floor_->Initialize();

	northWall_ = ObjectManager::Get().CreateObject<NorthWall>("NorthWall");
	northWall_->Initialize();

	southWall_ = ObjectManager::Get().CreateObject<SouthWall>("SouthWall");
	southWall_->Initialize();

	westWall_ = ObjectManager::Get().CreateObject<WestWall>("WestWall");
	westWall_->Initialize();

	eastWall_ = ObjectManager::Get().CreateObject<EastWall>("EastWall");
	eastWall_->Initialize();

	bulletSpawner0_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_0");
	bulletSpawner0_->Initialize(
		Vector3f(-4.0f, 0.5f, +4.0f), 
		1.5f, 
		[&]() {
			Bullet* bullet = ObjectManager::Get().CreateObject<Bullet>(StringUtils::PrintF("Bullet_%d", countOfbullet_++));
			Vector3f direction = MathUtils::Normalize(player_->GetTransform().GetLocation() - bulletSpawner0_->GetTransform().GetLocation());
			float speed = MathUtils::GenerateRandomFloat(2.0f, 5.0f);

			bullet->Initialize(bulletSpawner0_->GetTransform().GetLocation(), direction, speed, 0.2f);
			bullets_.push_back(bullet);
		}
	);

	bulletSpawner1_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_1");
	bulletSpawner1_->Initialize(
		Vector3f(+4.0f, 0.5f, +4.0f), 
		1.0f, 
		[&]() 
		{
			Bullet* bullet = ObjectManager::Get().CreateObject<Bullet>(StringUtils::PrintF("Bullet_%d", countOfbullet_++));
			Vector3f direction = MathUtils::Normalize(player_->GetTransform().GetLocation() - bulletSpawner1_->GetTransform().GetLocation());
			float speed = MathUtils::GenerateRandomFloat(2.0f, 5.0f);

			bullet->Initialize(bulletSpawner1_->GetTransform().GetLocation(), direction, speed, 0.2f);
			bullets_.push_back(bullet);
		}
	);

	bulletSpawner2_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_2");
	bulletSpawner2_->Initialize(
		Vector3f(+4.0f, 0.5f, -4.0f), 
		1.5f, 
		[&]() 
		{
			Bullet* bullet = ObjectManager::Get().CreateObject<Bullet>(StringUtils::PrintF("Bullet_%d", countOfbullet_++));
			Vector3f direction = MathUtils::Normalize(player_->GetTransform().GetLocation() - bulletSpawner2_->GetTransform().GetLocation());
			float speed = MathUtils::GenerateRandomFloat(2.0f, 5.0f);

			bullet->Initialize(bulletSpawner2_->GetTransform().GetLocation(), direction, speed, 0.2f);
			bullets_.push_back(bullet);
		}
	);

	bulletSpawner3_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_3");
	bulletSpawner3_->Initialize(
		Vector3f(-4.0f, 0.5f, -4.0f), 
		1.0f, 
		[&]() {
			Bullet* bullet = ObjectManager::Get().CreateObject<Bullet>(StringUtils::PrintF("Bullet_%d", countOfbullet_++));
			Vector3f direction = MathUtils::Normalize(player_->GetTransform().GetLocation() - bulletSpawner3_->GetTransform().GetLocation());
			float speed = MathUtils::GenerateRandomFloat(2.0f, 5.0f);

			bullet->Initialize(bulletSpawner3_->GetTransform().GetLocation(), direction, speed, 0.2f);
			bullets_.push_back(bullet);
		}
	);

	board_ = ObjectManager::Get().CreateObject<UIBoard>("Board");
	board_->Initialize();

	renderObjects_ = {
		floor_,
		northWall_,
		southWall_,
		westWall_,
		eastWall_,
		bulletSpawner0_,
		bulletSpawner1_,
		bulletSpawner2_,
		bulletSpawner3_,
		player_,
	};
}

void GameScene::UpdateScene(float deltaSeconds)
{
	if (sceneState_ == ESceneState::Ready)
	{
		stepTime_ += deltaSeconds;
		stepTime_ = MathUtils::Clamp<float>(stepTime_, 0.0f, fadeInStepTime_);

		if (stepTime_ >= fadeInStepTime_)
		{
			stepTime_ = 0.0f;
			sceneState_ = ESceneState::Play;
		}

		camera_->Tick(deltaSeconds);
		return;
	}

	if (sceneState_ == ESceneState::Done)
	{
		board_->Tick(deltaSeconds);
		return;
	}

	player_->Tick(deltaSeconds);
	camera_->Tick(deltaSeconds);

	bulletSpawner0_->Tick(deltaSeconds);
	bulletSpawner1_->Tick(deltaSeconds);
	bulletSpawner2_->Tick(deltaSeconds);
	bulletSpawner3_->Tick(deltaSeconds);

	bIsCollisionToPlayer_ = false;
	for (auto& bullet : bullets_)
	{
		bullet->Tick(deltaSeconds);

		if (bullet->IsCollisionToPlayer())
		{
			bIsCollisionToPlayer_ = true;
		}
	}

	board_->Tick(deltaSeconds);

	if (player_->GetHP() <= 0)
	{
		sceneState_ = ESceneState::Done;
	}
	
	bullets_.remove_if(bulletRemoveEvent_);
}

void GameScene::RenderDepthScene()
{
	RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	shadowMap_->Bind();
	shadowMap_->Clear();

	shadowShader_->Bind();
	shadowShader_->SetLight(light_);

	for (const auto& object : renderObjects_)
	{
		shadowShader_->DrawMesh3D(object->GetTransform().GetWorldMatrix(), object->GetMesh());
	}

	for (const auto& bullet : bullets_)
	{
		shadowShader_->DrawMesh3D(bullet->GetTransform().GetWorldMatrix(), bullet->GetMesh());
	}

	shadowShader_->Unbind();
	shadowMap_->Unbind();
}

void GameScene::RenderScene()
{
	RenderManager::Get().SetWindowViewport();

	if (sceneState_ == ESceneState::Done || sceneState_ == ESceneState::Ready)
	{
		framebuffer_->Bind();
		framebuffer_->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	}

	lightShader_->Bind();
	lightShader_->SetLight(light_);
	lightShader_->SetCamera(camera_);

	for (const auto& object : renderObjects_)
	{
		lightShader_->SetMaterial(object->GetMaterial());
		lightShader_->DrawMesh3D(object->GetTransform().GetWorldMatrix(), object->GetMesh(), shadowMap_);
	}

	for (const auto& bullet : bullets_)
	{
		lightShader_->DrawMesh3D(bullet->GetTransform().GetWorldMatrix(), bullet->GetMesh(), shadowMap_);
	}

	lightShader_->Unbind();
	
	player_->RenderHP(camera_);
	bulletSpawner0_->RenderRespawnTime(camera_);
	bulletSpawner1_->RenderRespawnTime(camera_);
	bulletSpawner2_->RenderRespawnTime(camera_);
	bulletSpawner3_->RenderRespawnTime(camera_);

	if (sceneState_ == ESceneState::Done || sceneState_ == ESceneState::Ready)
	{
		framebuffer_->Unbind();

		if (sceneState_ == ESceneState::Done)
		{
			grayscaleEffectShader_->Bind();
			grayscaleEffectShader_->BlitEffect(framebuffer_);
			grayscaleEffectShader_->Unbind();
		}
		else // sceneState_ == ESceneState::Ready
		{
			float fadeBias = MathUtils::Clamp<float>(stepTime_ / fadeInStepTime_, 0.0f, 1.0f);

			fadeEffectShader_->Bind();
			fadeEffectShader_->SetUniform("fadeBias", fadeBias);
			fadeEffectShader_->BlitEffect(framebuffer_);
			fadeEffectShader_->Unbind();
		}

		return;
	}
	
	board_->Render();
}