#pragma once

#include "CrossFadeController.h"
#include "Collision.h"
#include "IEntity.h"
#include "ITexture2D.h"
#include "Skeleton.h"
#include "SkinnedMesh.h"

class Wall;


/**
 * @brief ĳ���� ��ƼƼ�Դϴ�.
 */
class Character : public IEntity
{
public:
	/**
	 * @brief ĳ������ �����Դϴ�.
	 */
	enum class EStatus
	{
		IDLE = 0x00, // �����
		RUN  = 0x01, // �޸��� ��
		DONE = 0x02, // ���� ����
	};


public:
	/**
	 * @brief ĳ���� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param ĳ������ �������� ������ �� ��ƼƼ�Դϴ�.
	 */
	Character(Wall* wall);


	/**
	 * @brief ĳ���� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Character();


	/**
	 * @brief ĳ���� ��ƼƼ�� ���� ������ �� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Character);


	/**
	 * @brief ĳ���� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief ĳ���� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release();


	/**
	 * @brief ĳ������ �޽� ���ҽ� ����� ����ϴ�.
	 *
	 * @return ĳ������ �޽� ���ҽ� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	std::vector<SkinnedMesh*>& GetMeshes() { return meshes_; }


	/**
	 * @brief ĳ������ ���͸���(����)�� ����ϴ�.
	 *
	 * @return ĳ������ ���͸���(����) �����ڸ� ��ȯ�մϴ�.
	 */
	ITexture2D* GetMaterial() { return material_; }


	/**
	 * @brief ĳ������ ��� ������ ����ϴ�.
	 * 
	 * @return ĳ������ ��� ���� �����ڸ� ��ȯ�մϴ�.
	 */
	Sphere& GetSphere() { return sphere_; }


	/**
	 * @brief ĳ������ Ʈ�������� ����ϴ�.
	 * 
	 * @return ĳ������ Ʈ������ �����ڸ� ��ȯ�մϴ�.
	 */
	Transform& GetTransform() { return transform_; }


	/**
	 * @brief ĳ������ ũ�ν� ���̵� ��Ʈ�ѷ��� ����ϴ�.
	 *
	 * @return ĳ������ ũ�ν� ���̵� ��Ʈ�ѷ� �����ڸ� ��ȯ�մϴ�.
	 */
	CrossFadeController& GetCrossFadeController() { return crossFadeController_; }


private:
	/**
	 * @brief ĳ������ �̵� ������ ����ϴ�.
	 * 
	 * @return ĳ������ �̵� ������ ��ȯ�մϴ�.
	 */
	Vec3f GetMoveDirection();


private:
	/**
	 * @brief ī�޶� ��ƼƼ�Դϴ�.
	 */
	Camera* camera_ = nullptr;


	/**
	 * @brief ��Ű�� �޽� ���ҽ��Դϴ�.
	 */
	std::vector<SkinnedMesh*> meshes_;


	/**
	 * @brief ĳ������ ���͸����Դϴ�.
	 */
	ITexture2D* material_ = nullptr;


	/**
	 * @brief ĳ������ ��� �����Դϴ�.
	 */
	Sphere sphere_;


	/**
	 * @brief ĳ������ Ʈ�������Դϴ�.
	 */
	Transform transform_;


	/**
	 * @brief ��� �ִϸ��̼� Ŭ�� �ε����Դϴ�.
	 */
	uint32_t idleClip_ = 0;


	/**
	 * @brief �޸��� �ִϸ��̼� Ŭ�� �ε����Դϴ�.
	 */
	uint32_t runClip_ = 0;


	/**
	 * @brief �ִϸ��̼� Ŭ���Դϴ�.
	 */
	std::vector<Clip> clips_;


	/**
	 * @brief ĳ���� �ִϸ��̼��� �����Դϴ�.
	 */
	Skeleton skeleton_;


	/**
	 * @brief Ŭ���� �ε巯�� ��ȯ�� ���� ũ�ν� ���̵� ��Ʈ�ѷ��Դϴ�.
	 */
	CrossFadeController crossFadeController_;


	/**
	 * @brief ĳ������ ���� �����Դϴ�.
	 */
	EStatus currentStatus_ = EStatus::IDLE;


	/**
	 * @brief ĳ������ �̵� �ӵ��Դϴ�.
	 */
	float moveSpeed_ = 0.0f;


	/**
	 * @brief ĳ������ �������� ������ �� ��ƼƼ�Դϴ�.
	 */
	Wall* wall_ = nullptr;
};