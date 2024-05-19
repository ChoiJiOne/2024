#pragma once

/**
 * @brief �ִϸ��̼� � ���� �����Դϴ�.
 * 
 * @see https://gabormakesgames.com/blog_animation_pose.html
 */
enum class EInterpolation
{
	CONSTANT = 0x00, // ��� ��Դϴ�.
	LINEAR   = 0x01, // ���� ��Դϴ�.
	CUBIC    = 0x02, // ť�� ��Դϴ�.
};