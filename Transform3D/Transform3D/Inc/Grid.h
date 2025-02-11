#pragma once

#include "IEntity.h"

class GeometryRenderer3D;


/**
 * @brief 월드 상의 격자 엔티티입니다.
 */
class Grid : public IEntity
{
public:
	/**
	 * @brief 격자(Grid) 엔티티의 생성자입니다.
	 *
	 * @param renderer 구를 렌더링할 때 참조할 렌더러입니다.
	 */
	Grid(GeometryRenderer3D* renderer);


	/**
	 * @brief 격자(Grid) 엔티티의 가상 소멸자입니다.
	 */
	virtual ~Grid();


	/**
	 * @brief 격자(Grid) 엔티티의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Grid);


	/**
	 * @brief 격자(Grid) 엔티티를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 격자(Grid) 엔티티를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 격자(Grid) 엔티티 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 격자를 그릴 때 참조할 렌더러입니다.
	 */
	GeometryRenderer3D* renderer_ = nullptr;


	/**
	 * @brief 격자의 크기입니다.
	 */
	Vec3f size_ = Vec3f(1.0f, 1.0f, 1.0f);


	/**
	 * @brief 격자의 간격입니다.
	 */
	float stride_ = 1.0f;
};