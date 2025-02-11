#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief ���������� ���� �� ������ ������ �÷� ������ �����Դϴ�.
 */
class ColorFrameBuffer : public IResource
{
public:
	/**
	 * @brief �÷� ������ ������ ����Ʈ �������Դϴ�.
	 *
	 * @param bufferWidth ������ ������ ���� ũ���Դϴ�.
	 * @param bufferHeight ������ ������ ���� ũ���Դϴ�.
	 */
	ColorFrameBuffer(int32_t bufferWidth, int32_t bufferHeight);


	/**
	 * @brief �÷� ������ ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~ColorFrameBuffer();


	/**
	 * @brief �÷� ������ ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ColorFrameBuffer);


	/**
	 * @brief �÷� ������ ���� ������ ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �÷� ������ ���۸� �ʱ�ȭ�մϴ�.
	 *
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 */
	void Clear(float red, float green, float blue, float alpha);


	/**
	 * @brief �÷� ������ ���۸� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief �÷� ������ ������ ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief �÷� ������ ������ �÷� ���� �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 * 
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit) const;


	/**
	 * @brief �÷� ������ ũ�⸦ ����ϴ�.
	 * 
	 * @param outWidth �÷� ������ ���� ũ���Դϴ�.
	 * @param outHeight �÷� ������ ���� ũ���Դϴ�.
	 */
	void GetSize(uint32_t& outWidth, uint32_t& outHeight)
	{
		outWidth = width_;
		outHeight = height_;
	}


	/**
	 * @brief �÷� ���� ������Ʈ�� ID�� ����ϴ�.
	 * 
	 * @return �÷� ���� ������Ʈ�� ID�� ��ȯ�մϴ�.
	 */
	uint32_t GetColorBufferID() const { return colorBufferID_; }


private:
	/**
	 * @brief ������ ������ ���� ũ���Դϴ�.
	 */
	uint32_t width_ = 0;


	/**
	 * @brief ������ ������ ���� ũ���Դϴ�.
	 */
	uint32_t height_ = 0;


	/**
	 * @brief ������ ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t framebufferID_ = 0;


	/**
	 * @brief �÷� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t colorBufferID_;
};