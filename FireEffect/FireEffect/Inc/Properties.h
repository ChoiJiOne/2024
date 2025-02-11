#pragma once

#include <imgui.h>

#include "Vec2.h"

#include "IEntity.h"

class Shader;
class ColorFrameBuffer;


/**
 * @brief �� ȿ���� �Ӽ��Դϴ�.
 */
class Properties : public IEntity
{
public:
	/**
	 * @brief �� ȿ���� �Ӽ��� ��Ÿ���� ��ƼƼ�� �������Դϴ�.
	 *
	 * @param colorFrameBuffer �� ȿ���� �������� �ؽ�ó�Դϴ�.
	 */
	Properties(ColorFrameBuffer* colorFrameBuffer);


	/**
	 * @brief �� ȿ���� �Ӽ��� ��Ÿ���� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Properties();


	/**
	 * @brief �� ȿ���� �Ӽ��� ��Ÿ���� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Properties);


	/**
	 * @brief �� ȿ���� �Ӽ��� ��Ÿ���� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief �� ȿ���� �Ӽ��� ��Ÿ���� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �� ȿ���� �Ӽ��� ��Ÿ���� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief �� ȿ���� �����ϱ� ���� ��ǻƮ ���̴��Դϴ�.
	 */
	Shader* fireEffect_ = nullptr;


	/**
	 * @brief �� ȿ���� ������ �÷� ������ �����Դϴ�.
	 */
	ColorFrameBuffer* colorFrameBuffer_ = nullptr;


	/**
	 * @brief ImGui ������ �Ӽ��Դϴ�.
	 */
	ImGuiWindowFlags_ windowFlags_;


	/**
	 * @brief ImGui ���� ��ġ�Դϴ�.
	 */
	ImVec2 location_;


	/**
	 * @brief ImGui ���� ũ���Դϴ�.
	 */
	ImVec2 size_;


	/**
	 * @brief ���� ������ �����Դϴ�.
	 */
	Vec2f fireMovement_ = Vec2f(-0.01f, -0.5f);


	/**
	 * @brief �ؽ�ó �ְ� �����Դϴ�.
	 */
	Vec2f distortionMovement_ = Vec2f(-0.01f, -0.3f);


	/**
	 * @brief �븻 ���� ũ���Դϴ�.
	 */
	float normalStrength_ = 40.0f;


	/**
	 * @brief ���� �ð����Դϴ�.
	 */
	float time_ = 0.0f;
};