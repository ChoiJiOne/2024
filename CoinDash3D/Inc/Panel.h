#pragma once

#include <string>

#include "Entity2D.h"
#include "Vec.h"

class GeometryRenderer2D;
class TTFont;
class TextRenderer;


/**
 * @brief �г� ��ƼƼ�Դϴ�.
 */
class Panel : public Entity2D
{
public:
	/**
	 * @brief �г��� ���̾ƿ��Դϴ�.
	 */
	struct Layout
	{
		float width;
		float height;
		float side;
		Vec2f center;
		std::wstring text;
		Vec4f outlineColor;
		Vec4f backgroundColor;
		Vec4f textColor;
	};


public:
	/**
	 * @brief �г��� �������Դϴ�.
	 *
	 * @param path �г��� ���̾ƿ� ���ҽ� ����Դϴ�.
	 * @param font �г��� ��Ʈ ���ҽ��Դϴ�.
	 * @param geometryRenderer 2D ���� ������ �������� �� ����� �������Դϴ�.
	 * @param textRenderer �ؽ�Ʈ �������� ����� �������Դϴ�.
	 */
	explicit Panel(const std::string& path, TTFont* font, GeometryRenderer2D* geometryRenderer, TextRenderer* textRenderer);


	/**
	 * @brief �г��� �������Դϴ�.
	 *
	 * @param layout �г��� ���̾ƿ��Դϴ�.
	 * @param font �г��� ��Ʈ ���ҽ��Դϴ�.
	 */
	explicit Panel(const Layout& layout, TTFont* font);


	/**
	 * @brief �г��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Panel();


	/**
	 * @brief �г��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Panel);


	/**
	 * @brief �г��� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �г��� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �г� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


protected:
	/**
	 * @brief �г��� ���̾ƿ��Դϴ�.
	 */
	Layout layout_;


	/**
	 * @brief �гο� ǥ���� �ؽ�Ʈ�� ��Ʈ ���ҽ��Դϴ�.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief 2D ���� ������ �������� �� ����� �������Դϴ�.
	 */
	GeometryRenderer2D* geometryRenderer2D_ = nullptr;


	/**
	 * @brief �ؽ�Ʈ �������� ����� �������Դϴ�.
	 */
	TextRenderer* textRenderer_ = nullptr;
};