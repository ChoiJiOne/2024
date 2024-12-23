#include "Entity/EntityManager.h"
#include "Entity/Playground.h"
#include "Game/GameManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

Playground::Playground()
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");

	float radius = GameManager::GetRef().GetConfigValue<float>("Playground.radius");
	safeBound_ = Circle2D(glm::vec2(0.0f, 0.0f), radius);
	warnBound_ = Circle2D(glm::vec2(0.0f, 0.0f), radius + 50.0f);

	static const std::array<std::string, 6> TEXTURE_NAMES =
	{
		"Grass_1",
		"Grass_2",
		"Floor_1",
		"Floor_2",
		"Mushroom_1",
		"Mushroom_2",
	};

	for (auto& ornament : ornaments_)
	{
		int32_t randomIndex = GenerateRandomInt(0, TEXTURE_NAMES.size() - 1);

		ornament.name = TEXTURE_NAMES[randomIndex];
		ornament.rect.center = GenerateRandomDisk(safeBound_.radius);

		const TextureAtlas2D::Bound& bound = textureAtlas_->GetByName(TEXTURE_NAMES[randomIndex]);
		ornament.rect.size = glm::vec2(static_cast<float>(bound.w), static_cast<float>(bound.h)) * 2.0f;
	}

	outlineColor_ = glm::vec4(1.0f, 0.2f, 0.2f, 1.0f);

	bIsInitialized_ = true;
}

Playground::~Playground()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Playground::Tick(float deltaSeconds)
{
}

void Playground::Render()
{
	renderManager_->DrawCircleWireframe(warnBound_.center, warnBound_.radius, outlineColor_);

	for (const auto& ornament : ornaments_)
	{
		renderManager_->DrawTextureAtlas(textureAtlas_, ornament.name, ornament.rect.center, ornament.rect.size.x, ornament.rect.size.y, 0.0f);
	}
}

void Playground::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}
