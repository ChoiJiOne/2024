#pragma once

#include "CrossFadeController.h"
#include "IEntity.h"
#include "ITexture2D.h"
#include "Skeleton.h"
#include "SkinnedMesh.h"


/**
 * @brief ĳ���� ��ƼƼ�Դϴ�.
 */
class Character : public IEntity
{
public:
	/**
	 * @brief ĳ���� ��ƼƼ�� �������Դϴ�.
	 */
	Character();


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
	 * @brief ĳ������ ũ�ν� ���̵� ��Ʈ�ѷ��� ����ϴ�.
	 * 
	 * @return ĳ������ ũ�ν� ���̵� ��Ʈ�ѷ� �����ڸ� ��ȯ�մϴ�.
	 */
	CrossFadeController& GetCrossFadeController() { return crossFadeController_; }


private:
	/**
	 * @brief ��Ű�� �޽� ���ҽ��Դϴ�.
	 */
	std::vector<SkinnedMesh*> meshes_;


	/**
	 * @brief ĳ������ ���͸����Դϴ�.
	 */
	ITexture2D* material_ = nullptr;


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
};