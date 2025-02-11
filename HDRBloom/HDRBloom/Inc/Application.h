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
 * @brief 어플리케이션을 초기화/실행/해제하는 클래스입니다.
 */
class Application
{
public:
	/**
	 * @brief 어플리케이션의 생성자입니다.
	 */
	Application();


	/**
	 * @brief 어플리케이션의 가상 소멸자입니다.
	 */
	virtual ~Application();


	/**
	 * @brief 어플레케이션의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Application);


	/**
	 * @brief 어플리케이션을 초기화합니다.
	 */
	void Init();


	/**
	 * @brief 어플리케이션을 실행합니다.
	 */
	void Run();
	

private:
	/**
	 * @brief 멀티 샘플링을 수행하는 프레임 버퍼입니다.
	 */
	FrameBuffer* multisampleScene_ = nullptr;


	/**
	 * @brief 멀티 샘플링을 수행하지 않는 프레임 버퍼입니다.
	 */
	FrameBuffer* scene_ = nullptr;


	/**
	 * @brief 가우시안 블러 시 사용할 핑퐁 색상 프레임 버퍼입니다.
	 */
	ColorFrameBuffer* pingpong_[2] = { nullptr, nullptr };


	/**
	 * @brief 2D 기하 도형을 그리는 렌더러 입니다.
	 */
	GeometryRenderer2D* geometryRenderer_ = nullptr;


	/**
	 * @brief 2D 텍스트를 그리는 렌더러입니다.
	 */
	TextRenderer2D* textRenderer_ = nullptr;


	/**
	 * @brief 2D 프레임 버퍼를 그리는 렌더러입니다.
	 */
	FrameRenderer* frameRenderer_ = nullptr;


	/**
	 * @brief 가우시안 블러 효과를 적용하는 이펙터입니다.
	 */
	GaussianBlurEffector* gaussianBlurEffector_ = nullptr;


	/**
	 * @brief 블룸 효과를 적용하는 이펙터입니다.
	 */
	BloomEffector* bloomEffector_ = nullptr;


	/**
	 * @brief 폰트 리소스입니다.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief 블룸 효과를 활성화 할 지 확인합니다.
	 */
	bool bIsActiveBloom_ = true;


	/**
	 * @brief 텍스트 컬러입니다.
	 */
	Vec4f textColor_ = Vec4f(5.0f, 0.0f, 0.0f, 1.0f);


	/**
	 * @brief 외곽선 색상입니다.
	 */
	Vec4f outlineColor_ = Vec4f(5.0f, 0.0f, 0.0f, 1.0f);
};