#include "Entity/EntityManager.h"
#include "Entity/UIButton.h"
#include "Entity/UICamera.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

UIButton::UIButton(UICamera* uiCamera, TTFont* font)
	: uiCamera_(uiCamera)
	, font_(font)
{
	tickOrder_ = 1;
	renderOrder_ = 1;

	bIsInitialized_ = true;
}

UIButton::~UIButton()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIButton::Tick(float deltaSeconds)
{
}

void UIButton::Render()
{
	renderManager_->DrawRectWireframe(background_.center, background_.size.x, background_.size.y, glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), 0.0f);
}

void UIButton::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;
	uiCamera_ = nullptr;

	bIsInitialized_ = false;
}