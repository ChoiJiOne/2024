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

	virtual ~Block() {}

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

	const Rect2D& GetBound() const { return bound_; }
	const Vec4f& GetColor() const { return color_; }

	void SetBound(const Rect2D& bound) { bound_ = bound; }
	void SetCenter(const Vec2f& center) { bound_.center = center; }
	void SetColor(const Vec4f& color) { color_ = color; }

private:
	Rect2D bound_;
	Vec4f color_;
};