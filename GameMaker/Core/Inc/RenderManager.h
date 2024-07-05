#pragma once

#include "IManager.h"


namespace GameMaker
{
class Renderer2D;
class Renderer3D;


/**
 * @brief �⺻ ������ �׸��� ����Դϴ�.
 */
enum class EDrawMode : int32_t
{
	POINTS       = 0x0000,
	LINES        = 0x0001,
	LINE_STRIP   = 0x0003,
	TRIANGLES    = 0x0004,
	TRIANGLE_FAN = 0x0006,
	NONE         = 0xFFFF,
};


/**
 * @brief ������ ���� ó���� ����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief ���� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief ���� �Ŵ����� �����ڸ� ����ϴ�.
	 *
	 * @return ���� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static RenderManager& Get();


	/**
	 * @brief ���� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ������ �������� �����մϴ�.
	 *
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 * @param depth ���� ������ �ʱ�ȭ ���Դϴ�.
	 * @param stencil ���ٽ� ������ �ʱ�ȭ ���Դϴ�.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief ����ۿ� ����Ʈ ���۸� �����մϴ�.
	 *
	 * @return ����ۿ� ����Ʈ ������ ���ҿ� �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	void EndFrame();


	/**
	 * @brief �� ��Ʈ�� �����մϴ�.
	 *
	 * @param x ����Ʈ �簢���� ���� �Ʒ� �𼭸�(�ȼ�)�Դϴ�. �⺻���� (0,0)�Դϴ�.
	 * @param y ����Ʈ �簢���� ���� �Ʒ� �𼭸�(�ȼ�)�Դϴ�. �⺻���� (0,0)�Դϴ�.
	 * @param width ����Ʈ�� �ʺ��Դϴ�. OpenGL ���ؽ�Ʈ�� â�� ó�� ����Ǹ� �ʺ� �� ���� �� �ش� â�� ũ��� �����˴ϴ�.
	 * @param height ����Ʈ�� �����Դϴ�. OpenGL ���ؽ�Ʈ�� â�� ó�� ����Ǹ� �ʺ� �� ���� �� �ش� â�� ũ��� �����˴ϴ�.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * @brief ������ �� ��Ʈ�� �����մϴ�.
	 */
	void SetWindowViewport();


	/**
	 * @brief ���� ����ȭ �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ���� ����ȭ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief ���� �׽�Ʈ �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ���� �׽�Ʈ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief ���ٽ� �׽�Ʈ �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ���ٽ� �׽�Ʈ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetStencilMode(bool bIsEnable);


	/**
	 * @brief ���� ���� �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ���� ���� �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetAlphaBlendMode(bool bIsEnable);


	/**
	 * @brief ��Ƽ ���ø� �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ��Ƽ ���ø� �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetMultisampleMode(bool bIsEnable);


	/**
	 * @brief ���̴��� ����Ʈ ũ�� �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ����Ʈ ũ�� �ɼ��� Ȱ��ȭ�Ϸ��� true, �׷��� ������ false�Դϴ�.
	 */
	void SetPointSizeMode(bool bIsEnable);


	/**
	 * @brief ���̽� �ø� ��� �ɼ��� �����մϴ�.
	 *
	 * @param bIsEnable ���̽� �ø� ��带 Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetCullFaceMode(bool bIsEnable);


	/**
	 * @brief ���������ο� ���ε��� ���ҽ��� ������� �׸��⸦ �����մϴ�.
	 *
	 * @param vertexCount �׸��� ���� �� ������ ���ؽ� ������ ���Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 */
	void ExecuteDrawVertex(uint32_t vertexCount, const EDrawMode& drawMode);


	/**
	 * @brief ���������ο� ���ε��� ���ҽ��� ������� �׸��⸦ �����մϴ�.
	 *
	 * @param vertexCount �׸��� ���� �� ������ ���ؽ� ������ ���Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 * @param instanceCount �ν��Ͻ� ī��Ʈ�Դϴ�.
	 */
	void ExecuteDrawVertexInstanced(uint32_t vertexCount, const EDrawMode& drawMode, uint32_t instanceCounts);


	/**
	 * @brief ���������ο� ���ε��� ���ҽ��� ������� �׸��⸦ �����մϴ�.
	 *
	 * @param indexCount �׸��� ���� �� ������ �ε��� ������ ���Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 */
	void ExecuteDrawIndex(uint32_t indexCount, const EDrawMode& drawMode);


	/**
	 * @brief ���������ο� ���ε��� ���ҽ��� ������� �׸��⸦ �����մϴ�.
	 *
	 * @param indexCount �׸��� ���� �� ������ �ε��� ������ ���Դϴ�.
	 * @param drawMode �׸��� ����Դϴ�.
	 * @param instanceCount �ν��Ͻ� ī��Ʈ�Դϴ�.
	 */
	void ExecuteDrawIndexInstanced(uint32_t indexCount, const EDrawMode& drawMode, uint32_t instanceCounts);


	/**
	 * @brief ��ũ���� ũ�⸦ ����ϴ�.
	 * 
	 * @param outWidth ��ũ���� ���� ũ���Դϴ�.
	 * @param outHeight ��ũ���� ���� ũ���Դϴ�.
	 */
	template <typename T>
	void GetScreenSize(T& outWidth, T& outHeight);


private:
	/**
	 * @brief ���� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief ������ ����� �Ǵ� ������ �������Դϴ�.
	 */
	void* window_ = nullptr;
	

	/**
	 * @brief OpenGL ���ؽ�Ʈ�Դϴ�.
	 */
	void* context_ = nullptr;
};

}