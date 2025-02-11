#pragma once

#include <functional>
#include <string>

#include "Vec2.h"
#include "Vec4.h"

#include "IEntity.h"
#include "IResource.h"
#include "InputManager.h"


/**
 * @brief ���콺 ��ư ��ƼƼ�Դϴ�.
 */
class Button : public IEntity
{
public:
	/**
	 * @brief ���콺 ��ư�� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		Disabled = 0x00,
		Enabled = 0x01,
		Pressed = 0x02,
		Released = 0x03,
	};


	/**
	 * @brief ��ư�� ���̾ƿ��Դϴ�.
	 */
	struct Layout
	{
		float width;
		float height;
		float side;
		Vec2f center;
		std::wstring text;
		Vec4f outlineColor;
		Vec4f textColor;
		Vec4f disableColor;
		Vec4f enableColor;
		Vec4f pressColor;
		Vec4f releaseColor;
	};


public:
	/**
	 * @brief ���콺 ��ư�� �������Դϴ�.
	 *
	 * @param path ���콺 ��ư�� ���̾ƿ� ���ҽ� ����Դϴ�.
	 * @param fontID ���콺 ��ư�� ��Ʈ ���ҽ� ID�Դϴ�.
	 * @param mouseButton ���콺 ��ư�� �����Դϴ�.
	 * @param clickEvent ���콺 ��ư Ŭ�� �� ������ �̺�Ʈ�Դϴ�.
	 */
	explicit Button(const std::string& path, const RUID& fontID, const EMouseButton& mouseButton, const std::function<void()>& clickEvent);


	/**
	 * @brief ���콺 ��ư�� �������Դϴ�.
	 * 
	 * @param layout ���콺 ��ư�� ���̾ƿ��Դϴ�.
	 * @param fontID ���콺 ��ư�� ��Ʈ ���ҽ� ID�Դϴ�.
	 * @param mouseButton ���콺 ��ư�� �����Դϴ�.
	 * @param clickEvent ���콺 ��ư Ŭ�� �� ������ �̺�Ʈ�Դϴ�.
	 */
	explicit Button(const Layout& layout, const RUID& fontID, const EMouseButton& mouseButton, const std::function<void()>& clickEvent);


	/**
	 * @brief ���콺 ��ư�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Button();


	/**
	 * @brief ���콺 ��ư�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Button);


	/**
	 * @brief ���콺 ��ư�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���콺 ��ư�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���콺 ��ư ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ���콺 ��ư�� ���¸� ����ϴ�.
	 *
	 * @param pressState Ű �Է� �����Դϴ�.
	 * @param state ���� ��ư�� �����Դϴ�.
	 *
	 * @return ���Ӱ� ������Ʈ�� ��ư�� ���¸� ����ϴ�.
	 */
	EState GetMouseButtonState(const EPressState& pressState, const EState& state);


	/**
	 * @brief ���콺�� ��ư ���� �ִ��� Ȯ���մϴ�.
	 *
	 * @return ���콺�� ��ư ���� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool DetectMouseCursorInButton();

	
protected:
	/**
	 * @brief ���콺 ��ư�� ���̾ƿ��Դϴ�.
	 */
	Layout layout_;


	/**
	 * @brief ���콺 ��ư�� ǥ���� �ؽ�Ʈ�� ��Ʈ ���ҽ� ID�Դϴ�.
	 */
	RUID fontID_ = -1;


	/**
	 * @brief UI ��ư�� ���� Ű ���Դϴ�.
	 */
	EMouseButton mouseButton_ = EMouseButton::Left;


	/**
	 * @brief UI ��ư�� Ŭ������ �� ������ �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> clickEvent_;


	/**
	 * @brief ���� ���콺 ��ư�� �����Դϴ�.
	 */
	EState state_ = EState::Disabled;
};