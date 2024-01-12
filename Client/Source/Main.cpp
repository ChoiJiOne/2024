#include "IApplication.h"

#include "DemoScene.h"

#include <imgui.h>
#include <miniaudio.h>

/**
 * @brief ���� ���ø����̼��Դϴ�.
 */
class GameApplication : public IApplication
{
public:
	/**
	 * @brief ���� ���ø����̼��� ����Ʈ �������Դϴ�.
	 */
	GameApplication() = default;


	/**
	 * @brief ���� ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameApplication()
	{
		Shutdown();
	}


	/**
	 * @brief ���� ���ø����̼��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameApplication);


	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		clientPath_ = rootPath_ + L"Client/";
	}


	/**
	 * @brief ���� �����ӿ�ũ ����� �����մϴ�.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief ���� �����ӿ�ũ�� �����մϴ�.
	 */
	virtual void Run() override
	{
		int32_t width;
		int32_t height;
		window_->GetSize(width, height);

		Camera3D* camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
		camera->Initialize(
			Vector3f(5.0f, 5.0f, 5.0f), 
			Vector3f(-1.0f, -1.0f, -1.0f), 
			Vector3f(0.0f, 1.0f, 0.0f),
			MathUtils::ToRadian(45.0f),
			window_->GetAspectSize(),
			0.1f,
			100.0f
		);

		Framebuffer* framebuffer = ResourceManager::Get().CreateResource<Framebuffer>("framebuffer");
		framebuffer->Initialize(width, height);

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			framebuffer->Bind();
			RenderManager::Get().SetViewport(0, 0, width, height);
			{
				framebuffer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
				RenderManager::Get().RenderGrid3D(camera, -5.0f, 5.0f, 1.0f, -5.0f, 5.0f, 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
				RenderManager::Get().RenderWireframeSphere3D(camera, Vector3f(1.0f, 0.0f, 0.0f), 0.5f, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
			}
			framebuffer->Unbind();

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			{
				RenderManager::Get().SetViewport(0, 0, width / 2, height / 2);
				PostEffectShader* effect = ResourceManager::Get().GetResource<PostEffectShader>("InversionEffect");
				effect->Bind();
				effect->BlitEffect(framebuffer);
				effect->Unbind();
			}
			{
				RenderManager::Get().SetViewport(width / 2, 0, width / 2, height / 2);
				PostEffectShader* effect = ResourceManager::Get().GetResource<PostEffectShader>("GrayscaleEffect");
				effect->Bind();
				effect->BlitEffect(framebuffer);
				effect->Unbind();
			}
			{
				RenderManager::Get().SetViewport(0, height / 2, width / 2, height / 2);
				PostEffectShader* effect = ResourceManager::Get().GetResource<PostEffectShader>("GaussianBlurEffect");
				effect->Bind();
				effect->SetUniform("blurBias", 0.5f);
				effect->BlitEffect(framebuffer);
				effect->Unbind();
			}
			{
				RenderManager::Get().SetViewport(width / 2, height / 2, width / 2, height / 2);
				PostEffectShader* effect = ResourceManager::Get().GetResource<PostEffectShader>("FadeEffect");
				effect->Bind();
				effect->SetUniform("fadeBias", std::abs(MathUtils::Sin(timer_.GetTotalSeconds())));
				effect->BlitEffect(framebuffer);
				effect->Unbind();
			}
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief Ŭ���̾�Ʈ ����Դϴ�.
	 */
	std::wstring clientPath_;


	/**
	 * @brief ���� Ÿ�̸��Դϴ�.
	 */
	GameTimer timer_;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}