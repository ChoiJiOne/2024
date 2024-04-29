#pragma once

#include <cstdint>

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
		Size_128x128 = 128,
		Size_256x256 = 256,
		Size_512x512 = 512,
		Size_1024x1024 = 1024,
		Size_2048x2048 = 2048,
	};


public:
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
};