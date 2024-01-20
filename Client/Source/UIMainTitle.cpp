#include "UIMainTitle.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"
#include "TTFont.h"
#include "Window.h"

UIMainTitle::~UIMainTitle()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIMainTitle::Initialize()
{
	int32_t width;
	int32_t height;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(width, height);

	float mainTitleWidth = 600.0f;
	float mainTitleHeight = 200.0f;

	Vector2f center = Vector2f(static_cast<float>(width) / 2.0f, mainTitleHeight);
	TTFont* font = ResourceManager::Get().GetResource<TTFont>("Font128");

	UIPanel::Initialize(
		mainTitleWidth, mainTitleHeight, center, L"Dodge3D", font,
		Vector3f(0.227f, 0.663f, 1.0f),
		Vector3f(0.094f, 0.122f, 0.165f),
		Vector3f(0.227f, 0.663f, 1.0f),
		0.9f
	);
}

void UIMainTitle::Tick(float deltaSeconds)
{
	center_ = GetCenterFromWindow();
}

Vector2f UIMainTitle::GetCenterFromWindow()
{
	int32_t windowWidth;
	int32_t windowHeight;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(windowWidth, windowHeight);

	return Vector2f(static_cast<float>(windowWidth) / 2.0f, height_);
}