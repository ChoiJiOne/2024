#include "Entity/Coin.h"
#include "Entity/EntityManager.h"
#include "Entity/Fire.h"
#include "Entity/IObject.h"
#include "Entity/MiniMap.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "Entity/Potion.h"
#include "Entity/RandomChest.h"
#include "Entity/UICamera.h"
#include "GL/GLManager.h"
#include "GL/TextureAtlas2D.h"
#include "GLFW/GLFWManager.h"
#include "Utils/Assertion.h"

MiniMap::MiniMap(UICamera* uiCamera, RandomChest** randomChests, uint32_t countRandomChest)
	: uiCamera_(uiCamera)
	, randomChests_(countRandomChest)
{
	for (uint32_t index = 0; index < countRandomChest; ++index)
	{
		randomChests_[index] = randomChests[index];
	}

	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	player_ = EntityManager::GetRef().GetByName<Player>("Player");
	
	Playground* playground = EntityManager::GetRef().GetByName<Playground>("Playground");
	playgroundRadius_ = playground->GetSafeBound()->radius;

	glm::vec2 uiCameraSize = uiCamera_->GetSize() * 0.5f;
	float xoffset = 150.0f;
	float yoffset = 50.0f;
	renderBound_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(180.0f, 180.0f));
	renderBound_.center = glm::vec2(uiCameraSize.x, -uiCameraSize.y);
	renderBound_.center += glm::vec2(-renderBound_.size.x - xoffset, +renderBound_.size.y + yoffset) * 0.5f;

	worldScale_ = 0.35f;
	minimapRadius_ = renderBound_.size.x * worldScale_;
	pointSize_ = 6.0f;
	playerColor_ = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	coinColor_ = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	fireColor_ = glm::vec4(1.0f, 0.5f, 0.1f, 1.0f);
	redPotionColor_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	bluePotionColor_ = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	bIsInitialized_ = true;
}

MiniMap::~MiniMap()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MiniMap::Tick(float deltaSeconds)
{
	MinimapObject minimapPlayer;
	minimapPlayer.position = player_->GetCollider()->center / playgroundRadius_;
	minimapPlayer.position *= minimapRadius_;
	minimapPlayer.position += renderBound_.center;
	minimapPlayer.color = playerColor_;
	minimapObjects_.push(minimapPlayer);

	for (const auto& randomChest : randomChests_)
	{
		const std::list<IObject*>& objects = randomChest->GetObjects();
		for (const auto& object : objects)
		{
			MinimapObject minimapObject;
			ConvertMinimapObject(object, minimapObject);

			minimapObjects_.push(minimapObject);
		}
	}
}

void MiniMap::Render()
{
	renderManager_->DrawTextureAtlas(textureAtlas_, "MiniMap", renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f);

	while (!minimapObjects_.empty())
	{
		const MinimapObject& object = minimapObjects_.front();
		renderManager_->DrawPoint(object.position, object.color, pointSize_);
		minimapObjects_.pop();
	}
}

void MiniMap::Release()
{
	CHECK(bIsInitialized_);

	player_ = nullptr;
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

void MiniMap::ConvertMinimapObject(const IObject* object, MinimapObject& outMinimapObjec)
{
	const IObject::EType& type = object->GetType();

	switch (type)
	{
	case IObject::EType::COIN:
	{
		const Coin* coin = reinterpret_cast<const Coin*>(object);
		outMinimapObjec.position = coin->GetCollisionBound()->center / playgroundRadius_;
		outMinimapObjec.position *= minimapRadius_;
		outMinimapObjec.position += renderBound_.center;
		outMinimapObjec.color = coinColor_;
	}
	break;

	case IObject::EType::FIRE:
	{
		const Fire* fire = reinterpret_cast<const Fire*>(object);
		outMinimapObjec.position = fire->GetCollisionBound()->center / playgroundRadius_;
		outMinimapObjec.position *= minimapRadius_;
		outMinimapObjec.position += renderBound_.center;
		outMinimapObjec.color = fireColor_;
	}
	break;

	case IObject::EType::POTION:
	{
		const Potion* potion = reinterpret_cast<const Potion*>(object);
		outMinimapObjec.position = potion->GetCollisionBound()->center / playgroundRadius_;
		outMinimapObjec.position *= minimapRadius_;
		outMinimapObjec.position += renderBound_.center;

		const Potion::EColor& color = potion->GetColor();
		if (color == Potion::EColor::BLUE || color == Potion::EColor::BLUE_POWER)
		{
			outMinimapObjec.color = bluePotionColor_;
		}
		else
		{
			outMinimapObjec.color = redPotionColor_;
		}
	}
	break;
	}
}
