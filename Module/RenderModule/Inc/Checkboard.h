#pragma once

#include "Vec.h"

#include "ITexture2D.h"


/**
 * @brief 2D üũ ���� �ؽ�ó�Դϴ�.
 *
 * @note
 * - üũ ������ ũ��� �ݵ�� 2^n �Դϴ�.
 * - üũ ������ ũ��� �ܺο��� Ư���� �����θ� ������ �� �ֽ��ϴ�.
 */
class Checkboard : public ITexture2D
{
public:
	/**
	 * @brief üũ ������ ũ���Դϴ�.
	 */
	enum class ESize
	{
		Size_2x2 = 2,
		Size_4x4 = 4,
		Size_8x8 = 8,
		Size_16x16 = 16,
		Size_32x32 = 32,
		Size_64x64 = 64,
		Size_128x128 = 128,
		Size_256x256 = 256,
		Size_512x512 = 512,
		Size_1024x1024 = 1024,
		Size_2048x2048 = 2048,
	};


public:
	/**
	 * @brief üũ ������ �������Դϴ�.
	 *
	 * @param boardSize Ÿ�ϸ� ��ü�� ũ���Դϴ�.
	 * @param size üũ ���� �ϳ��� ũ���Դϴ�.
	 * @param color0 Ÿ���� ù ��° ���� �����Դϴ�.
	 * @param color1 Ÿ���� �� ��° ���� �����Դϴ�.
	 */
	Checkboard(const ESize& boardSize, const ESize& size, const Vec4f& color0 = Vec4f(1.0f, 1.0f, 1.0f, 1.0f), const Vec4f& color1 = Vec4f(0.0f, 0.0f, 0.0f, 1.0f));


	/**
	 * @brief üũ ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Checkboard();


	/**
	 * @brief üũ ������ ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Checkboard);


	/**
	 * @brief üũ ���� ���� ���ҽ��� �Ҵ� �����մϴ�.
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
	 * @brief üũ ������ ���� ũ���Դϴ�.
	 *
	 * @note üũ ������ ũ��� �ݵ�� 2^n �Դϴ�.
	 */
	int32_t width_ = 0;


	/**
	 * @brief üũ ������ ���� ũ���Դϴ�.
	 *
	 * @note üũ ������ ũ��� �ݵ�� 2^n �Դϴ�.
	 */
	int32_t height_ = 0;


	/**
	 * @brief �ؽ�ó ���ҽ��� ID ���Դϴ�.
	 */
	uint32_t textureID_ = 0;
};