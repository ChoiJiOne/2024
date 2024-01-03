#pragma once

#include <string>

#include "IResource.h"


/**
 * @brief ť��� ������ �ε��ϰ� OpenGL ���������ο� ���ε� ������ �ؽ�ó ���ҽ��� ���� �� �����մϴ�.
 */
class CubeMap : public IResource
{
public:
	/**
	 * @brief ť����� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	CubeMap() = default;


	/**
	 * @brief ť����� ���� �Ҹ����Դϴ�.
	 * 
	 * @note ť��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~CubeMap();


	/**
	 * @brief ť����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(CubeMap);


	/**
	 * @brief ť��� �̹��� ������ �а� ť��� ���ҽ��� �����մϴ�.
	 *
	 * @param rightPath ť��� RIGHT(+X) �κ��� �ؽ�ó ���ҽ� ����Դϴ�.
	 * @param leftPath ť��� LEFT(-X) �κ��� �ؽ�ó ���ҽ� ����Դϴ�.
	 * @param topPath ť��� TOP(+Y) �κ��� �ؽ�ó ���ҽ� ����Դϴ�.
	 * @param bottomPath ť��� BOTTOM(-Y) �κ��� �ؽ�ó ���ҽ� ����Դϴ�.
	 * @param frontPath ť��� FRONT(+Z) �κ��� �ؽ�ó ���ҽ� ����Դϴ�.
	 * @param backPath ť��� BACK(-Z) �κ��� �ؽ�ó ���ҽ� ����Դϴ�.
	 */
	void Initialize(
		const std::wstring& rightPath,
		const std::wstring& leftPath,
		const std::wstring& topPath,
		const std::wstring& bottomPath,
		const std::wstring& frontPath,
		const std::wstring& backPath
	);


	/**
	 * @brief ť��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ť����� Ȱ��ȭ�մϴ�.
	 * 
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit) const;


private:
	/**
	 * @brief ť��� �ؽ�ó�� ID�Դϴ�.
	 */
	uint32_t cubeMapID_ = 0;
};
