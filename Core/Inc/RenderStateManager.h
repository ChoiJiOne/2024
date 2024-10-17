#pragma once

#include <vector>

#include "GameMath.h"
#include "Macro.h"

enum class DrawMode : int32_t
{
	POINTS       = 0x0000,
	LINES        = 0x0001,
	LINE_STRIP   = 0x0003,
	TRIANGLES    = 0x0004,
	TRIANGLE_FAN = 0x0006,
	NONE         = 0xFFFF,
};

/** ������ ���� �Ŵ����� �̱����Դϴ�. */
class RenderStateManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderStateManager);

	static RenderStateManager& GetRef();
	static RenderStateManager* GetPtr();

	int32_t GetNumVideoDisplay();
	void GetVideoDisplaySize(int32_t index, Vec2i& outSize);

	template <typename T>
	void GetScreenSize(T& outWidth, T& outHeight);

	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
	void SetWindowViewport();
	void SetVsyncMode(bool bIsEnable);
	void SetDepthMode(bool bIsEnable);
	void SetStencilMode(bool bIsEnable);
	void SetAlphaBlendMode(bool bIsEnable);
	void SetMultisampleMode(bool bIsEnable);
	void SetCullFaceMode(bool bIsEnable);
	bool HasGLExtension(const std::string& extension);

	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);
	void EndFrame();

private:
	friend class IApp;

	RenderStateManager() = default;
	virtual ~RenderStateManager() {}

	void PreStartup(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */
	void PostStartup(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */
	void Shutdown(); /** IApp ���ο����� ����ϴ� �޼����Դϴ�. */

private:
	static RenderStateManager instance_;

	void* window_ = nullptr; /** ������ ����� �Ǵ� ������. ���� ���� �Ŵ��� ���ο��� �Ҵ� ������ �����ϸ� �ȵ�! */
	void* context_ = nullptr; /** OpenGL ���ؽ�Ʈ */

	int32_t numVideoDisplay_ = 0;
	std::vector<Vec2i> displaySizes_;

	std::vector<std::string> extensions_; /** OpenGL Ȯ���� ����Դϴ�. */
};