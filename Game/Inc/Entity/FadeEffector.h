#pragma once

#include <glm/glm.hpp>

#include "Entity/IEntity.h"

/** ���̵� ȿ���� �����ϴ� ��ƼƼ�Դϴ�. */
class FadeEffector : public IEntity
{
public:
	FadeEffector();
	virtual ~FadeEffector();

	DISALLOW_COPY_AND_ASSIGN(FadeEffector);

	virtual void Tick(float deltaSeconds) override;
	virtual void Release() override;

	/** ���̵� �� ȿ��(ȭ���� ��ξ��ٰ� ������ �������)�� �����մϴ�. */
	void StartIn(float time);

	/** ���̵� �ƿ� ȿ��(ȭ���� ��Ҵٰ� ������ ��ξ�����)�� �����մϴ�. */
	void StartOut(float time);

	/** ���� ���̵� ȿ���� ���۵Ǿ����� Ȯ���մϴ�. */
	bool IsStart() const { return bIsStart_; }

	/** ���̵� ȿ���� ���� �� ������ ����ϴ�. */
	const glm::vec3& GetBlendColor() const { return blendColor_; }

	/** ���̵� ȿ���� ������ ������ ����ġ ���� ����ϴ�.  */
	float GetFactor() const { return factor_; }

private:
	/** ���̵� ȿ���� �����Դϴ�. */
	enum class EType
	{
		NONE     = 0x00,
		FADE_IN  = 0x01,
		FADE_OUT = 0x02,
	};

private:
	/** ���̵� ȿ�� ���� �� ������ ���ۿ� ������ �����Դϴ�. �� ������ ������ �����Դϴ�. */
	glm::vec3 blendColor_ = glm::vec3(0.0f, 0.0f, 0.0f);

	/**
	 * ���̵� ȿ�� ���� �� ������ ����ġ ���Դϴ�. 0.0�̸� ������ ȥ������ �ʰ�, 1.0�̸� ȥ�� ���� ǥ���մϴ�.
	 * 0.0 => Fade In
	 * 1.0 => Fade Out
	 */
	float factor_ = 0.0f;

	/** ���̵� ȿ�� ���� �ð� ���Դϴ�. */
	float effectTime_ = 0.0f;

	/** ���̵� ȿ�� ���� ��ü �ð� ���Դϴ�. */
	float maxEffectTime_ = 0.0f;

	/** ���� ���̵� ȿ���Դϴ�. */
	EType type_ = EType::NONE;

	/** ���̵� ȿ���� ���۵Ǿ����� Ȯ���մϴ�. */
	bool bIsStart_ = false;
};