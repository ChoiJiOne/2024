#include "Entity/TitleFox.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

TitleFox::TitleFox()
{
	LoadAnimations();

	renderBound_ = Rect2D(glm::vec2(70.0f, -140.0f), glm::vec2(198.0f, 192.0f));

	shadow_.scale = 0.5f;
	shadow_.bound = renderBound_;
	shadow_.bound.size.y *= shadow_.scale;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
	shadow_.option.blend = glm::vec3(0.0f, 0.0f, 0.0f);
	shadow_.option.factor = 1.0f;
	shadow_.option.transparent = 0.3f;
	shadow_.option.bIsFlipV = true;

	speed_ = 500.0f;

	bIsInitialized_ = true;
}

TitleFox::~TitleFox()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TitleFox::Tick(float deltaSeconds)
{
	if (state_ == EState::RUN)
	{
		renderBound_.center += direction_ * speed_ * deltaSeconds;
		shadow_.bound.center = renderBound_.center;
		shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
	}

	animations_.at(state_)->Update(deltaSeconds);
}

void TitleFox::Render()
{
	TextureAtlas2D* textureAtlas = animations_.at(state_)->GetTextureAtlas();
	const std::string& clipName = animations_.at(state_)->GetCurrentClipName();

	renderManager_->DrawTextureAtlas(textureAtlas, clipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f, renderOption_);
	renderManager_->DrawTextureAtlas(textureAtlas, clipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}

void TitleFox::Release()
{
	CHECK(bIsInitialized_);

	UnloadAnimations();

	bIsInitialized_ = false;
}

void TitleFox::Reset()
{
	state_ = EState::IDLE;

	renderBound_ = Rect2D(glm::vec2(70.0f, -140.0f), glm::vec2(198.0f, 192.0f));
	shadow_.bound.center = renderBound_.center;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
}

void TitleFox::RunWayout()
{
	state_ = EState::RUN;
}

void TitleFox::LoadAnimations()
{
	TextureAtlas2D* textureAtlas = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

	std::vector<std::string> idleClipNames =
	{
		"Foxy_Idle_1",
		"Foxy_Idle_2",
		"Foxy_Idle_3",
		"Foxy_Idle_4",
	};
	SpriteAnimator2D* idleAnimation = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas, idleClipNames, 0.5f, true);
	animations_.insert({ EState::IDLE, idleAnimation });

	std::vector<std::string> runClipNames =
	{
		"Foxy_Run_1",
		"Foxy_Run_2",
		"Foxy_Run_3",
		"Foxy_Run_4",
		"Foxy_Run_5",
		"Foxy_Run_6",
	};
	SpriteAnimator2D* runAnimation = GLManager::GetRef().Create<SpriteAnimator2D>(textureAtlas, runClipNames, 0.5f, true);
	animations_.insert({ EState::RUN, runAnimation });
}

void TitleFox::UnloadAnimations()
{
	GLManager& glManager = GLManager::GetRef();
	for (auto& animation : animations_)
	{
		glManager.Destroy(animation.second);
	}
}