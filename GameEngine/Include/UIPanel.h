#pragma once

#include <string>

#include "IObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // Ʈ�� Ÿ�� ��Ʈ ���ҽ��� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief UI �г� ������Ʈ�Դϴ�.
 * 
 * @note UI �г� ������Ʈ�� ��ǥ��� ������ ��ǥ�� �����Դϴ�.
 */
class UIPanel : public IObject
{
public:
	/**
	 * @brief UI �г� ������Ʈ�� ���� �Ķ�����Դϴ�.
	 */
	struct UIConstructParam
	{
		float width;
		float height;
		Vector2f center;
		std::wstring text;
		TTFont* font;
		Vector4f outlineColor;
		Vector4f backgroundColor;
		Vector4f textColor;
	};


public:
	/**
	 * @brief UI �г� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	UIPanel() = default;


	/**
	 * @brief UI �г� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~UIPanel() {}


	/**
	 * @brief UI �г� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIPanel);


	/**
	 * @brief UI �г� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param uiConstructParam UI �г� ������Ʈ�� �ʱ�ȭ�ϱ� ���� �Ķ�����Դϴ�.
	 */
	virtual void Initialize(const UIConstructParam& uiConstructParam);


	/**
	 * @brief UI �г� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief UI �г� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render();


	/**
	 * @brief UI �г� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


    /**
     * @brief UI �г� ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ���� ũ���Դϴ�.
     */
    float GetWidth() { return width_; }


    /**
     * @brief UI �г� ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ���� ũ���Դϴ�.
     */
    const float& GetWidth() const { return width_; }


    /**
     * @brief UI �г� ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ���� ũ���Դϴ�.
     */
    float GetHeight() { return height_; }


    /**
     * @brief UI �г� ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ���� ũ���Դϴ�.
     */
    const float& GetHeight() const { return height_; }


    /**
     * @brief UI �г� ������Ʈ�� �߽� ��ǥ�� ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� �߽� ��ǥ�Դϴ�.
     */
    Vector2f GetCenter() { return center_; }


    /**
     * @brief UI �г� ������Ʈ�� �߽� ��ǥ�� ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� �߽� ��ǥ�Դϴ�.
     */
    const Vector2f& GetCenter() const { return center_; }


    /**
     * @brief UI �г� ������Ʈ�� ǥ�õ� �ؽ�Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
     */
    std::wstring GetText() { return text_; }


    /**
     * @brief UI �г� ������Ʈ�� ǥ�õ� �ؽ�Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
     */
    const std::wstring& GetText() const { return text_; }


    /**
     * @brief UI �г� ������Ʈ�� ���� ��Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ���� ��Ʈ�Դϴ�.
     */
    TTFont* GetFont() { return font_; }


    /**
     * @brief UI �г� ������Ʈ�� ���� ��Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ���� ��Ʈ�Դϴ�.
     */
    const TTFont* GetFont() const { return font_; }


    /**
     * @brief UI �г� ������Ʈ�� �ܰ��� ������ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    Vector4f GetOutlineColor() { return outlineColor_; }


    /**
     * @brief UI �г� ������Ʈ�� �ܰ��� ������ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    const Vector4f& GetOutlineColor() const { return outlineColor_; }
	

    /**
     * @brief UI �г� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ��� �����Դϴ�.
     */
    Vector4f GetBackgroundColor() { return backgroundColor_; }


    /**
     * @brief UI �г� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� ��� �����Դϴ�.
     */
    const Vector4f& GetBackgroundColor() const { return backgroundColor_; }


    /**
     * @brief UI �г� ������Ʈ�� �ؽ�Ʈ ������ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� �ؽ�Ʈ �����Դϴ�.
     */
    Vector4f GetTextColor() { return textColor_; }


    /**
     * @brief UI �г� ������Ʈ�� �ؽ�Ʈ ������ ��ȯ�մϴ�.
     *
     * @return UI �г� ������Ʈ�� �ؽ�Ʈ �����Դϴ�.
     */
    const Vector4f& GetTextColor() const { return textColor_; }
    

    /**
     * @brief UI �г� ������Ʈ�� ���� ũ�⸦ �����մϴ�.
     *
     * @param width UI �г� ������Ʈ�� ������ ���� ũ���Դϴ�.
     */
    void SetWidth(float width) { width_ = width; }


    /**
     * @brief UI �г� ������Ʈ�� ���� ũ�⸦ �����մϴ�.
     *
     * @param height UI �г� ������Ʈ�� ������ ���� ũ���Դϴ�.
     */
    void SetHeight(float height) { height_ = height; }


    /**
     * @brief UI �г� ������Ʈ�� �߽� ��ǥ�� �����մϴ�.
     *
     * @param center UI �г� ������Ʈ�� ������ �߽� ��ǥ�Դϴ�.
     */
    void SetCenter(const Vector2f& center) { center_ = center; }


    /**
     * @brief UI �г� ������Ʈ�� ǥ���� �ؽ�Ʈ�� �����մϴ�.
     *
     * @param text UI �г� ������Ʈ�� ������ �ؽ�Ʈ�Դϴ�.
     */
    void SetText(const std::wstring& text) { text_ = text; }


    /**
     * @brief UI �г� ������Ʈ�� ����� ��Ʈ�� �����մϴ�.
     *
     * @param font UI �г� ������Ʈ�� ������ ��Ʈ�Դϴ�.
     */
    void SetFont(TTFont* font) { font_ = font; }


    /**
     * @brief UI �г� ������Ʈ�� �ܰ��� ������ �����մϴ�.
     *
     * @param outlineColor UI �г� ������Ʈ�� ������ �ܰ��� �����Դϴ�.
     */
    void SetOutlineColor(const Vector4f& outlineColor) { outlineColor_ = outlineColor; }


    /**
     * @brief UI �г� ������Ʈ�� ��� ������ �����մϴ�.
     *
     * @param backgroundColor UI �г� ������Ʈ�� ������ ��� �����Դϴ�.
     */
    void SetBackgroundColor(const Vector4f& backgroundColor) { backgroundColor_ = backgroundColor; }


    /**
     * @brief UI �г� ������Ʈ�� �ؽ�Ʈ ������ �����մϴ�.
     *
     * @param textColor UI �г� ������Ʈ�� ������ �ؽ�Ʈ �����Դϴ�.
     */
    void SetTextColor(const Vector4f& textColor) { textColor_ = textColor; }
    

protected:
	/**
	 * @brief UI �г� ������Ʈ�� ���� ũ���Դϴ�.
	 */
	float width_;


	/**
	 * @brief UI �г� ������Ʈ�� ���� ũ���Դϴ�.
	 */
	float height_;


	/**
	 * @brief UI �г� ������Ʈ�� �߽� ��ǥ�Դϴ�.
	 * 
	 * @note �̶�, UI �г� ������Ʈ�� ��ǥ��� ������ ��ǥ�� �����Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief UI �г� ������Ʈ�� ǥ���� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring text_;


	/**
	 * @brief UI �г� ������Ʈ�� ǥ���� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font_;


	/**
	 * @brief UI �г� ������Ʈ�� �ܰ��� �����Դϴ�.
	 */
	Vector4f outlineColor_;


	/**
	 * @brief UI �г� ������Ʈ�� ��׶��� �����Դϴ�.
	 */
	Vector4f backgroundColor_;


	/**
	 * @brief UI �г� ������Ʈ�� �ؽ�Ʈ �����Դϴ�.
	 */
	Vector4f textColor_;
};