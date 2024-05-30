#pragma once

#include "ITexture2D.h"


/**
 * @brief �ε��� ���Դϴ�.
 *
 * @note
 * - ������ ���� ����/���� ũ��� �����մϴ�.
 * - �ε��� ���� ũ��� 2^n �������� �Ǿ� �ֽ��ϴ�.
 */
class ShadowMap : public ITexture2D
{
public:
	/**
	 * @brief �ε��� ���� ũ���Դϴ�.
	 */
	enum class ESize
	{
		Size_256x256   = 256,
		Size_512x512   = 512,
		Size_1024x1024 = 1024,
	};


public:
	/**
	 * @brief �ε��� ���� �������Դϴ�.
	 *
	 * @param size �ε��� ���� ũ���Դϴ�.
	 */
	ShadowMap(const ESize& size);


	/**
	 * @brief �ε��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ShadowMap();


	/**
	 * @brief �ε��� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowMap);


	/**
	 * @brief �ε��� �� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ε��� ���� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	virtual void Active(uint32_t unit) const override;


	/**
	 * @brief �ε��� ���� ���� ���� �ʱ�ȭ�մϴ�.
	 */
	void Clear();


	/**
	 * @brief �ε��� ���� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief �ε��� ���� ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief �ε��� ���� ũ�⸦ ����ϴ�.
	 *
	 * @return �ε��� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t GetSize() const { return size_; }


private:
	/**
	 * @brief �ε��� ���� ũ���Դϴ�.
	 */
	uint32_t size_;


	/**
	 * @brief �ε��� ���� ������ ���� ID���Դϴ�.
	 */
	uint32_t shadowMapFBO_ = 0;


	/**
	 * @brief �ε��� ���� ���̰� ���� ID���Դϴ�.
	 */
	uint32_t shadowMapID_ = 0;
};