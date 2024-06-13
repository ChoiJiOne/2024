#pragma once

#include "Vec.h"

#include "ITexture.h"


/**
 * @brief Ÿ�� �÷� ���Դϴ�.
 *
 * @note
 * - �ؽ�ó�� ũ��� �ݵ�� 2^n �����Դϴ�.
 * - �ؽ�ó�� ũ��� ������ ���������θ� ������ �� �ֽ��ϴ�.
 */
class TileColorMap : public ITexture
{
public:
	/**
	 * @brief Ÿ�� ������ ũ���Դϴ�.
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
	 * @brief Ÿ�� ���� �������Դϴ�.
	 *
	 * @param boardSize Ÿ�ϸ� ��ü�� ũ���Դϴ�.
	 * @param tileSize Ÿ�� �� �ϳ��� ũ���Դϴ�.
	 * @param color0 Ÿ���� ù ��° ���� �����Դϴ�.
	 * @param color1 Ÿ���� �� ��° ���� �����Դϴ�.
	 */
	TileColorMap(const ESize& boardSize, const ESize& tileSize, const Vec4f& color0 = Vec4f(1.0f, 1.0f, 1.0f, 1.0f), const Vec4f& color1 = Vec4f(0.0f, 0.0f, 0.0f, 1.0f));


	/**
	 * @brief Ÿ�� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~TileColorMap();


	/**
	 * @brief Ÿ�� ���� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TileColorMap);


	/**
	 * @brief Ÿ�� �� ���� ���ҽ��� �Ҵ� �����մϴ�.
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
	 * @brief Ÿ�� ���� ���� ũ���Դϴ�.
	 */
	int32_t width_ = 0;


	/**
	 * @brief Ÿ�� ���� ���� ũ���Դϴ�.
	 */
	int32_t height_ = 0;


	/**
	 * @brief �ؽ�ó ���ҽ��� ID ���Դϴ�.
	 */
	uint32_t textureID_ = 0;
};