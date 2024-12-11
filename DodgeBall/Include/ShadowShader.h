#pragma once

#include "Shader.h"

class StaticMesh; // ���� �޽� ���ҽ��� ����ϱ� ���� ���漱�� �Դϴ�.
class Light;      // ����Ʈ ������Ʈ�� ����ϱ� ���� ���漱�� �Դϴ�.


/**
 * @brief �ε��� ȿ���� �����ϴ� ���̴��Դϴ�.
 * 
 * @note �� ���̴��� ���� ���ο��� �����ϴ� ���̴��Դϴ�. �ܺο��� �ʱ�ȭ�ϸ� �ȵ˴ϴ�.
 */
class ShadowShader : public Shader
{
public:
	/**
	 * @brief �ε��� ȿ���� �����ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	ShadowShader() = default;


	/**
	 * @brief �ε��� ȿ���� �����ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~ShadowShader();


	/**
	 * @brief �ε��� ȿ���� �����ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowShader);


	/**
	 * @brief �ε��� ���̴��� ����Ʈ�� ���õ� ������ ���۸� �����մϴ�.
	 * 
	 * @param light ������ ����Ʈ�� �������Դϴ�.
	 */
	void SetLight(const Light* light);


	/**
	 * @brief ���� ���ۿ� �޽��� ���� ���� �������մϴ�.
	 *
	 * @param world �޽��� ���� ����Դϴ�.
	 * @param mesh ������ ȿ���� ������ �޽��Դϴ�.
	 */
	void DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh);
};