#pragma once

#include "Collision2D.h"

class Block
{
public:
	Block() = default;
	Block(Block&& instance) noexcept
		: bound_(instance.bound_)
		, color_(instance.color_) {}
	Block(const Block& instance) noexcept
		: bound_(instance.bound_)
		, color_(instance.color_) {}
	Block(const Vec2f& center, const Vec2f& size, const Vec4f& color)
		: bound_(Rect2D(center, size))
		, color_(color) {}
	Block(const Rect2D& bound, const Vec4f& color)
		: bound_(bound)
		, color_(color) {}

	virtual ~Block();

	Block& operator=(Block&& instance) noexcept
	{
		if (this == &instance) return *this;

		bound_ = instance.bound_;
		color_ = instance.color_;

		return *this;
	}

	Block& operator=(const Block& instance) noexcept
	{
		if (this == &instance) return *this;

		bound_ = instance.bound_;
		color_ = instance.color_;

		return *this;
	}
	
private:
	Rect2D bound_;
	Vec4f color_;
};