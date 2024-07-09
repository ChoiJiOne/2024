#include <array>

#include "Assertion.h"
#include "Collision2D.h"

using namespace GameMaker;

/** ���� �� ������ �浹 ó�� */
bool IsCollision(const Point2D* point0, const Point2D* point1)
{
	return point0->center == point1->center;
}

/** ���� �� ������ �浹 ó�� */
bool IsCollision(const Point2D* point, const Line2D* line)
{
	if (NearZero(line->start.x - line->end.x)) /** Case 1. ������ y��� ���� */
	{
		float minY = Min<float>(line->start.y, line->end.y);
		float maxY = Max<float>(line->start.y, line->end.y);

		return NearZero(line->start.x - point->center.x) && (minY <= point->center.y && point->center.y <= maxY);
	}
	else if (NearZero(line->start.y - line->end.y)) /** Case 2. ������ x��� ���� */
	{
		float minX = Min<float>(line->start.x, line->end.x);
		float maxX = Max<float>(line->start.x, line->end.x);

		return NearZero(line->start.y - point->center.y) && (minX <= point->center.x && point->center.x <= maxX);
	}
	else /** Case 3. �� �̿��� ��� ��� */
	{
		float m = (line->end.y - line->start.y) / (line->end.x - line->start.x);
		float y = line->start.y + m * (point->center.x - line->start.x); /** ������ �����Ŀ� ���� */

		return NearZero(y - point->center.y);
	}
}

/** ���� �� ������ �浹 ó�� */
bool IsCollision(const Point2D* point, const Circle2D* circle)
{
	float d2 = Vec2f::LengthSq(point->center - circle->center);
	float r2 = circle->radius * circle->radius;

	return (d2 <= r2);
}

/** ���� AABB ������ �浹 ó�� */
bool IsCollision(const Point2D* point, const Rect2D* rect)
{
	Vec2f minPos = rect->GetMin();
	Vec2f maxPos = rect->GetMax();

	return (minPos.x <= point->center.x && point->center.x <= maxPos.x) && (minPos.y <= point->center.y && point->center.y <= maxPos.y);
}

/** ���� OBB ������ �浹 ó�� */
bool IsCollision(const Point2D* point, const OrientedRect2D* orientedRect)
{
	Vec2f targetPos = point->center - orientedRect->center;
	float rotate = -orientedRect->rotate;

	Mat2x2 roateMat(Cos(rotate), -Sin(rotate), Sin(rotate), Cos(rotate));
	targetPos = roateMat * targetPos;

	Vec2f minPos = -orientedRect->size * 0.5f;
	Vec2f maxPos = orientedRect->size * 0.5f;

	return (minPos.x <= targetPos.x && targetPos.x <= maxPos.x) && (minPos.y <= targetPos.y && targetPos.y <= maxPos.y);
}

/** ���� �� ������ �浹 ó�� */
bool IsCollision(const Line2D* line0, const Line2D* line1)
{
	Vec2f p1 = line0->start;
	Vec2f p2 = line0->end;
	Vec2f p3 = line1->start;
	Vec2f p4 = line1->end;

	Vec2f p12 = p2 - p1;
	Vec2f p34 = p4 - p3;
	Vec2f p31 = p1 - p3;

	float cross = Vec2f::Cross(p12, p34);
	if (NearZero(cross)) /** �� ������ ���� ������ ���. */
	{
		static auto checkBound = [](const Vec2f& minPos, const Vec2f& maxPos, const Vec2f& pos)->bool
			{
				float minX = Min<float>(minPos.x, maxPos.x);
				float minY = Min<float>(minPos.y, maxPos.y);
				float maxX = Max<float>(minPos.x, maxPos.x);
				float maxY = Max<float>(minPos.y, maxPos.y);

				return (minX <= pos.x && pos.x <= maxX) && (minY <= pos.y && pos.y <= maxY);
			};

		return (checkBound(p1, p2, p3) || checkBound(p1, p2, p4) || checkBound(p3, p4, p1) || checkBound(p3, p4, p2));
	}
	else /** �׷��� ���� ��� ��� */
	{
		float uA = Vec2f::Cross(p34, p31) / cross;
		float uB = Vec2f::Cross(p12, p31) / cross;
		return (uA >= 0.0f && uA <= 1.0f && uB >= 0.0f && uB <= 1.0f);
	}
}

/** ���� �� ������ �浹 ó�� */
bool IsCollision(const Line2D* line, const Circle2D* circle)
{
	static auto checkCircleBound = [](const Circle2D* circle, const Vec2f& pos)->bool
		{
			float dist2 = Vec2f::LengthSq(pos - circle->center);
			float r2 = circle->radius * circle->radius;
			return dist2 <= r2;
		};

	if (checkCircleBound(circle, line->start) || checkCircleBound(circle, line->end))
	{
		return true;
	}

	Vec2f d = line->end - line->start;
	float t = Vec2f::Dot(circle->center - line->start, d) / Vec2f::Dot(d, d);
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}

	Vec2f pos = line->start + d * t;
	pos = pos - circle->center;
	float r2 = circle->radius * circle->radius;

	return Vec2f::LengthSq(pos) <= r2;
}

/** ���� AABB ������ �浹 ó�� */
bool IsCollision(const Line2D* line, const Rect2D* rect)
{
	Vec2f minPos = rect->GetMin();
	Vec2f maxPos = rect->GetMax();
	std::array<Line2D, 4> targetLines =
	{
		Line2D(Vec2f(minPos.x, minPos.y), Vec2f(maxPos.x, minPos.y)),
		Line2D(Vec2f(maxPos.x, minPos.y), Vec2f(maxPos.x, maxPos.y)),
		Line2D(Vec2f(maxPos.x, maxPos.y), Vec2f(minPos.x, maxPos.y)),
		Line2D(Vec2f(minPos.x, maxPos.y), Vec2f(minPos.x, minPos.y)),
	};

	for (const auto& targetLine : targetLines)
	{
		if (IsCollision(line, &targetLine))
		{
			return true;
		}
	}

	return false;
}

/** ���� OBB ������ �浹 ó�� */
bool IsCollision(const Line2D* line, const OrientedRect2D* orientedRect)
{
	float rotate = -orientedRect->rotate;
	Mat2x2 roateMat(Cos(rotate), -Sin(rotate), Sin(rotate), Cos(rotate));

	Vec2f start = roateMat * (line->start - orientedRect->center);
	Vec2f end = roateMat * (line->end - orientedRect->center);

	Line2D targetLine(start, end);
	Rect2D targetRect(Vec2f(0.0f, 0.0f), orientedRect->size);

	return IsCollision(&targetLine, &targetRect);
}

/** ���� �� ������ �浹 ó�� */
bool IsCollision(const Circle2D* circle0, const Circle2D* circle1)
{
	float dist = Vec2f::LengthSq(circle1->center - circle0->center);
	float radiusSum = circle0->radius + circle1->radius;

	return dist <= radiusSum * radiusSum;
}

/** ���� AABB ������ �浹 ó�� */
bool IsCollision(const Circle2D* circle, const Rect2D* rect)
{
	Vec2f minPos = rect->GetMin();
	Vec2f maxPos = rect->GetMax();
	Vec2f closest(Clamp<float>(circle->center.x, minPos.x, maxPos.x), Clamp<float>(circle->center.y, minPos.y, maxPos.y));

	float dist = Vec2f::LengthSq(closest - circle->center);
	float r2 = circle->radius * circle->radius;

	return dist <= r2;
}

/** ���� OBB ������ �浹 ó�� */
bool IsCollision(const Circle2D* circle, const OrientedRect2D* orientedRect)
{
	float rotate = -orientedRect->rotate;
	Mat2x2 roateMat(Cos(rotate), -Sin(rotate), Sin(rotate), Cos(rotate));

	Vec2f center = roateMat * (circle->center - orientedRect->center);

	Circle2D targetCircle(center, circle->radius);
	Rect2D targetRect(Vec2f(0.0f, 0.0f), orientedRect->size);
	
	return IsCollision(&targetCircle, &targetRect);
}

/** AABB�� AABB ������ �浹 ó�� */
bool IsCollision(const Rect2D* rect0, const Rect2D* rect1)
{
	Vec2f minPos0 = rect0->GetMin();
	Vec2f maxPos0 = rect0->GetMax();
	Vec2f minPos1 = rect1->GetMin();
	Vec2f maxPos1 = rect1->GetMax();

	bool bIsOverlapX = ((minPos1.x <= maxPos0.x) && (minPos0.x <= maxPos1.x));
	bool bIsOverlapY = ((minPos1.y <= maxPos0.y) && (minPos0.y <= maxPos1.y));

	return bIsOverlapX && bIsOverlapY;
}

/** AABB�� OBB ������ �浹 ó�� */
bool IsCollision(const Rect2D* rect, const OrientedRect2D* orientedRect)
{
	float rotate = orientedRect->rotate;
	Mat2x2 roateMat(Cos(rotate), -Sin(rotate), Sin(rotate), Cos(rotate));

	Vec2f axis0(orientedRect->size.x * 0.5f, 0.0f);
	Vec2f axis1(0.0f, orientedRect->size.y * 0.5f);

	axis0 = roateMat * Vec2f::Normalize(axis0);
	axis1 = roateMat * Vec2f::Normalize(axis1);

	std::array<Vec2f, 4> separateAxis =
	{
		Vec2f(1.0f, 0.0f),
		Vec2f(0.0f, 1.0f),
		roateMat * Vec2f::Normalize(axis0),
		roateMat * Vec2f::Normalize(axis1),
	};

	//for (const auto& axis : separateAxis)
	//{

	//}

	return false;
}

/** OBB�� OBB ������ �浹 ó�� */
bool IsCollision(const OrientedRect2D* orientedRect0, const OrientedRect2D* orientedRect1)
{
	return false;
}

bool Point2D::Intersect(const ICollision2D* target) const
{
	CHECK(target != nullptr);

	EType type = target->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollision2D::EType::POINT:
	{
		const Point2D* other = reinterpret_cast<const Point2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::CIRCLE: 
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::RECT:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::ORIENTED_RECT:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}
	break;

	default: break;// ICollision2D::EType::NONE:
	}

	return bIsIntersect;
}

bool Line2D::Intersect(const ICollision2D* target) const
{
	CHECK(target != nullptr);

	EType type = target->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollision2D::EType::POINT:
	{
		const Point2D* other = reinterpret_cast<const Point2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::CIRCLE:
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::RECT:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::ORIENTED_RECT:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	default: break;// ICollision2D::EType::NONE:
	}

	return bIsIntersect;
}

bool Circle2D::Intersect(const ICollision2D* target) const
{
	CHECK(target != nullptr);

	EType type = target->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollision2D::EType::POINT:
	{
		const Point2D* other = reinterpret_cast<const Point2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::CIRCLE:
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::RECT:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::ORIENTED_RECT:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	default: break;// ICollision2D::EType::NONE:
	}

	return bIsIntersect;
}

bool Rect2D::Intersect(const ICollision2D* target) const
{
	CHECK(target != nullptr);

	EType type = target->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollision2D::EType::POINT:
	{
		const Point2D* other = reinterpret_cast<const Point2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::CIRCLE:
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::RECT:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	case ICollision2D::EType::ORIENTED_RECT:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	default: break;// ICollision2D::EType::NONE:
	}

	return bIsIntersect;
}

void Rect2D::GetInterval(const Vec2f& axis, float& outMin, float& outMax)
{
	Vec2f minPos = GetMin();
	Vec2f maxPos = GetMax();

	std::array<Vec2f, 4> vertices =
	{
		Vec2f(minPos.x, minPos.y),
		Vec2f(minPos.x, maxPos.y),
		Vec2f(maxPos.x, maxPos.y),
		Vec2f(maxPos.x, minPos.y),
	};
	
	outMin = +FLT_MAX;
	outMax = -FLT_MAX;

	for (int32_t index = 0; index < vertices.size(); ++index)
	{
		float projection = Vec2f::Dot(axis, vertices[index]);

		if (projection < outMin)
		{
			outMin = projection;
		}

		if (projection > outMax)
		{
			outMax = projection;
		}
	}
}

bool OrientedRect2D::Intersect(const ICollision2D* target) const
{
	CHECK(target != nullptr);

	EType type = target->GetType();
	bool bIsIntersect = false;

	switch (type)
	{
	case ICollision2D::EType::POINT:
	{
		const Point2D* other = reinterpret_cast<const Point2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::LINE:
	{
		const Line2D* other = reinterpret_cast<const Line2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::CIRCLE:
	{
		const Circle2D* other = reinterpret_cast<const Circle2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::RECT:
	{
		const Rect2D* other = reinterpret_cast<const Rect2D*>(target);
		bIsIntersect = IsCollision(other, this);
		break;
	}

	case ICollision2D::EType::ORIENTED_RECT:
	{
		const OrientedRect2D* other = reinterpret_cast<const OrientedRect2D*>(target);
		bIsIntersect = IsCollision(this, other);
		break;
	}

	default: break;// ICollision2D::EType::NONE:
	}

	return bIsIntersect;
}

void OrientedRect2D::GetInterval(const Vec2f& axis, float& outMin, float& outMax)
{
	Rect2D rect(center, size);
	Vec2f minPos = rect.GetMin();
	Vec2f maxPos = rect.GetMax();

	std::array<Vec2f, 4> vertices =
	{
		Vec2f(minPos.x, minPos.y),
		Vec2f(minPos.x, maxPos.y),
		Vec2f(maxPos.x, maxPos.y),
		Vec2f(maxPos.x, minPos.y),
	};

	Mat2x2 roateMat(Cos(rotate), -Sin(rotate), Sin(rotate), Cos(rotate));
	for (int32_t index = 0; index < vertices.size(); ++index)
	{
		Vec2f targetPos = roateMat * (vertices[index] - center);
		vertices[index] = targetPos + center;
	}

	outMin = +FLT_MAX;
	outMax = -FLT_MAX;

	for (int32_t index = 0; index < vertices.size(); ++index)
	{
		float projection = Vec2f::Dot(axis, vertices[index]);

		if (projection < outMin)
		{
			outMin = projection;
		}

		if (projection > outMax)
		{
			outMax = projection;
		}
	}

}
