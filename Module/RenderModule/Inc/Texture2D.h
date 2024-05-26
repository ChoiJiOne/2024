#pragma once

#include <vector>
#include <string>

#include "ITexture2D.h"


/**
 * @brief OpenGL ���������ο� ���ε� ������ �ؽ�ó ���ҽ��Դϴ�.
 */
class Texture2D : public ITexture2D
{
public:
	/**
	 * @brief �̹��� ������ �а� �ؽ�ó ���ҽ��� �����մϴ�.
	 *
	 * @param path �̹��� ������ ����Դϴ�.
	 */
	explicit Texture2D(const std::string& path);


	/**
	 * @brief �ؽ�ó�� ���� �Ҹ����Դϴ�.
	 *
	 * @note �ؽ�ó ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Texture2D();


	/**
	 * @brief �ؽ�ó�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2D);


	/**
	 * @brief �ؽ�ó�� ���� ���ҽ��� �Ҵ� �����մϴ�.
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
	 * @brief ���Ϸκ��� �ȼ� ���۸� �н��ϴ�.
	 *
	 * @param path �ȼ� ���� ����(�̹��� ����)�� ����Դϴ�.
	 * @param outWidth ������ ���� ũ���Դϴ�.
	 * @param outHeight ������ ���� ũ���Դϴ�.
	 * @param outChannels �ȼ��� ü��(1~4)�Դϴ�.
	 * @param outPixelBuffer �ȼ� �����Դϴ�.
	 * @param bIsVerticallyFlip �ȼ� ���۸� �������� �������� Ȯ���մϴ�. �⺻ ���� true�Դϴ�.
	 */
	void ReadPixelBufferFromFile(
		const std::string& path,
		int32_t& outWidth,
		int32_t& outHeight,
		int32_t& outChannels,
		std::vector<uint8_t>& outPixelBuffer,
		bool bIsVerticallyFlip = true
	);


private:
	/**
	 * @brief �ؽ�ó ���ҽ��� ID�Դϴ�.
	 */
	uint32_t textureID_ = 0;
};