#pragma once

#include "ITexture.h"


/**
 * @brief ���������� ���� �� ������ ������ ������ �����Դϴ�.
 */
class FrameBuffer : public ITexture
{
public:
	/**
	 * @brief ������ ������ �������Դϴ�.
	 *
	 * @param bufferWidth ������ ������ ���� ũ���Դϴ�.
	 * @param bufferHeight ������ ������ ���� ũ���Դϴ�.
	 */
	FrameBuffer(int32_t bufferWidth, int32_t bufferHeight);


	/**
	 * @brief ������ ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~FrameBuffer();


	/**
	 * @brief ������ ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(FrameBuffer);


	/**
	 * @brief ������ ���� ������ ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ ���۸� �ʱ�ȭ�մϴ�.
	 *
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 * @param depth ���� ������ �ʱ�ȭ ���Դϴ�.
	 * @param stencil ���ٽ� ������ �ʱ�ȭ ���Դϴ�.
	 */
	void Clear(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief ������ ���۸� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ������ ������ ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ������ ������ �÷� ���� �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 * 
	 * @note ���� Ÿ�������ϴ� �÷� ������ �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 * 
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	virtual void Active(uint32_t unit) const override;


	/**
	 * @brief ������ ������ ũ�⸦ ����ϴ�.
	 *
	 * @param outWidth ������ ������ ���� ũ���Դϴ�.
	 * @param outHeight ������ ������ ���� ũ���Դϴ�.
	 */
	void GetSize(uint32_t& outWidth, uint32_t& outHeight)
	{
		outWidth = width_;
		outHeight = height_;
	}


	/**
	 * @brief ���� �÷� ���� Ÿ���� �ε����� �����մϴ�.
	 * 
	 * @param index ������ �÷� ���� Ÿ���� �ε����Դϴ�.
	 */
	void SetTargetColorBuffer(uint32_t index);


	/**
	 * @brief �� �����ӹ����� �ٸ� ������ ���۷� ���縦 �����մϴ�.
	 *
	 * @param src ���� ������ �����Դϴ�.
	 * @param dst ���縦 ������ ������ �����Դϴ�.
	 */
	static void Blit(FrameBuffer* src, FrameBuffer* dst);


private:
	/**
	 * @brief ���� ������ �ִ� ���Դϴ�.
	 */
	static const uint32_t MAX_COLOR_BUFFER_COUNT = 2;


	/**
	 * @brief ������ ���� ũ���Դϴ�.
	 */
	uint32_t width_ = 0;


	/**
	 * @brief ������ ���� ũ���Դϴ�.
	 */
	uint32_t height_ = 0;


	/**
	 * @brief ������ ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t framebufferID_ = 0;


	/**
	 * @brief ���� Ÿ�� �÷� ���� ������Ʈ�� �ε����Դϴ�.
	 */
	uint32_t targetColorBuffer_ = 0;


	/**
	 * @brief �÷� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t colorBufferID_[MAX_COLOR_BUFFER_COUNT] = { 0, };


	/**
	 * @brief ���� ���ٽ� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t depthStencilBufferID_ = 0;
};