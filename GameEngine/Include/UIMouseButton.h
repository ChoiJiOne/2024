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
 * @brief UI ���콺 ��ư ������Ʈ�Դϴ�.
 */
class UIMouseButton : public IObject
{
public:
	/**
	 * @brief UI ��ư ������Ʈ�� ���� �Ķ�����Դϴ�.
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
		Vector4f enableColor;
		Vector4f pressColor;
		Vector4f releaseColor;
        EVirtualKey virtualKey;
		std::function<void()> clickEvent;
	};


    /**
     * 
     */


    /**
     * @brief ���콺 ��ư�� �����Դϴ�.
     */
    enum class EState : int32_t
    {
        Disabled = 0x00,
        Enabled  = 0x01,
        Pressed  = 0x02,
        Released = 0x03,
    };


public:
	/**
	 * @brief UI ��ư ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	UIMouseButton() = default;


	/**
	 * @brief UI ��ư ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~UIMouseButton();


	/**
	 * @brief UI ��ư ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIMouseButton);


	/**
	 * @brief UI ��ư ������Ʈ�� �ʱ�ȭ�մϴ�.
	 *
	 * @param uiConstructParam UI ��ư ������Ʈ�� �ʱ�ȭ�ϱ� ���� �Ķ�����Դϴ�.
	 */
	virtual void Initialize(const UIButtonConstructParam& uiConstructParam);


	/**
	 * @brief UI ��ư ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief UI ��ư ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render();


	/**
	 * @brief UI ��ư ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


    /**
     * @brief UI ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    float GetWidth() { return width_; }


    /**
	 * @brief UI ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
	 *
	 * @return UI ��ư ������Ʈ�� ���� ũ���Դϴ�.
	 */
    const float& GetWidth() const { return width_; }


    /**
     * @brief UI ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    float GetHeight() { return height_; }


    /**
     * @brief UI ��ư ������Ʈ�� ���� ũ�⸦ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ���� ũ���Դϴ�.
     */
    const float& GetHeight() const { return height_; }


    /**
     * @brief UI ��ư ������Ʈ�� �߽� ��ǥ�� ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� �߽� ��ǥ�Դϴ�.
     */
    Vector2f GetCenter() { return center_; }


    /**
     * @brief UI ��ư ������Ʈ�� �߽� ��ǥ�� ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� �߽� ��ǥ�Դϴ�.
     */
    const Vector2f& GetCenter() const { return center_; }


    /**
     * @brief UI ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
     */
    std::wstring GetText() { return text_; }


    /**
     * @brief UI ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�� ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
     */
    const std::wstring& GetText() const { return text_; }


    /**
     * @brief UI ��ư ������Ʈ�� �ܰ��� ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    Vector4f GetOutlineColor() { return outlineColor_; }


    /**
     * @brief UI ��ư ������Ʈ�� �ܰ��� ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� �ܰ��� �����Դϴ�.
     */
    const Vector4f& GetOutlineColor() const { return outlineColor_; }


    /**
     * @brief UI ��ư ������Ʈ�� ��Ȱ��ȭ ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ��Ȱ��ȭ �����Դϴ�.
     */
    Vector4f GetDisableColor() { return disableColor_; }


    /**
     * @brief UI ��ư ������Ʈ�� ��Ȱ��ȭ ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� ��Ȱ��ȭ �����Դϴ�.
     */
    const Vector4f& GetDisableColor() const { return disableColor_; }


    /**
     * @brief UI ��ư ������Ʈ�� Ȱ��ȭ ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� Ȱ��ȭ �����Դϴ�.
     */
    Vector4f GetEnableColor() { return enableColor_; }


    /**
     * @brief UI ��ư ������Ʈ�� Ȱ��ȭ ������ ��ȯ�մϴ�.
     *
     * @return UI ��ư ������Ʈ�� Ȱ��ȭ �����Դϴ�.
     */
    const Vector4f& GetEnableColor() const { return enableColor_; }


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
     * @brief UI ��ư ������Ʈ�� ���� ũ�⸦ �����մϴ�.
     *
     * @param width UI ��ư ������Ʈ�� ������ ���� ũ���Դϴ�.
     */
    void SetWidth(float width) { width_ = width; }


    /**
     * @brief UI ��ư ������Ʈ�� ���� ũ�⸦ �����մϴ�.
     *
     * @param height UI ��ư ������Ʈ�� ������ ���� �Դϴ�.
     */
    void SetHeight(float height) { height_ = height; }


    /**
     * @brief UI ��ư ������Ʈ�� �߽� ��ǥ�� �����մϴ�.
     *
     * @param center UI ��ư ������Ʈ�� ������ �߽� ��ǥ�Դϴ�.
     */
    void SetCenter(const Vector2f& center) { center_ = center; }


    /**
     * @brief UI ��ư ������Ʈ�� ǥ���� �ؽ�Ʈ�� �����մϴ�.
     *
     * @param text UI ��ư ������Ʈ�� ������ �ؽ�Ʈ�Դϴ�.
     */
    void SetText(const std::wstring& text) { text_ = text; }


    /**
     * @brief UI ��ư ������Ʈ�� �ܰ��� ������ �����մϴ�.
     *
     * @param outlineColor UI ��ư ������Ʈ�� ������ �ܰ��� �����Դϴ�.
     */
    void SetOutlineColor(const Vector4f& outlineColor) { outlineColor_ = outlineColor; }


    /**
     * @brief UI ��ư ������Ʈ�� ��Ȱ��ȭ ������ �����մϴ�.
     *
     * @param disableColor UI ��ư ������Ʈ�� ������ ��Ȱ��ȭ �����Դϴ�.
     */
    void SetDisableColor(const Vector4f& disableColor) { disableColor_ = disableColor; }


    /**
     * @brief UI ��ư ������Ʈ�� Ȱ��ȭ ������ �����մϴ�.
     *
     * @param enableColor UI ��ư ������Ʈ�� ������ Ȱ��ȭ �����Դϴ�.
     */
    void SetEnableColor(const Vector4f& enableColor) { enableColor_ = enableColor; }


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
     * @brief ���콺 ��ư�� ���¸� ����ϴ�.
     * 
     * @param keyPressState Ű �Է� �����Դϴ�.
     * @param state ���� ��ư�� �����Դϴ�.
     * 
     * @return ���Ӱ� ������Ʈ�� ��ư�� ���¸� ����ϴ�.
     */
    EState GetMouseButtonState(const EPressState& keyPressState, const EState& state);


    /**
     * @brief ���콺�� UI ��ư ���� �ִ��� Ȯ���մϴ�.
     * 
     * @return ���콺�� UI ��ư ���� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
     */
    bool DetectMouseCursorInButton();


private:
	/**
	 * @brief UI ��ư ������Ʈ�� ���� ũ���Դϴ�.
	 */
	float width_;


	/**
	 * @brief UI ��ư ������Ʈ�� ���� ũ���Դϴ�.
	 */
	float height_;


	/**
	 * @brief UI ��ư ������Ʈ�� �߽� ��ǥ�Դϴ�.
	 * 
	 * @note �̶�, UI �г� ������Ʈ�� ��ǥ��� ������ ��ǥ�� �����Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief UI ��ư ������Ʈ�� ǥ���� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring text_;


	/**
	 * @brief UI ��ư ������Ʈ�� ǥ���� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font_;


	/**
	 * @brief UI ��ư ������Ʈ�� �ܰ��� �����Դϴ�.
	 */
	Vector4f outlineColor_;


    /**
     * @brief UI ��ư �ؽ�Ʈ�� �����Դϴ�.
     */
    Vector4f textColor_;


	/**
	 * @brief UI ��ư ������Ʈ�� ��Ȱ��ȭ �����Դϴ�.
	 */
	Vector4f disableColor_;


	/**
	 * @brief UI ��ư�� Ȱ��ȭ �����Դϴ�.
	 */
	Vector4f enableColor_;


	/**
	 * @brief UI ��ư�� ������ ���� �����Դϴ�.
	 */
	Vector4f pressColor_;


	/**
	 * @brief UI ��ư�� ������ ���� ���� �����Դϴ�.
	 */
	Vector4f releaseColor_;
    

	/**
	 * @brief UI ��ư�� ���� Ű ���Դϴ�.
	 */
	EVirtualKey virtualKey_ = EVirtualKey::VKEY_NONE;


	/**
	 * @brief UI ��ư�� Ŭ������ �� ������ �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> clickEvent_;


    /**
     * @brief ���� ���콺 ��ư�� �����Դϴ�.
     */
    EState state_ = EState::Disabled;
};