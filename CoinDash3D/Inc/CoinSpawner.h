#pragma once

#include <list>

#include "IEntity.h"

class Character;
class Coin;


/**
 * @brief ������ �����ϴ� ��ƼƼ�Դϴ�.
 */
class CoinSpawner : public IEntity
{
public:
	/**
	 * @brief ������ �����ϴ� ��ƼƼ�� �������Դϴ�.
	 *
	 * @param coins ���� ����� �������Դϴ�.
	 * @param character ������ ������ ĳ���� ��ƼƼ�Դϴ�.
	 */
	CoinSpawner(std::list<Coin*>& coins, Character* character);


	/**
	 * @brief ������ �����ϴ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~CoinSpawner();


	/**
	 * @brief ������ �����ϴ� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(CoinSpawner);


	/**
	 * @brief ������ �����ϴ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ������ �����ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


private:
	/**
	 * @brief ������ �����մϴ�.
	 */
	void GenerateCoins();


private:
	/**
	 * @brief ���� ����� �������Դϴ�.
	 */
	std::list<Coin*>& coins_;


	/**
	 * @brief ������ ������ ĳ���� ��ƼƼ�Դϴ�.
	 */
	Character* character_ = nullptr;


	/**
	 * @brief �ִ� ���� ���� ���Դϴ�.
	 */
	uint32_t maxCoin_ = 10;
};