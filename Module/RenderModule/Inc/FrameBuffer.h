#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief ���������� ���� �� ������ ������ ������ �����Դϴ�.
 */
class FrameBuffer : public IResource
{
public:
	/**
	 * @brief ��Ƽ ���ø� ����� ��Ȱ��ȭ�� ������ ������ �������Դϴ�.
	 *
	 * @param bufferWidth ������ ������ ���� ũ���Դϴ�.
	 * @param bufferHeight ������ ������ ���� ũ���Դϴ�.
	 */
	FrameBuffer(int32_t bufferWidth, int32_t bufferHeight);


	/**
	 * @brief ��Ƽ ���ø� ����� Ȱ��ȭ�� ������ ������ �������Դϴ�.
	 *
	 * @param bufferWidth ������ ������ ���� ũ���Դϴ�.
	 * @param bufferHeight ������ ������ ���� ũ���Դϴ�.
	 * @param sample ��Ƽ ���ø� �� ����� ���� ���Դϴ�.
	 */
	FrameBuffer(int32_t bufferWidth, int32_t bufferHeight, int32_t sample);


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
	 * @param index Ȱ��ȭ �� �÷� ������ �ε����Դϴ�.
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t index, uint32_t unit) const;


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
	 * @brief ��Ƽ ���ø��� Ȱ��ȭ �Ǿ����� Ȯ���մϴ�.
	 */
	bool bEnableMultisampling_ = false;


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
	 * @brief �÷� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t colorBufferID_[MAX_COLOR_BUFFER_COUNT] = { 0, };


	/**
	 * @brief ���� ���ٽ� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t depthStencilBufferID_ = 0;
};