#include <array>

#include "Entity/EntityManager.h"
#include "Entity/KeyArrowPressViewer.h"
#include "Entity/Player.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TextureAtlas2D.h"
#include "Utils/Assertion.h"

KeyArrowPressViewer::KeyArrowPressViewer()
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	player_ = EntityManager::GetRef().GetByName<Player>("Player");

	KeyArrowState leftKeyArrowState;
	leftKeyArrowState.key = EKey::KEY_LEFT;
	leftKeyArrowState.press = EPress::NONE;
	leftKeyArrowState.renderBound = Rect2D(player_->GetCollider()->center, glm::vec2(32.0f, 32.0f));
	leftKeyArrowState.names.insert({ EPress::PRESSED,  "KeyArrowLeft_1" });
	leftKeyArrowState.names.insert({ EPress::HELD,     "KeyArrowLeft_1" });
	leftKeyArrowState.names.insert({ EPress::NONE,     "KeyArrowLeft_0" });
	leftKeyArrowState.names.insert({ EPress::RELEASED, "KeyArrowLeft_0" });

	KeyArrowState rightKeyArrowState;
	rightKeyArrowState.key = EKey::KEY_RIGHT;
	rightKeyArrowState.press = EPress::NONE;
	rightKeyArrowState.renderBound = Rect2D(player_->GetCollider()->center, glm::vec2(32.0f, 32.0f));
	rightKeyArrowState.names.insert({ EPress::PRESSED,  "KeyArrowRight_1" });
	rightKeyArrowState.names.insert({ EPress::HELD,     "KeyArrowRight_1" });
	rightKeyArrowState.names.insert({ EPress::NONE,     "KeyArrowRight_0" });
	rightKeyArrowState.names.insert({ EPress::RELEASED, "KeyArrowRight_0" });

	KeyArrowState upKeyArrowState;
	upKeyArrowState.key = EKey::KEY_UP;
	upKeyArrowState.press = EPress::NONE;
	upKeyArrowState.renderBound = Rect2D(player_->GetCollider()->center, glm::vec2(32.0f, 32.0f));
	upKeyArrowState.names.insert({ EPress::PRESSED,  "KeyArrowUp_1" });
	upKeyArrowState.names.insert({ EPress::HELD,     "KeyArrowUp_1" });
	upKeyArrowState.names.insert({ EPress::NONE,     "KeyArrowUp_0" });
	upKeyArrowState.names.insert({ EPress::RELEASED, "KeyArrowUp_0" });

	KeyArrowState downKeyArrowState;
	downKeyArrowState.key = EKey::KEY_DOWN;
	downKeyArrowState.press = EPress::NONE;
	downKeyArrowState.renderBound = Rect2D(player_->GetCollider()->center, glm::vec2(32.0f, 32.0f));
	downKeyArrowState.names.insert({ EPress::PRESSED,  "KeyArrowDown_1" });
	downKeyArrowState.names.insert({ EPress::HELD,     "KeyArrowDown_1" });
	downKeyArrowState.names.insert({ EPress::NONE,     "KeyArrowDown_0" });
	downKeyArrowState.names.insert({ EPress::RELEASED, "KeyArrowDown_0" });

	keyArrowStates_ =
	{
		leftKeyArrowState,
		rightKeyArrowState,
		upKeyArrowState,
		downKeyArrowState,
	};

	showTime_ = 10.0f;

	bIsInitialized_ = true;
}

KeyArrowPressViewer::~KeyArrowPressViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void KeyArrowPressViewer::Tick(float deltaSeconds)
{
	if (showTime_ <= 0.0f)
	{
		return;
	}

	showTime_ -= deltaSeconds;

	static const std::map<EKey, glm::vec2> KEY_POSITIONS =
	{
		{ EKey::KEY_LEFT,  glm::vec2(-30.0f, -100.0f) },
		{ EKey::KEY_RIGHT, glm::vec2(+30.0f, -100.0f) },
		{ EKey::KEY_UP,    glm::vec2(  0.0f,  -70.0f) },
		{ EKey::KEY_DOWN,  glm::vec2(  0.0f, -100.0f) },
	};

	for (auto& keyArrowState : keyArrowStates_)
	{
		keyArrowState.press = GLFWManager::GetRef().GetKeyPress(keyArrowState.key);

		Rect2D& renderBound = keyArrowState.renderBound;
		renderBound.center = player_->GetCollider()->center;
		renderBound.center += KEY_POSITIONS.at(keyArrowState.key);
	}
}

void KeyArrowPressViewer::Render()
{
	if (showTime_ <= 0.0f)
	{
		return;
	}

	for (const auto& keyArrowState : keyArrowStates_)
	{
		const Rect2D& renderBound = keyArrowState.renderBound;
		renderManager_->DrawTextureAtlas(textureAtlas_, keyArrowState.names.at(keyArrowState.press), renderBound.center, renderBound.size.x, renderBound.size.y, 0.0f);
	}
}

void KeyArrowPressViewer::Release()
{
	CHECK(bIsInitialized_);

	textureAtlas_ = nullptr;
	player_ = nullptr;

	bIsInitialized_ = false;
}
