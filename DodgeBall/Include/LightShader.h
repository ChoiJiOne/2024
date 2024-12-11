#pragma once

#include "Shader.h"

class Light;      // ����Ʈ ������Ʈ�� ����ϱ� ���� ���漱�� �Դϴ�.
class Camera3D;   // ī�޶� ������Ʈ�� ����ϱ� ���� ���漱�� �Դϴ�.
class Material;   // ���͸��� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.
class StaticMesh; // ���� �޽� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.
class ShadowMap;  // �ε��� �� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�. 


/**
 * @brief ����Ʈ ȿ���� �����ϴ� ���̴��Դϴ�.
 * 
 * @note �� ���̴��� ���� ���ο��� �����ϴ� ���̴��Դϴ�. �ܺο��� �ʱ�ȭ�ϸ� �ȵ˴ϴ�.
 */
class LightShader : public Shader
{
public:
	/**
	 * @brief ����Ʈ ȿ���� �����ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	LightShader() = default;


	/**
	 * @brief ����Ʈ ȿ���� �����ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~LightShader();


	/**
	 * @brief ����Ʈ ȿ���� �����ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(LightShader);


	/**
	 * @brief ����Ʈ ���̴��� ���͸���� ���õ� ������ ���۸� �����մϴ�.
	 * 
	 * @param material ������ ���͸����� �������Դϴ�.
	 */
	void SetMaterial(const Material* material);


	/**
	 * @brief ����Ʈ ���̴��� ����Ʈ�� ���õ� ������ ���۸� �����մϴ�.
	 * 
	 * @param light ������ ����Ʈ�� �������Դϴ�.
	 */
	void SetLight(const Light* light);


	/**
	 * @brief ����Ʈ ���̴����� ī�޶�� ���õ� ������ ���۸� �����մϴ�.
	 * 
	 * @param camera ������ ī�޶��� �������Դϴ�.
	 */
	void SetCamera(const Camera3D* camera);


	/**
	 * @brief �޽ÿ� ������ ȿ���� �����մϴ�.
	 * 
	 * @param world �޽��� ���� ����Դϴ�.
	 * @param mesh ������ ȿ���� ������ �޽��Դϴ�.
	 * @param shadowMap �ε��� ���Դϴ�.
	 */
	void DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh, const ShadowMap* shadowMap);
};