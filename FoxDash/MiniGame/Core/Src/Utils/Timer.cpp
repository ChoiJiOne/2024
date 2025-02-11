#include <glfw/glfw3.h>

#include "Utils/Timer.h"

Timer::Timer(Timer&& instance) noexcept
	: bIsStop_(instance.bIsStop_)
	, baseTime_(instance.baseTime_)
	, pausedTime_(instance.pausedTime_)
	, stopTime_(instance.stopTime_)
	, prevTime_(instance.prevTime_)
	, currTime_(instance.currTime_) {}

Timer::Timer(const Timer& instance) noexcept
	: bIsStop_(instance.bIsStop_)
	, baseTime_(instance.baseTime_)
	, pausedTime_(instance.pausedTime_)
	, stopTime_(instance.stopTime_)
	, prevTime_(instance.prevTime_)
	, currTime_(instance.currTime_) {}

Timer& Timer::operator=(Timer&& instance) noexcept
{
	if (this == &instance) return *this;

	bIsStop_ = instance.bIsStop_;
	baseTime_ = instance.baseTime_;
	pausedTime_ = instance.pausedTime_;
	stopTime_ = instance.stopTime_;
	prevTime_ = instance.prevTime_;
	currTime_ = instance.currTime_;

	return *this;
}

Timer& Timer::operator=(const Timer& instance) noexcept
{
	if (this == &instance) return *this;

	bIsStop_ = instance.bIsStop_;
	baseTime_ = instance.baseTime_;
	pausedTime_ = instance.pausedTime_;
	stopTime_ = instance.stopTime_;
	prevTime_ = instance.prevTime_;
	currTime_ = instance.currTime_;

	return *this;
}

float Timer::GetDeltaSeconds() const
{
	if (bIsStop_)
	{
		return 0.0f;
	}
	else
	{
		return currTime_ - prevTime_;
	}
}

float Timer::GetTotalSeconds() const
{
	if (bIsStop_)
	{
		return (stopTime_ - pausedTime_ - baseTime_);
	}
	else
	{
		return (currTime_ - pausedTime_ - baseTime_);
	}
}

void Timer::Reset()
{
	float tickTime = static_cast<float>(glfwGetTime());
	
	bIsStop_ = false;
	baseTime_ = tickTime;
	pausedTime_ = 0.0f;
	stopTime_ = 0.0f;
	prevTime_ = tickTime;
	currTime_ = tickTime;
}

void Timer::Start()
{
	if (bIsStop_)
	{
		float tickTime = static_cast<float>(glfwGetTime());

		pausedTime_ += (tickTime - stopTime_);
		prevTime_ = tickTime;
		stopTime_ = 0.0f;

		bIsStop_ = false;
	}
}

void Timer::Stop()
{
	if (!bIsStop_)
	{
		stopTime_ = static_cast<float>(glfwGetTime());
		bIsStop_ = true;
	}
}

void Timer::Tick()
{
	prevTime_ = currTime_;
	currTime_ = static_cast<float>(glfwGetTime());
}