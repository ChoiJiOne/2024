#pragma once

#include <imgui.h>

#include "IEntity.h"

class ColorFrameBuffer;


/**
 * @brief UI ���� �� ȿ���� ��Ÿ���� ��ƼƼ�Դϴ�.
 */
class FireEffect : public IEntity
{
public:
	/**
	 * @brief �� ȿ���� ��Ÿ���� ��ƼƼ�� �������Դϴ�.
	 * 
	 * @param colorFrameBuffer �� ȿ���� �������� �ؽ�ó�Դϴ�.
	 */
	FireEffect(ColorFrameBuffer* colorFrameBuffer);


	/**
	 * @brief �� ȿ���� ��Ÿ���� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~FireEffect();


	/**
	 * @brief �� ȿ���� ��Ÿ���� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(FireEffect);


	/**
	 * @brief �� ȿ�� ��ƼƼ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds);


	/**
	 * @brief �� ȿ�� ��ƼƼ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �� ȿ�� ��ƼƼ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief �� ȿ���� �������� �ؽ�ó�Դϴ�.
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
};