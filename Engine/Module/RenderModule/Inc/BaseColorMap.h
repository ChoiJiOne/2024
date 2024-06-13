#pragma once

#include "Vec.h"

#include "ITexture.h"


/**
 * @brief ���̽� �÷� ���Դϴ�.
 * 
 * @note
 * - �ؽ�ó�� ũ��� �ݵ�� 2^n �����Դϴ�.
 * - �ؽ�ó�� ũ��� ������ ���������θ� ������ �� �ֽ��ϴ�.
 * - �� �ؽ�ó�� �ܻ��Դϴ�.
 */
class BaseColorMap : public ITexture
{
public:
	/**
	 * @brief �ؽ�ó�� ũ���Դϴ�.
	 */
	enum class ESize
	{
		Size_2x2       = 2,
		Size_4x4       = 4,
		Size_8x8       = 8,
		Size_16x16     = 16,
		Size_32x32     = 32,
		Size_64x64     = 64,
		Size_128x128   = 128,
		Size_256x256   = 256,
		Size_512x512   = 512,
		Size_1024x1024 = 1024,
		Size_2048x2048 = 2048,
	};


public:
	/**
	 * @brief ���̽� �÷� ���� �������Դϴ�.
	 * 
	 * @param size ���̽� �÷� ���� ũ���Դϴ�.
	 * @param baseColor ���̽� �÷� ���� �����Դϴ�.
	 */
	BaseColorMap(const ESize& size, const Vec4f& baseColor);


	/**
	 * @brief ���̽� �÷� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BaseColorMap();


	/**
	 * @brief ���̽� �÷� ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BaseColorMap);


	/**
	 * @brief ���̽� �÷� �� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	virtual void Active(uint32_t unit) const override;


private:
	/**
	 * @brief ���̽� �÷� ���� ���� ũ���Դϴ�.
	 */
	int32_t width_ = 0;


	/**
	 * @brief ���̽� �÷� ���� ���� ũ���Դϴ�.
	 */
	int32_t height_ = 0;


	/**
	 * @brief �ؽ�ó ���ҽ��� ID ���Դϴ�.
	 */
	uint32_t textureID_ = 0;
};