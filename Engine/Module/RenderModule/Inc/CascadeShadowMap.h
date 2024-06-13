#pragma once

#include "ITexture.h"


/**
 * @brief ĳ�����̵� �ε��� ���Դϴ�.
 *
 * @note
 * - ������ ���� ����/���� ũ��� �����մϴ�.
 * - ĳ�����̵� �ε��� ���� ũ��� 2^n �������� �Ǿ� �ֽ��ϴ�.
 */
class CascadeShadowMap : public ITexture
{
public:
	/**
	 * @brief ĳ�����̵� �ε��� ���� ũ���Դϴ�.
	 */
	enum class ESize
	{
		Size_256  = 256,
		Size_512  = 512,
		Size_1024 = 1024,
		Size_2048 = 2048,
		Size_4096 = 4096,
	};


public:
	/**
	 * @brief ĳ�����̵� �ε��� ���� �������Դϴ�.
	 *
	 * @param size ĳ�����̵� �ε��� ���� ũ���Դϴ�.
	 * @param level ĳ�����̵��� �����Դϴ�.
	 */
	CascadeShadowMap(const ESize& size, uint32_t level);


	/**
	 * @brief ĳ�����̵� �ε��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~CascadeShadowMap();


	/**
	 * @brief ĳ�����̵� �ε��� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(CascadeShadowMap);


	/**
	 * @brief ĳ�����̵� �ε��� �� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ĳ�����̵� �ε��� ���� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	virtual void Active(uint32_t unit) const override;


	/**
	 * @brief ĳ�����̵� �ε��� ���� ���� ���� �ʱ�ȭ�մϴ�.
	 */
	void Clear();


	/**
	 * @brief ĳ�����̵� �ε��� ���� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ĳ�����̵� �ε��� ���� ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ĳ�����̵� �ε��� ���� ũ�⸦ ����ϴ�.
	 *
	 * @return ĳ�����̵� �ε��� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t GetSize() const { return size_; }


private:
	/**
	 * @brief ĳ�����̵� �ε��� ���� ũ���Դϴ�.
	 */
	uint32_t size_;


	/**
	 * @brief ĳ�����̵� �ε��� ���� ������ ���� ID���Դϴ�.
	 */
	uint32_t shadowMapFBO_ = 0;


	/**
	 * @brief ĳ�����̵� �ε��� ���� ���̰� ���� ID���Դϴ�.
	 */
	uint32_t shadowMapID_ = 0;
};