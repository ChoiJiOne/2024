#include <array>
#include <cstdint>
#include <memory>

#include "IEntity.h"


/**
 * @brief ���� ��ƼƼ�� �����ϴ� ���� ����Դϴ�.
 * 
 * @note �� Ŭ������ ��� ��� ������ �޼���� ��� ����(static) Ÿ���Դϴ�.
 */
class GameModule
{
public:
	/**
	 * @brief ���� ����� ���� ó�� ����Դϴ�.
	 */
	enum class Errors
	{
		OK            = 0x00, // ������ �����ϴ�.
		FAILED        = 0x01, // �Ϲ����� �����Դϴ�.
		ERR_PREV_INIT = 0x05, // ������ �ʱ�ȭ�� �����߽��ϴ�.
		ERR_NOT_INIT  = 0x06, // �ʱ�ȭ�� ������� �ʾҽ��ϴ�.
	};


public:
	/**
	 * @brief ���� ����� �ʱ�ȭ�մϴ�.
	 * 
	 * @return �ʱ�ȭ�� �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Init();


	/**
	 * @brief ���� ����� �ʱ�ȭ�� �����մϴ�.
	 * 
	 * @return �ʱ�ȭ ������ �����ϸ� Errors �������� OK ����, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Uninit();


	/**
	 * @brief ��ƼƼ�� �����մϴ�.
	 *
	 * @param args ��ƼƼ�� �����ڿ� ������ ���ڵ��Դϴ�.
	 *
	 * @return ������ ��ƼƼ�� �����͸� ��ȯ�մϴ�. ��ƼƼ ������ �����ϸ� nullptr�� ��ȯ�մϴ�.
	 */
	template <typename TEntity, typename... Args>
	static TEntity* CreateEntity(Args&&... args)
	{
		if (!(0 <= cacheSize && cacheSize < MAX_ENTITY_COUNT))
		{
			return nullptr;
		}

		int32_t id = -1;
		for (uint32_t index = 0; index < cacheSize; ++index)
		{
			if (!cache[index] && !usage[index])
			{
				id = static_cast<int32_t>(index);
				break;
			}
		}

		if (id == -1)
		{
			id = cacheSize++;
		}

		usage[id] = true;
		cache[id] = std::make_unique<TEntity>(args...);

		return reinterpret_cast<TEntity*>(cache[id].get());
	}


	/**
	 * @brief ��ƼƼ �Ŵ����� �����ϴ� ��ƼƼ�� �����մϴ�.
	 *
	 * @param entity ������ ��ƼƼ�� �������Դϴ�.
	 */
	static void DestroyEntity(const IEntity* entity)
	{
		int32_t id = -1;
		for (uint32_t index = 0; index < cacheSize; ++index)
		{
			IEntity* cacheEntity = cache[index].get();
			if (entity == cacheEntity)
			{
				id = static_cast<int32_t>(index);
				break;
			}
		}

		if (id != -1 && cache[id])
		{
			if (cache[id]->IsInitialized())
			{
				cache[id]->Release();
			}

			usage[id] = false;
			cache[id].reset();
		}
	}


private:
	/**
	 * @brief ���� ����� �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 */
	static bool bIsInit;


	/**
	 * @brief ������ �� �ִ� �ִ� ��ƼƼ ���Դϴ�.
	 */
	static const uint32_t MAX_ENTITY_COUNT = 200;


	/**
	 * @brief ĳ�� ũ���Դϴ�.
	 */
	static uint32_t cacheSize;


	/**
	 * @brief ��ƼƼ�� ĳ���Դϴ�.
	 */
	static std::array<std::unique_ptr<IEntity>, MAX_ENTITY_COUNT> cache;


	/**
	 * @brief ��ƼƼ�� ��� �����Դϴ�.
	 */
	static std::array<bool, MAX_ENTITY_COUNT> usage;
};