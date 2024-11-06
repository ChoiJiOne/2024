#pragma once

#include <glm/glm.hpp>

#include "IEntity.h"

/**
 * 2D ī�޶� ��ƼƼ�Դϴ�.
 * 2D ������ �� �ݵ�� �ʿ��� ��ƼƼ�Դϴ�.
 */
class Camera2D : public IEntity
{
public:
	Camera2D() = default;
	Camera2D(const glm::vec2& center, const glm::vec2& size);
	virtual ~Camera2D();

	DISALLOW_COPY_AND_ASSIGN(Camera2D);

	/** 2D ī�޶� ��ƼƼ�� ������Ʈ�մϴ�. */
	virtual void Tick(float deltaSeconds) override;

	/** 2D ī�޶� ��ƼƼ�� �ʱ�ȭ�� �����մϴ�. */
	virtual void Release() override;

	/** 2D ī�޶� ��ƼƼ�� ������Ƽ�� ���� Getter �Դϴ�. */
	const glm::vec2& GetCenter() const { return center_; }
	const glm::vec2& GetSize() const { return size_; }
	const float& GetWidth() const { return size_.x; }
	const float& GetHeight() const { return size_.y; }
	const glm::mat4& GetOrtho() const { return ortho_; }

protected:
	/** 2D ī�޶��� ��ġ�� ũ�⸦ ������� ���� ���� ����� ����մϴ�. */
	glm::mat4 CalculateOrtho(const glm::vec2& center, const glm::vec2& size, float zNear = -1.0f, float zFar = 1.0f);

private:
	/** 2D ī�޶��� �߽� ��ġ�Դϴ�. */
	glm::vec2 center_;

	/** 2D ī�޶��� ����/���� ũ���Դϴ�. */
	glm::vec2 size_;

	/** 2D ������ �� ������ ī�޶� ũ�⿡ �����ϴ� ���� ���� ����Դϴ�. */
	glm::mat4 ortho_;
};