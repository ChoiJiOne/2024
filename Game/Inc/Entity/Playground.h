#pragma once

#include <array>
#include <map>

#include "Entity/IEntity2D.h"
#include "Physic/Circle2D.h"
#include "Physic/Rect2D.h"

class TextureAtlas2D;

/** �÷��̾��� �÷��� ������ ��Ÿ���� ��ƼƼ�Դϴ�. */
class Playground : public IEntity2D
{
public:
	Playground();
	virtual ~Playground();

	DISALLOW_COPY_AND_ASSIGN(Playground);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ������ ������ ����ϴ�. */
	Circle2D* GetSafeBound() { return &safeBound_; }

	/** ������ ������ ����ϴ�. */
	Circle2D* GetWarnBound() { return &warnBound_; }

private:
	/** �÷��� ���� ���� ��Ĺ��Դϴ�. */
	struct Ornament
	{
		std::string name;
		Rect2D rect;
	};

private:
	/** �÷��̱׶��� ���� ��Ĺ� �������� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ���� �����Դϴ�. */
	Circle2D safeBound_;

	/** ������ �����Դϴ�. */
	Circle2D warnBound_;

	/** �÷��� ������ ��Ȯ�ϰ� ǥ���ϱ� ���� �����Դϴ�. */
	glm::vec4 outlineColor_;

	/** �÷��� ���� ���� �ִ� ��Ĺ� �����Դϴ�. */
	static const uint32_t MAX_COUNT_ORNAMENT = 100;

	/** �÷��� ���� ���� ��Ĺ����Դϴ�. */
	std::array<Ornament, MAX_COUNT_ORNAMENT> ornaments_;
};