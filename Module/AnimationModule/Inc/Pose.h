#pragma once

#include <vector>

#include "Transform.h"


/**
 * @brief �ִϸ��̼�ȭ�� ĳ������ ��ݿ��� ��� ������ ��ȭ�� �����ϴ� Ŭ�����Դϴ�.
 */
class Pose
{
public:
	/**
	 * @brief ���� Ŭ������ ����Ʈ �������Դϴ�.
	 */
	Pose() = default;


	/**
	 * @brief ���� Ŭ������ �������Դϴ�.
	 * 
	 * @param numJoints ���� ��ȯ ��� ũ���Դϴ�.
	 */
	Pose(uint32_t numJoints)
	{
		Resize(numJoints);
	}


	/**
	 * @brief ���� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Pose(Pose&& instance) noexcept
		: joints_(instance.joints_)
		, parents_(instance.parents_) {}


	/**
	 * @brief ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ �ν��Ͻ��Դϴ�.
	 */
	Pose(const Pose& instance) noexcept
		: joints_(instance.joints_)
		, parents_(instance.parents_) {}


	/**
	 * @brief ���� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Pose() {}


	/**
	 * @brief ���� Ŭ������ ���� �������Դϴ�.
	 * 
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 * 
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Pose& operator=(Pose&& instance) noexcept
	{
		if (this == &instance) return *this;

		joints_ = instance.joints_;
		parents_ = instance.parents_;

		return *this;
	}


	/**
	 * @brief ���� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ���� ������ ������ �ν��Ͻ��Դϴ�.
	 *
	 * @return ���� ������ ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	Pose& operator=(const Pose& instance) noexcept
	{
		if (this == &instance) return *this;

		joints_ = instance.joints_;
		parents_ = instance.parents_;

		return *this;
	}


	/**
	 * @brief �� ��� ���� ��ġ�ϴ��� Ȯ���մϴ�.
	 *
	 * @param instance ��ġ�ϴ��� Ȯ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return �� ��� ��ġ�Ѵٸ� true, �׷��� ������ false�Դϴ�.
	 */
	bool operator==(Pose&& instance) noexcept;


	/**
	 * @brief �� ��� ���� ��ġ�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param instance ��ġ�ϴ��� Ȯ���� �ν��Ͻ��Դϴ�.
	 * 
	 * @return �� ��� ��ġ�Ѵٸ� true, �׷��� ������ false�Դϴ�.
	 */
	bool operator==(const Pose& instance);


	/**
	 * @brief �� ��� ���� ��ġ���� �ʴ��� Ȯ���մϴ�.
	 *
	 * @param instance ��ġ���� �ʴ��� Ȯ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return �� ��� ��ġ���� �ʴ´ٸ� true, �׷��� ������ false�Դϴ�.
	 */
	bool operator!=(Pose&& instance) noexcept;


	/**
	 * @brief �� ��� ���� ��ġ���� �ʴ��� Ȯ���մϴ�.
	 *
	 * @param instance ��ġ���� �ʴ��� Ȯ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return �� ��� ��ġ���� �ʴ´ٸ� true, �׷��� ������ false�Դϴ�.
	 */
	bool operator!=(const Pose& instance);


	/**
	 * @brief ���� ���� ����� ũ�⸦ �����մϴ�.
	 * 
	 * @param size ������ ũ���Դϴ�.
	 */
	void Resize(uint32_t size);


	/**
	 * @brief ���� ���� ���� ��ȯ ��� ũ�⸦ ����ϴ�.
	 * 
	 * @return ���� ���� ���� ��ȯ ��� ũ�⸦ ��ȯ�մϴ�.
	 */
	uint32_t Size() const { return static_cast<uint32_t>(joints_.size()); }


	/**
	 * @brief �ε����� �����ϴ� ���� ��ȯ ���� ����ϴ�.
	 * 
	 * @param index ���� ��ȯ ���� ���� �ε����Դϴ�.
	 * 
	 * @return �ε����� �����ϴ� ���� ��ȯ ���� ��ȯ�մϴ�.
	 */
	Transform GetLocalTransform(uint32_t index);


	/**
	 * @brief �ε����� �����ϴ� ���� ��ȯ ���� �����մϴ�.
	 *
	 * @param index ���� ��ȯ ���� ������ �ε����Դϴ�.
	 * @param transform ������ ��ȯ ���Դϴ�.
	 */
	void SetLocalTransform(uint32_t index, const Transform& transform);


	/**
	 * @brief �ε����� �����ϴ� �۷ι� ���� ��ȯ ���� ����ϴ�.
	 * 
	 * @param index ���� ��ȯ ���� ���� �ε����Դϴ�.
	 * 
	 * @return �ε����� �����ϴ� �۷ι� ���� ��ȯ ���� ��ȯ�մϴ�.
	 */
	Transform GetGlobalTransform(uint32_t index);


	/**
	 * @brief �ε����� �����ϴ� �۷ι� ���� ��ȯ ���� ����ϴ�.
	 *
	 * @param index ���� ��ȯ ���� ���� �ε����Դϴ�.
	 *
	 * @return �ε����� �����ϴ� �۷ι� ���� ��ȯ ���� ��ȯ�մϴ�.
	 */
	Transform operator[](uint32_t index);


	/**
	 * @brief ���� ���� ��ȯ�� ��� ������� ��ȯ�մϴ�.
	 * 
	 * @param outMatrixPalette ��� ����� ������ �����Դϴ�.
	 */
	void GetMatrixPalette(std::vector<Mat4x4>& outMatrixPalette);


	/**
	 * @brief �ε����� �����ϴ� �θ� ���� ���� ����ϴ�.
	 * 
	 * @param index �θ� ���� ���� ���� �ε��� ���Դϴ�.
	 * 
	 * @return �ε����� �����ϴ� �θ� ���� ���� ��ȯ�մϴ�.
	 */
	int32_t GetParent(uint32_t index) { return parents_[index]; }


	/**
	 * @brief �θ� ���� ���� �����մϴ�.
	 * 
	 * @param index �θ� ���� ���� ������ �ε����Դϴ�.
	 * @param parent ������ �θ� ���� ���Դϴ�.
	 */
	void SetParent(uint32_t index, int32_t parent) { parents_[index] = parent; }


private:
	/**
	 * @brief ���� ��ȯ ����Դϴ�.
	 */
	std::vector<Transform> joints_;


	/**
	 * @brief ������ �θ� �ε��� ����Դϴ�.
	 */
	std::vector<int32_t> parents_;
};