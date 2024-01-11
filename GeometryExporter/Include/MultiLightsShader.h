#pragma once

#include <vector>

#include "Shader.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Camera3D;   // ī�޶� ������Ʈ�� ����ϱ� ���� ���漱�� �Դϴ�.
class Material;   // ���͸��� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.
class StaticMesh; // ���� �޽� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.


/**
 * @brief ���� ������ ȿ���� �����ϴ� ���̴��Դϴ�.
 */
class MultiLightsShader : public Shader
{
public:
	/**
	 * @briref ���� �������� �ִ� ����Ʈ ���Դϴ�.
	 */
	static const uint32_t MAX_LIGHTS = 5;


public:
	/**
	 * @brief ���� ������ ȿ���� �����ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	MultiLightsShader() = default;


	/**
	 * @brief ���� ������ ȿ���� �����ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~MultiLightsShader();


	/**
	 * @brief ���� ������ ȿ���� �����ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MultiLightsShader);


	/**
	 * @brief ���� ����Ʈ ���̴����� ī�޶�� ���õ� ������ ���۸� �����մϴ�.
	 *
	 * @param camera ������ ī�޶��� �������Դϴ�.
	 */
	void SetCamera(const Camera3D* camera);


	/**
	 * @brief ���� ����Ʈ ���̴��� ���͸���� ���õ� ������ ���۸� �����մϴ�.
	 *
	 * @param material ������ ���͸����� �������Դϴ�.
	 */
	void SetMaterial(const Material* material);


	/**
	 * @brief ���� ����Ʈ ���̴��� ������(Directional Light) ���� ������ ���۸� �����մϴ�.
	 * 
	 * @param directionalLights ������ ������(Directional Light)���Դϴ�.
	 */
	void SetDirectionalLights(const std::vector<DirectionalLight>& directionalLights);


	/**
	 * @brief ���� ����Ʈ ���̴��� ����(Point Light) ���� ������ ���۸� �����մϴ�.
	 * 
	 * @param pointLights ������ ����(Point Light)���Դϴ�.
	 */
	void SetPointLights(const std::vector<PointLight>& pointLights);


	/**
	 * @brief ���� ����Ʈ ���̴��� ����Ʈ ����Ʈ(Spot Light) ���� ������ ���۸� �����մϴ�.
	 * 
	 * @param spotLights ������ ����Ʈ ����Ʈ(Spot Light)���Դϴ�.
	 */
	void SetSpotLights(const std::vector<SpotLight> spotLights);


	 /**
	  * @brief �޽ÿ� ������ ȿ���� �����մϴ�.
	  *
	  * @param world �޽��� ���� ����Դϴ�.
	  * @param mesh ������ ȿ���� ������ �޽��Դϴ�.
	  * @param shadowMap �ε��� ���Դϴ�.
	  */
	void DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh);
};