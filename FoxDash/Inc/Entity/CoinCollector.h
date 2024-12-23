#pragma once

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class Player;
class PlayerFollowCamera;
class TextureAtlas2D;
class TTFont;

/** ������ �����ϰ�, �÷��̾ ȹ���� ������ ���¸� ǥ���ϴ� ��ƼƼ�Դϴ�. */
class CoinCollector : public IEntity2D
{
public:
	CoinCollector(TTFont* font);
	virtual ~CoinCollector();

	DISALLOW_COPY_AND_ASSIGN(CoinCollector);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	/** ���� �ݷ����� �浹 ������ ����ϴ�. */
	const Rect2D* GetCollider() const { return &background_; }

private:
	/** ������ ȹ���ϴ� �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** ���� �ݷ��͸� �������� �� ������ ī�޶��Դϴ�. */
	PlayerFollowCamera* playerFollowCamera_ = nullptr;

	/** ���� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** �ؽ�Ʈ ������ �� ������ ��Ʈ ���ҽ��Դϴ�. */
	TTFont* font_ = nullptr;

	/** ī�޶� ������ ������ ��ġ ���Դϴ�. */
	glm::vec2 offset_ = glm::vec2(0.0f, 0.0f);

	/** ��׶��� �����Դϴ�. */
	Rect2D background_;

	/** ������ ��ġ�Դϴ�. */
	Rect2D coin_;

	/** ���� �ݷ��Ͱ� �����ϴ� ���� ���Դϴ�. */
	int32_t countCoin_ = 0;

	/** ȹ���� ������ ǥ���� �ؽ�Ʈ�� ��ġ�Դϴ�. */
	glm::vec2 textBasePos_ = glm::vec2(0.0f, 0.0f);

	/** ȹ���� ������ �ؽ�Ʈ�Դϴ�. */
	std::wstring coinText_;

	/** ȹ���� ������ �ؽ�Ʈ �����Դϴ�. */
	glm::vec4 textColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	/** ��׶����� �����Դϴ�. */
	glm::vec4 backgroundColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};