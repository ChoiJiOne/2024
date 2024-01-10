#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IScene.h"


/**
 * @brief ���� ���� ���� �����ϴ� �Ŵ����Դϴ�.
 *
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class SceneManager : public IManager
{
public:
	/**
	 * @brief �� ������ �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(SceneManager);


	/**
	 * @brief �� ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return �� ������ �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static SceneManager& Get()
	{
		static SceneManager instance;
		return instance;
	}


	/**
	 * @brief �� ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief �� ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� �����մϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ���� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return ������ ���� �����͸� ��ȯ�մϴ�.
	 *
	 * @note ���� �ñ״�ó ���� �ߺ��� ������� �ʽ��ϴ�.
	 */
	template <typename TScene>
	TScene* CreateScene(const std::string& signature)
	{
		ASSERT(!IsValidSceneKey(signature), "already exist scene signature key : %s", signature.c_str());

		std::unique_ptr<TScene> scene = std::make_unique<TScene>();
		scenes_.insert({ signature, std::move(scene) });

		return reinterpret_cast<TScene*>(scenes_.at(signature).get());
	}


	/**
	 * @brief �� �Ŵ����� �����ϴ� ���ҽ��� ����ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ������ ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó�� �����ϴ� �� �����͸� ����ϴ�. �ñ״�ó ���� �����ϴ� ���� ������ �� �����͸� ��ȯ�մϴ�.
	 */
	template <typename TScene>
	TScene* GetScene(const std::string& signature)
	{
		if (!IsValidSceneKey(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TScene*>(scenes_.at(signature).get());
	}


	/**
	 * @brief �� �Ŵ����� �����ϴ� ���� �����մϴ�.
	 *
	 * @param signature ������ ���� �ñ״�ó ���Դϴ�.
	 */
	void DestroyScene(const std::string& signature);
	

private:
	/**
	 * @brief �� ������ �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(SceneManager);


	/**
	 * @brief �ñ״�ó ���� �����ϴ� ���� �����ϴ��� Ȯ���մϴ�.
	 *
	 * @param signature ���� �����ϴ� �� Ȯ���� �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó ���� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValidSceneKey(const std::string& signature);


private:
	/**
	 * @brief �� �Ŵ����� �����ϴ� ���Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IScene>> scenes_;
};