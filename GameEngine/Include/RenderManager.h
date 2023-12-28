#pragma once

#include <cstdint>
#include <unordered_map>
#include <windows.h>

#include "IManager.h"
#include "Matrix4x4.h"

class Window;
class Shader;
class Mesh;
class Texture2D;


/**
 * @brief ������ ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return ������ ó���� �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static RenderManager& Get()
	{
		static RenderManager instance;
		return instance;
	}


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 * 
	 * @note 
	 * - �� �޼��� ȣ�� ���� ������ ����� �Ǵ� ������ �����͸� �����ؾ� �մϴ�.
	 * - �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 * 
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ������ ����� �Ǵ� �����츦 �����մϴ�.
	 * 
	 * @param window ������ ����� �Ǵ� �������Դϴ�.
	 */
	void SetRenderTargetWindow(Window* window) { renderTargetWindow_ = window; }


	/**
	 * @brief ������ ����� �Ǵ� �����츦 ����ϴ�.
	 * 
	 * @return ������ ����� �Ǵ� �������� �����͸� ��ȯ�մϴ�.
	 */
	Window* GetRenderTargetWindow() const { return renderTargetWindow_; }


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
	 * @brief 3D �޽ø� ���� ������ �̿��ؼ� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param world ���� ����Դϴ�.
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param mesh ȭ�鿡 �׸� �޽� ���ҽ��Դϴ�.
	 */
	void RenderMesh3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, const Mesh* mesh);


	/**
	 * @brief 3D �޽ø� �ؽ�ó�� �̿��ؼ� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param mesh ȭ�鿡 �׸� �޽� ���ҽ��Դϴ�.
	 * @param textureMap ȭ�鿡 �׸� �޽��� �ؽ�ó ���ҽ��Դϴ�.
	 */
	void RenderMesh3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, const Mesh* mesh, const Texture2D* textureMap);


private:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief ������ ����� �Ǵ� ������ �������Դϴ�.
	 */
	Window* renderTargetWindow_ = nullptr;


	/**
	 * @brief ���� ����ȭ Ȱ��ȭ �����Դϴ�. �⺻ ���� ��Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableVsync_ = false;


	/**
	 * @brief ���� �׽�Ʈ Ȱ��ȭ �����Դϴ�. �⺻ ���� Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableDepth_ = true;


	/**
	 * @brief ���ٽ� �׽�Ʈ Ȱ��ȭ �����Դϴ�. �⺻ ���� ��Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableStencil_ = false;


	/**
	 * @brief ���� ���� Ȱ��ȭ �����Դϴ�. �⺻ ���� Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableAlphaBlend_ = true;


	/**
	 * @brief �������� ����� ����̽� ���ؽ�Ʈ�� �ڵ��Դϴ�.
	 */
	HDC deviceContext_ = nullptr;


	/**
	 * @brief �������� ����� OpenGL ���ؽ�Ʈ�� �ڵ��Դϴ�.
	 */
	HGLRC glRenderContext_ = nullptr;


	/**
	 * @brief ���̴� ���ҽ��� ����Դϴ�.
	 */
	std::wstring shaderPath_;

	
	/**
	 * @brief ���� �Ŵ������� ����� ���̴� ĳ���Դϴ�.
	 */
	std::unordered_map<std::wstring, Shader*> shaderCache_;
};