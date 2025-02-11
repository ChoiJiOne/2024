#pragma once

#include <string>

#include "Vec2.h"
#include "Vec4.h"

#include "IEntity.h"
#include "IResource.h"


/**
 * @brief �г� ��ƼƼ�Դϴ�.
 */
class Panel : public IEntity
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
	 * @param fontID �г��� ��Ʈ ���ҽ� ID�Դϴ�.
	 */
	explicit Panel(const std::string& path, const RUID& fontID);


	/**
	 * @brief �г��� �������Դϴ�.
	 *
	 * @param layout �г��� ���̾ƿ��Դϴ�.
	 * @param fontID �г��� ��Ʈ ���ҽ� ID�Դϴ�.
	 */
	explicit Panel(const Layout& layout, const RUID& fontID);


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
	 * @brief �гο� ǥ���� �ؽ�Ʈ�� ��Ʈ ���ҽ� ID�Դϴ�.
	 */
	RUID fontID_ = -1;
};