#pragma once

#include <glm/glm.hpp>

#include "IEntity.h"

/**
 * 2D 카메라 엔티티입니다.
 * 2D 렌더링 시 반드시 필요한 엔티티입니다.
 */
class Camera2D : public IEntity
{
public:
	Camera2D() = default;
	Camera2D(const glm::vec2& center, const glm::vec2& size);
	virtual ~Camera2D();

	DISALLOW_COPY_AND_ASSIGN(Camera2D);

	/** 2D 카메라 엔티티를 업데이트합니다. */
	virtual void Tick(float deltaSeconds) override;

	/** 2D 카메라 엔티티의 초기화를 해제합니다. */
	virtual void Release() override;

	/** 2D 카메라 엔티티의 프로퍼티에 대한 Getter 입니다. */
	const glm::vec2& GetCenter() const { return center_; }
	const glm::vec2& GetSize() const { return size_; }
	const float& GetWidth() const { return size_.x; }
	const float& GetHeight() const { return size_.y; }
	const glm::mat4& GetOrtho() const { return ortho_; }

protected:
	/** 2D 카메라의 위치와 크기를 기반으로 직교 투영 행렬을 계산합니다. */
	glm::mat4 CalculateOrtho(const glm::vec2& center, const glm::vec2& size, float zNear = -1.0f, float zFar = 1.0f);

protected:
	/** 2D 카메라의 중심 위치입니다. */
	glm::vec2 center_;

	/** 2D 카메라의 가로/세로 크기입니다. */
	glm::vec2 size_;

	/** 2D 렌더링 시 참조할 카메라 크기에 대응하는 직교 투영 행렬입니다. */
	glm::mat4 ortho_;
};