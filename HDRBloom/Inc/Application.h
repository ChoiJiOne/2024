#pragma once

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

#include "BloomEffector.h"
#include "ColorFrameBuffer.h"
#include "FrameBuffer.h"
#include "FrameRenderer.h"
#include "GaussianBlurEffector.h"
#include "GeometryRenderer2D.h"
#include "TextRenderer2D.h"
#include "TTFont.h"


/**
 * @brief ���ø����̼��� �ʱ�ȭ/����/�����ϴ� Ŭ�����Դϴ�.
 */
class Application
{
public:
	/**
	 * @brief ���ø����̼��� �������Դϴ�.
	 */
	Application();


	/**
	 * @brief ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Application();


	/**
	 * @brief ���÷����̼��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Application);


	/**
	 * @brief ���ø����̼��� �ʱ�ȭ�մϴ�.
	 */
	void Init();


	/**
	 * @brief ���ø����̼��� �����մϴ�.
	 */
	void Run();
	

private:
	/**
	 * @brief ��Ƽ ���ø��� �����ϴ� ������ �����Դϴ�.
	 */
	FrameBuffer* multisampleScene_ = nullptr;


	/**
	 * @brief ��Ƽ ���ø��� �������� �ʴ� ������ �����Դϴ�.
	 */
	FrameBuffer* scene_ = nullptr;


	/**
	 * @brief ����þ� �� �� ����� ���� ���� ������ �����Դϴ�.
	 */
	ColorFrameBuffer* pingpong_[2] = { nullptr, nullptr };


	/**
	 * @brief 2D ���� ������ �׸��� ������ �Դϴ�.
	 */
	GeometryRenderer2D* geometryRenderer_ = nullptr;


	/**
	 * @brief 2D �ؽ�Ʈ�� �׸��� �������Դϴ�.
	 */
	TextRenderer2D* textRenderer_ = nullptr;


	/**
	 * @brief 2D ������ ���۸� �׸��� �������Դϴ�.
	 */
	FrameRenderer* frameRenderer_ = nullptr;


	/**
	 * @brief ����þ� �� ȿ���� �����ϴ� �������Դϴ�.
	 */
	GaussianBlurEffector* gaussianBlurEffector_ = nullptr;


	/**
	 * @brief ��� ȿ���� �����ϴ� �������Դϴ�.
	 */
	BloomEffector* bloomEffector_ = nullptr;


	/**
	 * @brief ��Ʈ ���ҽ��Դϴ�.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief ��� ȿ���� Ȱ��ȭ �� �� Ȯ���մϴ�.
	 */
	bool bIsActiveBloom_ = true;


	/**
	 * @brief �ؽ�Ʈ �÷��Դϴ�.
	 */
	Vec4f textColor_ = Vec4f(5.0f, 0.0f, 0.0f, 1.0f);


	/**
	 * @brief �ܰ��� �����Դϴ�.
	 */
	Vec4f outlineColor_ = Vec4f(5.0f, 0.0f, 0.0f, 1.0f);
};