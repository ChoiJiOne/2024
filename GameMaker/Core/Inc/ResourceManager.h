#pragma once

#include <array>
#include <memory>

#include "IManager.h"
#include "IResource.h"


namespace GameMaker
{
/**
 * @brief ������ ���ҽ��� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ResourceManager : public IManager
{
public:
	/**
	 * @brief ���ҽ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ResourceManager);


	/**
	 * @brief ���ҽ� �Ŵ����� �����ڸ� ����ϴ�.
	 *
	 * @return ���ҽ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static ResourceManager& Get();


	/**
	 * @brief ���ҽ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���ҽ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���ҽ��� �����մϴ�.
	 *
	 * @param args ���ҽ��� �����ڿ� ������ ���ڵ��Դϴ�.
	 *
	 * @return ������ ���ҽ��� �����͸� ��ȯ�մϴ�. ���ҽ� ������ �����ϸ� nullptr�� ��ȯ�մϴ�.
	 */
	template <typename TResource, typename... Args>
	TResource* Create(Args&&... args)
	{
		if (!(0 <= cacheSize_ && cacheSize_ < MAX_RESOURCE_SIZE))
		{
			return nullptr;
		}

		int32_t resourceID = -1;
		for (uint32_t index = 0; index < cacheSize_; ++index)
		{
			if (!cache_[index] && !usage_[index])
			{
				resourceID = static_cast<int32_t>(index);
				break;
			}
		}

		if (resourceID == -1)
		{
			resourceID = cacheSize_++;
		}

		usage_[resourceID] = true;
		cache_[resourceID] = std::make_unique<TResource>(args...);

		return reinterpret_cast<TResource*>(cache_[resourceID].get());
	}


	/**
	 * @brief ���ҽ� �Ŵ����� �����ϴ� ���ҽ��� �����մϴ�.
	 *
	 * @param resource ������ ���ҽ� �������Դϴ�.
	 */
	void Destroy(const IResource* resource)
	{
		int32_t resourceID = -1;
		for (uint32_t index = 0; index < cacheSize_; ++index)
		{
			IResource* cacheResource = cache_[index].get();
			if (resource == cacheResource)
			{
				resourceID = static_cast<int32_t>(index);
				break;
			}
		}

		if (resourceID != -1 && cache_[resourceID])
		{
			if (cache_[resourceID]->IsInitialized())
			{
				cache_[resourceID]->Release();
			}

			cache_[resourceID].reset();
			usage_[resourceID] = false;
		}
	}


private:
	/**
	 * @brief ���ҽ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ResourceManager);


private:
	/**
	 * @brief ������ �� �ִ� �ִ� ���ҽ� ���Դϴ�.
	 */
	static const uint32_t MAX_RESOURCE_SIZE = 200;


	/**
	 * @brief ĳ�� ũ���Դϴ�.
	 */
	uint32_t cacheSize_ = 0;


	/**
	 * @brief ���ҽ��� ĳ���Դϴ�.
	 */
	std::array<std::unique_ptr<IResource>, MAX_RESOURCE_SIZE> cache_;


	/**
	 * @brief ���ҽ��� ��� �����Դϴ�.
	 */
	std::array<bool, MAX_RESOURCE_SIZE> usage_;
};

}