#pragma once

#include <vector>

#include "Shader.h"

#include "DirectionalLight.h"

class Camera3D;   // ī�޶� ������Ʈ�� ����ϱ� ���� ���漱�� �Դϴ�.
class Material;   // ���͸��� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.
class StaticMesh; // ���� �޽� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.


/**
 * @brief ������(Directional Light) ȿ���� �����ϴ� ���̴��Դϴ�.
 */
class DirectionalLightShader : public Shader
{
public:
	/**
	 * @briref ������(Directional Light)�� �ִ� ����Ʈ ���Դϴ�.
	 */
	static const uint32_t MAX_LIGHTS = 5;


public:
	/**
	 * @brief ������(Directional Light) ȿ���� �����ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	DirectionalLightShader() = default;


	/**
	 * @brief ������(Directional Light) ȿ���� �����ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~DirectionalLightShader();


	/**
	 * @brief ������(Directional Light) ȿ���� �����ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(DirectionalLightShader);


	/**
	 * @brief ������(Directional Light) ���̴����� ī�޶�� ���õ� ������ ���۸� �����մϴ�.
	 *
	 * @param camera ������ ī�޶��� �������Դϴ�.
	 */
	void SetCamera(const Camera3D* camera);


	/**
	 * @brief ������(Directional Light) ���̴��� ���͸���� ���õ� ������ ���۸� �����մϴ�.
	 *
	 * @param material ������ ���͸����� �������Դϴ�.
	 */
	void SetMaterial(const Material* material);


	/**
	 * @brief ������(Directional Light) ���̴��� ������ ���۸� �����մϴ�.
	 * 
	 * @param directionalLight ������ ������(Directional Light)�Դϴ�.
	 */
	void SetDirectionalLight(const DirectionalLight& directionalLight);


	/**
	 * @brief �޽ÿ� ������ ȿ���� �����մϴ�.
	 *
	 * @param world �޽��� ���� ����Դϴ�.
	 * @param mesh ������ ȿ���� ������ �޽��Դϴ�.
	 * @param shadowMap �ε��� ���Դϴ�.
	 */
	void DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh);
};