#pragma once

#include <cstdint>

#include "Vec4.h"

#include "IResource.h"


/**
 * @brief ���� Ÿ�� ���Դϴ�.
 * 
 * @note
 * - ���� Ÿ�ϸ��� ũ��� �ݵ�� 2^n �Դϴ�.
 * - ���� Ÿ�ϸ��� ũ��� �ܺο��� Ư���� �����θ� ������ �� �ֽ��ϴ�.
 */
class TileMap : public IResource
{
public:
	/**
	 * @brief ���� Ÿ�ϸ��� ũ���Դϴ�.
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
	 * @brief ���� Ÿ�ϸ��� �������Դϴ�.
	 * 
	 * @param size Ÿ�ϸ� ��ü�� ũ���Դϴ�.
	 * @param tileSize Ÿ�� �ϳ��� ũ���Դϴ�.
	 * @param pattern0 Ÿ���� ù ��° ���� �����Դϴ�.
	 * @param pattern1 Ÿ���� �� ��° ���� �����Դϴ�.
	 */
	TileMap(const ESize& size, const ESize& tileSize, const Vec4f& pattern0 = Vec4f(1.0f, 1.0f, 1.0f, 1.0f), const Vec4f& pattern1 = Vec4f(0.0f, 0.0f, 0.0f, 1.0f));


	/**
	 * @brief ���� Ÿ�ϸ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~TileMap();


	/**
	 * @brief ���� Ÿ�ϸ��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TileMap);


	/**
	 * @brief ���� Ÿ�ϸ� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit) const;


	/**
	 * @brief �ؽ�ó�� ID ���� ����ϴ�.
	 * 
	 * @return �ؽ�ó�� ID ���� ��ȯ�մϴ�.
	 */
	uint32_t GetID() const { return textureID_; }


private:
	/**
	 * @brief ���� Ÿ�ϸ��� ���� ũ���Դϴ�.
	 * 
	 * @note ���� Ÿ�ϸ��� ũ��� �ݵ�� 2^n �Դϴ�.
	 */
	int32_t width_ = 0;


	/**
	 * @brief ���� Ÿ�ϸ��� ���� ũ���Դϴ�.
	 * 
	 * @note ���� Ÿ�ϸ��� ũ��� �ݵ�� 2^n �Դϴ�.
	 */
	int32_t height_ = 0;


	/**
	 * @brief �ؽ�ó ���ҽ��� ID ���Դϴ�.
	 */
	uint32_t textureID_ = 0;
};