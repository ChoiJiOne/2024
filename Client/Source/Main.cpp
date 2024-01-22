#include "IApplication.h"

#include "GameScene.h"
#include "RankScene.h"
#include "StartScene.h"


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

		window_->SetIcon(clientPath_ + L"Resource/Icon/Icon.ico");

		TTFont* font32 = ResourceManager::Get().CreateResource<TTFont>("Font32");
		font32->Initialize(clientPath_ + L"Resource/Font/SeoulNamsanEB.ttf", 32, 127, 32.0f);

		TTFont* font64 = ResourceManager::Get().CreateResource<TTFont>("Font64");
		font64->Initialize(clientPath_ + L"Resource/Font/SeoulNamsanEB.ttf", 32, 127, 64.0f);

		TTFont* font128 = ResourceManager::Get().CreateResource<TTFont>("Font128");
		font128->Initialize(clientPath_ + L"Resource/Font/SeoulNamsanEB.ttf", 32, 127, 128.0f);

		Sound* buttonClickSound = ResourceManager::Get().CreateResource<Sound>("ButtonClick");
		buttonClickSound->Initialize(clientPath_ + L"Resource/Sound/ButtonClick.mp3");
		buttonClickSound->SetLooping(false);

		Sound* hitSound = ResourceManager::Get().CreateResource<Sound>("Hit");
		hitSound->Initialize(clientPath_ + L"Resource/Sound/Hit.mp3");
		hitSound->SetLooping(false);

		loopQuitEvent_ = [&]() { bIsDoneLoop_ = true; };

		startScene_ = SceneManager::Get().CreateScene<StartScene>("StartScene");
		gameScene_ = SceneManager::Get().CreateScene<GameScene>("GameScene");
		rankScene_ = SceneManager::Get().CreateScene<RankScene>("RankScene");

		startScene_->SetLoopQuitEvent(loopQuitEvent_);
		startScene_->SetNextScene(gameScene_);

		gameScene_->SetLoopQuitEvent(loopQuitEvent_);
		gameScene_->SetNextResetScene(startScene_);
		gameScene_->SetNextRankScene(rankScene_);

		rankScene_->SetLoopQuitEvent(loopQuitEvent_);
		rankScene_->SetNextScene(startScene_);
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
		IScene* currentScene = startScene_;
		currentScene->EnterScene();

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			currentScene->Tick(timer_.GetDeltaSeconds());

			if (currentScene->DetectSwitchScene())
			{
				currentScene->ExitScene();
				currentScene = currentScene->GetNextScene();
				currentScene->EnterScene();
			}
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


	/**
	 * @brief ���� ���� ���� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;


	/**
	 * @brief ���� ���� ���Դϴ�.
	 */
	StartScene* startScene_ = nullptr;


	/**
	 * @brief ���� �÷��� ���Դϴ�.
	 */
	GameScene* gameScene_ = nullptr;


	/**
	 * @brief �÷��̾��� ��ŷ�� �����ִ� ���Դϴ�.
	 */
	RankScene* rankScene_ = nullptr;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}