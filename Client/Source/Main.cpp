#include "IApplication.h"

#include "GameScene.h"
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

		TTFont* font32 = ResourceManager::Get().CreateResource<TTFont>("Font32");
		font32->Initialize(clientPath_ + L"Resource/SeoulNamsanEB.ttf", 32, 127, 32.0f);

		TTFont* font64 = ResourceManager::Get().CreateResource<TTFont>("Font64");
		font64->Initialize(clientPath_ + L"Resource/SeoulNamsanEB.ttf", 32, 127, 64.0f);

		TTFont* font128 = ResourceManager::Get().CreateResource<TTFont>("Font128");
		font128->Initialize(clientPath_ + L"Resource/SeoulNamsanEB.ttf", 32, 127, 128.0f);

		startScene_ = SceneManager::Get().CreateScene<StartScene>("StartScene");
		gameScene_ = SceneManager::Get().CreateScene<GameScene>("GameScene");
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
		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			startScene_->Tick(timer_.GetDeltaSeconds());
			//gameScene_->Tick(timer_.GetDeltaSeconds());
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
	 * @brief ���� ���� ���Դϴ�.
	 */
	StartScene* startScene_ = nullptr;


	/**
	 * @brief ���� �÷��� ���Դϴ�.
	 */
	GameScene* gameScene_ = nullptr;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}