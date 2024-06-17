#pragma once

#include "Entity2D.h"

class Character;
class GeometryRenderer2D;
class TextRenderer;
class TTFont;


/**
 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�Դϴ�.
 */
class StatusViewer : public Entity2D
{
public:
	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param character ���� ���� ǥ���� �� ������ ĳ�����Դϴ�.
	 * @param geometryRenderer ���� ���¸� �������� �� ����� 2D �������Դϴ�.
	 * @param textRenderer ���� ���¸� �������� �� ����� �ؽ�Ʈ �������Դϴ�.
	 * @param font �ؽ�Ʈ ������ �� ������ ��Ʈ�Դϴ�.
	 */
	StatusViewer(Character* character, GeometryRenderer2D* geometryRenderer, TextRenderer* textRenderer, TTFont* font);


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StatusViewer();


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StatusViewer);


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���� ���� ���¸� ǥ���ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ���� ���� ǥ���� �� ������ ĳ�����Դϴ�.
	 */
	Character* character_ = nullptr;


	/**
	 * @brief ���� ���¸� �������� �� ����� 2D �������Դϴ�.
	 */
	GeometryRenderer2D* geometryRenderer_ = nullptr;


	/**
	 * @brief ���� ���¸� �������� �� ����� �ؽ�Ʈ �������Դϴ�.
	 */
	TextRenderer* textRenderer_ = nullptr;


	/**
	 * @brief �ؽ�Ʈ ������ �� ������ ��Ʈ�Դϴ�.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief ��׶����� �����Դϴ�.
	 */
	Vec4f backgroundColor_;


	/**
	 * @brief ��׶����� �߽��Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief ��׶����� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ��׶����� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ��׶����� �ձ� �κ��� ũ���Դϴ�.
	 */
	float side_ = 10.0f;


	/**
	 * @brief �Ϲ����� �ؽ�Ʈ �÷��Դϴ�.
	 */
	Vec4f textColor_;


	/**
	 * @brief ���� ������ ���Դϴ�.
	 */
	int32_t currentCoinCount_ = 0;


	/**
	 * @brief ���� ������ �� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring currentCoinCountText_;


	/**
	 * @brief ���� ������ �� �ؽ�Ʈ ��ġ�Դϴ�.
	 */
	Vec2f currentCoinCountTextPosition_;


	/**
	 * @brief ���� ���� �ð��Դϴ�.
	 */
	int32_t currentRemainTime_ = 0.0f;


	/**
	 * @brief ���� ���� �ð� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring currentRemainTimeText_;


	/**
	 * @brief ���� ���� �ð� �ؽ�Ʈ�� ��ġ�Դϴ�.
	 */
	Vec2f currentRemainTimeTextPosition_;


	/**
	 * @brief ī��� �ٿ� ��ġ�Դϴ�.
	 */
	Vec2f countDownPosition_;


	/**
	 * @brief ī��Ʈ �ٿ��� ���� ũ���Դϴ�.
	 */
	float countDownWidth_ = 0.0f;


	/**
	 * @brief ī��Ʈ �ٿ��� ���� ũ���Դϴ�.
	 */
	float countDownHeight_ = 0.0f;


	/**
	 * @brief ī��Ʈ �ٿ��� ��׶��� �����Դϴ�.
	 */
	Vec4f countDownBackgroundColor_;


	/**
	 * @brief ī��Ʈ �ٿ��� �����Դϴ�.
	 */
	Vec4f countDownColor_;
};
