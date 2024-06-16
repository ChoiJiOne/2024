#pragma once

#include <list>

#include "Entity2D.h"

class Character;
class Coin;
class GeometryRenderer2D;


/**
 * @brief ���� ���� ��ġ�� ǥ���ϴ� �̴ϸ� ��ƼƼ�Դϴ�.
 */
class MiniMap : public Entity2D
{
public:
	/**
	 * @brief �̴ϸ��� �������Դϴ�.
	 * 
	 * @param coins �̴ϸ��� ���� ��� �������Դϴ�.
	 * @param character �̴ϸ��� ĳ�����Դϴ�.
	 * @param renderer �̴ϸ� ������ �� ������ 2D �������Դϴ�.
	 */
	MiniMap(std::list<Coin*>& coins, Character* character, GeometryRenderer2D* renderer);


	/**
	 * @brief �̴ϸ��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~MiniMap();


	/**
	 * @brief �̴ϸ��� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MiniMap);


	/**
	 * @brief �̴ϸ� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �̴ϸ��� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ������ �����ϴ� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 3D��ġ�� 2D �̴ϸ� ���� ��ġ�� ��ȯ�մϴ�.
	 * 
	 * @param position3D ��ȯ�� 3D ��ġ�Դϴ�.
	 * 
	 * @return ��ȯ�� 2D �̴ϸ� ���� ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2f Convert3DTo2D(const Vec3f& position3D);


private:
	/**
	 * @brief �̴ϸ��� ���� ��� �������Դϴ�.
	 */
	std::list<Coin*>& coins_;


	/**
	 * @brief �̴ϸ��� ĳ�����Դϴ�.
	 */
	Character* character_ = nullptr;


	/**
	 * @brief �̴ϸ� ������ �� ������ 2D �������Դϴ�.
	 */
	GeometryRenderer2D* renderer_ = nullptr;


	/**
	 * @brief �̴ϸ��� ��ġ�Դϴ�.
	 */
	Vec2f center_;


	/**
	 * @brief �̴ϸ��� ũ���Դϴ�.
	 * 
	 * @note �̴ϸ��� ���簢���Դϴ�.
	 */
	float size_;


	/**
	 * @brief �̴ϸ��� ��׶��� �����Դϴ�.
	 */
	Vec4f background_;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vec4f coinColor_;


	/**
	 * @brief �÷��̾��� �����Դϴ�.
	 */
	Vec4f characterColor_;


	/**
	 * @brief ������ �ִ� ��ǥ ���Դϴ�.
	 */
	float maxPosition_ = 0.0f;
};
