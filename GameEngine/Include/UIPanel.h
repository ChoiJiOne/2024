#pragma once

#include <string>

#include "UIObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // Ʈ�� Ÿ�� ��Ʈ ���ҽ��� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief UI �г� ������Ʈ�Դϴ�.
 */
class UIPanel : public UIObject
{
public:
	/**
	 * @brief UI �г� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	UIPanel() = default;


	/**
	 * @brief UI �г� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~UIPanel();


	/**
	 * @brief UI �г� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIPanel);


	/**
	 * @brief 2D �г� UI ������Ʈ�� �ʱ�ȭ�մϴ�.
	 *
	 * @param width �г��� ���� ũ���Դϴ�.
	 * @param height �г��� ���� ũ���Դϴ�.
	 * @param center �г��� �߽� ��ǥ�Դϴ�.
	 * @param text �г� ���� ǥ�õ� �ؽ�Ʈ�Դϴ�.
	 * @param font �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 * @param outlineRGB �г� �ܰ����� �����Դϴ�.
	 * @param backgroundRGB �г� ���� ��׶��� �����Դϴ�.
	 * @param textRGB �г� ���� �ؽ�Ʈ �����Դϴ�.
	 * @param transparent �г��� �����Դϴ�. �̶�, ���� ���� ������ 0.0���� 1.0�Դϴ�.
	 */
	virtual void Initialize(
		float width,
		float height,
		const Vector2f& center,
		const std::wstring& text,
		TTFont* font,
		const Vector3f& outlineRGB,
		const Vector3f& backgroundRGB,
		const Vector3f& textRGB,
		float transparent = 1.0f
	);


	/**
	 * @brief UI �г� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief UI �г� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief UI �г� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


protected:
	/**
	 * @brief �г��� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief �г��� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief �г��� �߽� ũ���Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief �гο� ǥ�õ� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring text_;


	/**
	 * @brief �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief �г��� �ܰ��� �����Դϴ�.
	 */
	Vector3f outlineRGB_;


	/**
	 * @brief �г� ��׶����� �����Դϴ�.
	 */
	Vector3f backgroundRGB_;


	/**
	 * @brief �ؽ�Ʈ�� �����Դϴ�.
	 */
	Vector3f textRGB_;


	/**
	 * @brief �г��� �����Դϴ�.
	 */
	float transparent_ = 1.0f;
};