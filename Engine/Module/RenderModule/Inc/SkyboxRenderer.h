#pragma once

#include <array>

#include "IResource.h"
#include "RenderModule.h"
#include "VertexBuffer.h"

class Shader;
class Skybox;


/**
 * @brief ��ī�� �ڽ��� �������ϴ� �������Դϴ�.
 */
class SkyboxRenderer : public IResource
{
public:
	/**
	 * @brief ��ī�� �ڽ��� �׸��� �������� �������Դϴ�.
	 */
	explicit SkyboxRenderer();


	/**
	 * @brief ��ī�� �ڽ��� �׸��� �������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~SkyboxRenderer();


	/**
	 * @brief ��ī�� �ڽ��� �׸��� �������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(SkyboxRenderer);


	/**
	 * @brief ������ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ��ī�� �ڽ� �׸��⸦ �����մϴ�.
	 *
	 * @param view ���ε��� ������ ���ۿ� �׸� �� ������ �þ� ����Դϴ�.
	 * @param projection ���ε��� ������ ���ۿ� �׸� �� ������ ���� ����Դϴ�.
	 * @param skybox ���ε��� ������ ���ۿ� �׸� ��ī�� �ڽ��Դϴ�.
	 */
	void Draw(const Mat4x4& view, const Mat4x4& projection, const Skybox* skybox);


private:
	/**
	 * @brief ��ī�� �ڽ��� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief ��ī�� �ڽ� ������ ���Դϴ�.
	 */
	uint32_t vertexCount_ = 0;


	/**
	 * @brief ��ī�� �ڽ��� ���� �����Դϴ�.
	 */
	VertexBuffer* vertexBuffer_ = nullptr;


	/**
	 * @brief ��ī�� �ڽ��� �������ϴ� ���̴��Դϴ�.
	 */
	Shader* shader_ = nullptr;


	/**
	 * @brief ��ī�� �ڽ� �ؽ�ó�� ���ε� �����Դϴ�.
	 */
	static const uint32_t SKYBOX_BIND_SLOT = 0;
};