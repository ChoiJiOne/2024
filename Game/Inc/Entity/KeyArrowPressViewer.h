#pragma once

#include <list>

#include "Entity/IEntity2D.h"
#include "GLFW/GLFWManager.h"
#include "Physic/Rect2D.h"

/** Ŭ������ ���� �����Դϴ�. */
class Player;
class TextureAtlas2D;

/** �÷��̾� ���� Ű �Է� ���¸� �����ִ� ��ƼƼ�Դϴ�. */
class KeyArrowPressViewer : public IEntity2D
{
public:
	KeyArrowPressViewer();
	virtual ~KeyArrowPressViewer();

	DISALLOW_COPY_AND_ASSIGN(KeyArrowPressViewer);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	/** ���� Ű �Է� �����Դϴ�. */
	struct KeyArrowState
	{
		EKey key;
		EPress press;
		Rect2D renderBound;
		std::map<EPress, std::string> names;
	};

private:
	/** Ű �Է� ���� �������� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** Ű �Է� ���� �������� ������ �÷��̾��Դϴ�. */
	Player* player_ = nullptr;

	/** ���� Ű �Է� ������ ����Դϴ�. */
	std::list<KeyArrowState> keyArrowStates_;
};