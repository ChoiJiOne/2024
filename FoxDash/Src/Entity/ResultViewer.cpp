#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "Entity/ResultViewer.h"
#include "GL/GLManager.h"
#include "GL/RenderManager2D.h"
#include "GL/TTFont.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

ResultViewer::ResultViewer(TTFont* font, const glm::vec2& basePos, const std::wstring& text, const glm::vec4& textColor, float showTime)
	: font_(font)
	, basePos_(basePos)
	, text_(text)
	, textColor_(textColor)
	, maxResultShowTime_(showTime)
{
	shadowOffset_ = glm::vec2(+3.0f, -3.0f);
	shadowColor_ = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f);

	bIsInitialized_ = true;
}

ResultViewer::~ResultViewer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ResultViewer::Tick(float deltaSeconds)
{
	if (state_ == EState::WAIT || state_ == EState::DONE)
	{
		return;
	}

	resultShowTime_ += deltaSeconds;
	resultShowTime_ = glm::clamp<float>(resultShowTime_, 0.0f, maxResultShowTime_);

	float scale = resultShowTime_ / maxResultShowTime_;
	float playResult = static_cast<float>(playResult_);
	float currentPlayResult = glm::lerp<float>(0.0f, playResult, scale);

	if (currentPlayResult_ != static_cast<int32_t>(currentPlayResult))
	{
		currentPlayResult_ = static_cast<int32_t>(currentPlayResult);
		resultText_ = PrintF(L"%s: %d", text_.c_str(), currentPlayResult_);
	}

	if (resultShowTime_ >= maxResultShowTime_ && state_ == EState::ACTIVE)
	{
		state_ = EState::DONE;
	}
}

void ResultViewer::Render()
{
	if (state_ == EState::WAIT)
	{
		return;
	}

	renderManager_->DrawString(font_, resultText_, basePos_ + shadowOffset_, shadowColor_);
	renderManager_->DrawString(font_, resultText_, basePos_, textColor_);
}

void ResultViewer::Release()
{
	CHECK(bIsInitialized_);

	font_ = nullptr;

	bIsInitialized_ = false;
}

void ResultViewer::Start(int32_t playResult)
{
	state_ = EState::ACTIVE;
	resultShowTime_ = 0.0f;
	playResult_ = playResult;
	currentPlayResult_ = playResult_;
	resultText_ = PrintF(L"%s: %d", text_.c_str(), currentPlayResult_);
}