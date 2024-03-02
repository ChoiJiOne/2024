#include <array>
#include <cstdint>
#include <windows.h>
#include <vector>

#include "CrashModule.h"
#include "FileModule.h"
#include "MathModule.h"

#include "Assertion.h"
#include "AudioManager.h"
#include "ConfigManager.h"
#include "EntityManager.h"
#include "GameTimer.h"
#include "InputManager.h"
#include "PlayScene.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SDLManager.h"
#include "SettingScene.h"
#include "StartScene.h"


/**
 * @brief ���� ���ø����̼� Ŭ�����Դϴ�.
 */
class Application
{
public:
	/**
	 * @brief ���� ���ø����̼��� �������Դϴ�.
	 */
	explicit Application()
	{
		CHECK(CrashModule::RegisterExceptionFilter());

		SDLManager::Get().Startup();
		InputManager::Get().Startup();
		AudioManager::Get().Startup();
		RenderManager::Get().Startup();
		ResourceManager::Get().Startup();
		EntityManager::Get().Startup();
		ConfigManager::Get().Startup();

		RenderManager::Get().SetDepthMode(false);
		RenderManager::Get().SetAlphaBlendMode(true);
		RenderManager::Get().SetMultisampleMode(true);
	}


	/**
	 * @brief ���� ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Application()
	{
		ConfigManager::Get().Shutdown();
		EntityManager::Get().Shutdown();
		ResourceManager::Get().Shutdown();
		RenderManager::Get().Shutdown();
		AudioManager::Get().Shutdown();
		InputManager::Get().Shutdown();
		SDLManager::Get().Shutdown();

		CrashModule::UnregisterExceptionFilter();
	}


	/**
	 * @brief ���� ���ø����̼��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Application);


	/**
	 * @brief ���ø����̼� �ʱ�ȭ�� �����մϴ�.
	 */
	void Startup()
	{
		quitLoopEvent_ = [&]() { bIsDone_ = true; };

		InputManager::Get().AddWindowEventAction(EWindowEvent::CLOSE, quitLoopEvent_, true);

		startScene_ = std::make_unique<StartScene>();
		settingScene_ = std::make_unique<SettingScene>();
		playScene_ = std::make_unique<PlayScene>();
		
		StartScene* startScene = reinterpret_cast<StartScene*>(startScene_.get());
		startScene->SetQuitLoopEvent(quitLoopEvent_);
		startScene->SetSettingScene(settingScene_.get());
		startScene->SetPlayScene(playScene_.get());

		SettingScene* settingScene = reinterpret_cast<SettingScene*>(settingScene_.get());
		settingScene->SetStartScene(startScene);

		PlayScene* playScene = reinterpret_cast<PlayScene*>(playScene_.get());
		playScene->SetStartScene(startScene);

		currentScene_ = startScene;
	}


	/**
	 * @brief ���ø����̼��� �����մϴ�.
	 */
	void Run()
	{
		currentScene_->Enter();
		timer_.Reset();

		while (!bIsDone_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			currentScene_->Tick(timer_.GetDeltaSeconds());

			if (currentScene_->IsDetectSwitch())
			{
				currentScene_->Exit();
				currentScene_ = currentScene_->GetLink();
				currentScene_->Enter();
			}
		}
	}


	/**
	 * @brief ���ø����̼��� ������ �����մϴ�.
	 */
	void Shutdown()
	{
	}


private:
	/**
	 * @brief ���� ���� �����Դϴ�.
	 */
	bool bIsDone_ = false;


	/**
	 * @brief ���� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> quitLoopEvent_;


	/**
	 * @brief ���� Ÿ�̸��Դϴ�.
	 */
	GameTimer timer_;


	/**
	 * @brief ���� ���Դϴ�.
	 */
	std::unique_ptr<IScene> startScene_ = nullptr;


	/**
	 * @brief ���� ���Դϴ�.
	 */
	std::unique_ptr<IScene> settingScene_ = nullptr;


	/**
	 * @brief �÷��� ���Դϴ�.
	 */
	std::unique_ptr<IScene> playScene_ = nullptr;


	/**
	 * @brief ���� ���Դϴ�.
	 */
	IScene* currentScene_ = nullptr;
};

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->Startup();
	app->Run();
	app->Shutdown();
	return 0;
}