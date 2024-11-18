#pragma once

#include <queue>

#include "Entity/IEntity2D.h"
#include "GL/RenderManager2D.h"
#include "Physic/Rect2D.h"

/** Ŭ���� ���� �����Դϴ�. */
class UICamera;
class IObject;
class RandomChest;
class Player;
class Playground;
class TextureAtlas2D;

/** ��ü ���� ���带 ����ؼ� �����ִ� �̴ϸ� ��ƼƼ�Դϴ�. */
class MiniMap : public IEntity2D
{
public:
	MiniMap(UICamera* uiCamera, const std::vector<RandomChest*>& randomChests);
	virtual ~MiniMap();

	DISALLOW_COPY_AND_ASSIGN(MiniMap);
	
	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** �̴ϸ� ���� ������Ʈ�Դϴ�. */
	struct MinimapObject
	{
		glm::vec2 position; // �̴ϸ� ���� ��ġ�Դϴ�.
		glm::vec4 color; // �̴ϸ� ���� �����Դϴ�.
	};

	/** ������Ʈ�� �̴ϸ� ������Ʈ�� ��ȯ�մϴ�. */
	void ConvertMinimapObject(const IObject* object, MinimapObject& outMinimapObjec);

private:
	/** �̴ϸ� �������� ������ �� UI ī�޶��Դϴ�. */
	UICamera* uiCamera_ = nullptr;

	/** �̴ϸ� ������ �� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** ������ �����Դϴ�. */
	Rect2D renderBound_;

	/** �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** �÷��� ������ ������ �����Դϴ�. */
	float playgroundRadius_ = 0.0f;

	/** �̴ϸ� ������ �����Դϴ�. */
	float minimapRadius_ = 0.0f;

	/** �̴ϸʿ� ǥ���� ���� ũ���Դϴ�. */
	float pointSize_ = 0.0f;
	
	/** �̴ϸ� ���� �÷��̾� �����Դϴ�. */
	glm::vec4 playerColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** �̴ϸ� ���� ���� �����Դϴ�. */
	glm::vec4 coinColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** �̴ϸ� ���� �� �����Դϴ�. */
	glm::vec4 fireColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** �̴ϸ� ���� ������ ���� �����Դϴ�. */
	glm::vec4 redPotionColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** �̴ϸ� ���� �Ķ��� ���� �����Դϴ�. */
	glm::vec4 bluePotionColor_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	/** ������Ʈ���� �����ϴ� ���� ���� ��ƼƼ ����Դϴ�. */
	std::vector<RandomChest*> randomChests_;

	/** �̴ϸ� ���� ������Ʈ ť�Դϴ�. */
	std::queue<MinimapObject> minimapObjects_;
};