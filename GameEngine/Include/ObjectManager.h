#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IObject.h"


/**
 * @brief ������Ʈ ������ �����ϴ� �Ŵ����Դϴ�.
 *
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ObjectManager : public IManager
{
public:
	/**
	 * @brief ������Ʈ ������ �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ObjectManager);


	/**
	 * @brief ������Ʈ ������ �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return ������Ʈ ������ �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static ObjectManager& Get()
	{
		static ObjectManager instance;
		return instance;
	}


	/**
	 * @brief ������Ʈ ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ������Ʈ ������ �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ������Ʈ�� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief �� ������Ʈ�� �����մϴ�.
	 *
	 * @note
	 * - ������Ʈ �Ŵ����� �ʱ�ȭ�� �������� �����Ƿ�, ��ȯ�ϴ� ������ ������ �̿��ؼ� �ʱ�ȭ�� ���� �����ؾ� �մϴ�.
	 * - ������Ʈ�� �ñ״�ó ���� �ߺ��� ������� �ʽ��ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ������Ʈ���� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return ������ ������Ʈ�� �����͸� ��ȯ�մϴ�.
	 */
	template <typename TObject>
	TObject* CreateObject(const std::string& signature)
	{
		ASSERT(!IsValidObjectKey(signature), "already exist object signature %s key...", signature.c_str());

		std::unique_ptr<TObject> object = std::make_unique<TObject>();
		objectCache_.insert({ signature, std::move(object) });

		return reinterpret_cast<TObject*>(objectCache_.at(signature).get());
	}


	/**
	 * @brief ������Ʈ �Ŵ����� �����ϴ� ������Ʈ�� ����ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ������Ʈ���� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó�� �����ϴ� ������Ʈ�� �����͸� ����ϴ�. �ñ״�ó ���� �����ϴ� ������Ʈ�� ������ �� �����͸� ��ȯ�մϴ�.
	 */
	template <typename TObject>
	TObject* GetObject(const std::string& signature)
	{
		if (!IsValidObjectKey(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TObject*>(objectCache_.at(signature).get());
	}


	/**
	 * @brief ������Ʈ �Ŵ����� �����ϴ� ������Ʈ�� �����մϴ�.
	 *
	 * @param signature ������ ������Ʈ�� �ñ״�ó ���Դϴ�.
	 */
	void DestroyObject(const std::string& signature);


private:
	/**
	 * @brief ������Ʈ ������ �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ObjectManager);


	/**
	 * @brief Ű ���� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param key ��ȿ���� Ȯ���� Ű ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ������Ʈ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValidObjectKey(const std::string& key);


private:
	/**
	 * @brief ������Ʈ �Ŵ��� ���� ������Ʈ ĳ���Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IObject>> objectCache_;
};