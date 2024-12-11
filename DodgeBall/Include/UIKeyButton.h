#pragma once

#include <functional>
#include <string>

#include "IObject.h"
#include "InputManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // Ʈ�� Ÿ�� ��Ʈ ���ҽ��� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief UI Ű ��ư ������Ʈ�Դϴ�.
 */
class UIKeyButton : public IObject
{
public:
    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� �Ķ�����Դϴ�.
     */
    struct UIButtonConstructParam
    {
        float width;
        float height;
        Vector2f center;
        std::wstring text;
        TTFont* font;
        Vector4f outlineColor;
        Vector4f textColor;
        Vector4f disableColor;
        Vector4f pressColor;
        Vector4f releaseColor;
        EVirtualKey key;
        std::function<void()> keyClickEvent;
    };


public:
    /**
     * @brief UI Ű ��ư ������Ʈ�� ����Ʈ �������Դϴ�.
     */
    UIKeyButton() = default;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� �Ҹ����Դϴ�.
     */
    virtual ~UIKeyButton();


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
     */
    DISALLOW_COPY_AND_ASSIGN(UIKeyButton);


    /**
     * @brief UI Ű ��ư ������Ʈ�� �ʱ�ȭ�մϴ�.
     *
     * @param uiConstructParam UI Ű ��ư ������Ʈ�� �ʱ�ȭ�ϱ� ���� �Ķ�����Դϴ�.
     */
    virtual void Initialize(const UIButtonConstructParam& uiConstructParam);


    /**
     * @brief UI Ű ��ư ������Ʈ�� ������Ʈ�մϴ�.
     *
     * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
     */
    virtual void Tick(float deltaSeconds) override;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ȭ�鿡 �׸��ϴ�.
     */
    virtual void Render();


    /**
     * @brief UI Ű ��ư ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
     */
    virtual void Release() override;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    float GetWidth() { return width_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    const float& GetWidth() const { return width_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    float GetHeight() { return height_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    const float& GetHeight() const { return height_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� �߽� ��ǥ�� ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� �߽� ��ǥ�Դϴ�.
     */
    Vector2f GetCenter() { return center_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� �߽� ��ǥ�� ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� �߽� ��ǥ�Դϴ�.
     */
    const Vector2f& GetCenter() const { return center_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
     */
    std::wstring GetText() { return text_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
     */
    const std::wstring& GetText() const { return text_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� �ܰ��� ������ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    Vector4f GetOutlineColor() { return outlineColor_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� �ܰ��� ������ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    const Vector4f& GetOutlineColor() const { return outlineColor_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ��Ȱ��ȭ ������ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ��Ȱ��ȭ �����Դϴ�.
     */
    Vector4f GetDisableColor() { return disableColor_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ��Ȱ��ȭ ������ ��ȯ�մϴ�.
     *
     * @return UI Ű ��ư ������Ʈ�� ��Ȱ��ȭ �����Դϴ�.
     */
    const Vector4f& GetDisableColor() const { return disableColor_; }

    
    /**
     * @brief UI ��ư�� ������ ���� ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư�� ������ ���� �����Դϴ�.
     */
    Vector4f GetPressColor() { return pressColor_; }


    /**
     * @brief UI ��ư�� ������ ���� ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư�� ������ ���� �����Դϴ�.
     */
    const Vector4f& GetPressColor() const { return pressColor_; }


    /**
     * @brief UI ��ư�� ������ ���� ���� ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư�� ������ ���� ���� �����Դϴ�.
     */
    Vector4f GetReleaseColor() { return releaseColor_; }


    /**
     * @brief UI ��ư�� ������ ���� ���� ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư�� ������ ���� ���� �����Դϴ�.
     */
    const Vector4f& GetReleaseColor() const { return releaseColor_; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ�⸦ �����մϴ�.
     *
     * @param width UI Ű ��ư ������Ʈ�� ������ ���� ũ���Դϴ�.
     */
    void SetWidth(float width) { width_ = width; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ�⸦ �����մϴ�.
     *
     * @param height UI Ű ��ư ������Ʈ�� ������ ���� �Դϴ�.
     */
    void SetHeight(float height) { height_ = height; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� �߽� ��ǥ�� �����մϴ�.
     *
     * @param center UI Ű ��ư ������Ʈ�� ������ �߽� ��ǥ�Դϴ�.
     */
    void SetCenter(const Vector2f& center) { center_ = center; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ǥ���� �ؽ�Ʈ�� �����մϴ�.
     *
     * @param text UI Ű ��ư ������Ʈ�� ������ �ؽ�Ʈ�Դϴ�.
     */
    void SetText(const std::wstring& text) { text_ = text; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� �ܰ��� ������ �����մϴ�.
     *
     * @param outlineColor UI Ű ��ư ������Ʈ�� ������ �ܰ��� �����Դϴ�.
     */
    void SetOutlineColor(const Vector4f& outlineColor) { outlineColor_ = outlineColor; }


    /**
     * @brief UI Ű ��ư ������Ʈ�� ��Ȱ��ȭ ������ �����մϴ�.
     *
     * @param disableColor UI Ű ��ư ������Ʈ�� ������ ��Ȱ��ȭ �����Դϴ�.
     */
    void SetDisableColor(const Vector4f& disableColor) { disableColor_ = disableColor; }


    /**
     * @brief UI ��ư�� ������ ���� ������ �����մϴ�.
     *
     * @param pressColor UI ��ư�� ������ ������ ���� �����Դϴ�.
     */
    void SetPressColor(const Vector4f& pressColor) { pressColor_ = pressColor; }


    /**
     * @brief UI ��ư�� ������ ���� ���� ������ �����մϴ�.
     *
     * @param releaseColor UI ��ư�� ������ ������ ���� ���� �����Դϴ�.
     */
    void SetReleaseColor(const Vector4f& releaseColor) { releaseColor_ = releaseColor; }


private:
    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    float width_;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    float height_;


    /**
     * @brief UI Ű ��ư ������Ʈ�� �߽� ��ǥ�Դϴ�.
     *
     * @note �̶�, UI �г� ������Ʈ�� ��ǥ��� ������ ��ǥ�� �����Դϴ�.
     */
    Vector2f center_;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ǥ���� �ؽ�Ʈ�Դϴ�.
     */
    std::wstring text_;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ǥ���� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
     */
    TTFont* font_;


    /**
     * @brief UI Ű ��ư ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    Vector4f outlineColor_;


    /**
     * @brief UI ��ư �ؽ�Ʈ�� �����Դϴ�.
     */
    Vector4f textColor_;


    /**
     * @brief UI Ű ��ư ������Ʈ�� ��Ȱ��ȭ �����Դϴ�.
     */
    Vector4f disableColor_;


    /**
     * @brief UI ��ư�� ������ ���� �����Դϴ�.
     */
    Vector4f pressColor_;


    /**
     * @brief UI ��ư�� ������ ���� ���� �����Դϴ�.
     */
    Vector4f releaseColor_;


    /**
     * @brief UI Ű ��ư�� ���� Ű ���Դϴ�.
     */
    EVirtualKey virtualKey_ = EVirtualKey::VKEY_NONE;


    /**
     * @brief UI Ű ��ư�� Ŭ������ �� ������ �̺�Ʈ�Դϴ�.
     */
    std::function<void()> keyClickEvent_;
};