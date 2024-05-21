#pragma once

#include <vector>

#include "Transform.h"


/**
 * @brief 애니메이션된 계층 구조의 각 본 변환를 관리합니다.
 */
class Pose
{
public:
	/**
	 * @brief 포즈의 기본 생성자입니다.
	 */
	explicit Pose() {}


	/**
	 * @brief 포즈의 생성자입니다.
	 *
	 * @param size 변환 목록 및 인덱스의 크기입니다.
	 */
	explicit Pose(uint32_t size);


	/**
	 * @brief 포즈의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Pose(Pose&& instance) noexcept;


	/**
	 * @brief 포즈의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Pose(const Pose& instance) noexcept;


	/**
	 * @brief 포즈의 가상 소멸자입니다.
	 */
	virtual ~Pose() {}


	/**
	 * @brief 포즈의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Pose& operator=(Pose&& instance) noexcept;


	/**
	 * @brief 포즈의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입 연산을 수행한 객체의 참조자를 반환합니다.
	 */
	Pose& operator=(const Pose& instance) noexcept;


	/**
	 * @brief 두 포즈가 일치하는지 확인합니다.
	 *
	 * @param instance 일치하는지 확인할 인스턴스입니다.
	 *
	 * @return 두 포즈가 일치한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Pose&& instance) noexcept;


	/**
	 * @brief 두 포즈가 일치하는지 확인합니다.
	 *
	 * @param instance 일치하는지 확인할 인스턴스입니다.
	 *
	 * @return 두 포즈가 일치한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Pose& instance) noexcept;


	/**
	 * @brief 두 포즈가 일치하지 않는지 확인합니다.
	 *
	 * @param instance 일치하지 않는지 확인할 인스턴스입니다.
	 *
	 * @return 두 포즈가 일치하지 않는다면 true, 그렇다면 false를 반환합니다.
	 */
	bool operator!=(Pose&& instance) noexcept;


	/**
	 * @brief 두 포즈가 일치하지 않는지 확인합니다.
	 *
	 * @param instance 일치하지 않는지 확인할 인스턴스입니다.
	 *
	 * @return 두 포즈가 일치하지 않는다면 true, 그렇다면 false를 반환합니다.
	 */
	bool operator!=(const Pose& instance) noexcept;


	/**
	 * @brief 인덱스에 대응하는 변환값을 얻습니다.
	 *
	 * @param index 변환값의 인덱스입니다.
	 *
	 * @return 인덱스에 대응하는 변환값입니다.
	 */
	Transform operator[](uint32_t index);


	/**
	 * @brief 포즈 내의 버퍼 크기를 변경합니다.
	 *
	 * @param size 변경할 버퍼의 크기입니다.
	 */
	void Resize(uint32_t size);


	/**
	 * @brief 변환 목록의 크기를 얻습니다.
	 *
	 * @return 변환 목록의 크기를 반환합니다.
	 */
	uint32_t GetJointSize() { return static_cast<uint32_t>(joints_.size()); }


	/**
	 * @brief 인덱스에 대응하는 로컬 변환 값을 얻습니다.
	 *
	 * @param index 로컬 변환 값을 얻을 인덱스입니다.
	 *
	 * @return 인덱스에 대응하는 로컬 변환 값을 반환합니다.
	 */
	Transform GetLocalTransform(uint32_t index);


	/**
	 * @brief 인덱스에 대응하는 로컬 변환 값을 설정합니다.
	 *
	 * @param index 설정할 인덱스입니다.
	 * @param transform 설정할 변환 값입니다.
	 */
	void SetLocalTransform(uint32_t index, const Transform& transform);


	/**
	 * @brief 인덱스에 대응하는 글로벌 변환 값을 얻습니다.
	 *
	 * @param index 글로벌 변환 값을 얻을 인덱스입니다.
	 *
	 * @return 인덱스에 대응하는 글로벌 변환 값을 반환합니다.
	 */
	Transform GetGlobalTransform(uint32_t index);


	/**
	 * @brief 변환값에 대응하는 행렬 목록입니다.
	 *
	 * @param outMatrices 변환값에 대응하는 행렬을 저장할 벡터입니다.
	 */
	void GetMatrixPalette(std::vector<Mat4x4>& outMatrices);


	/**
	 * @brief 인덱스에 대응하는 부모 인덱스 값을 얻습니다.
	 *
	 * @param index 부모 인덱스 값의 인덱스 입니다.
	 *
	 * @return 부모 인덱스 값을 반환합니다.
	 */
	int32_t GetParent(uint32_t index);


	/**
	 * @brief 인덱스에 대응하는 부모 인덱스 값을 설정합니다.
	 *
	 * @param index 설정할 인덱스입니다.
	 * @param parent 설정할 부모 인덱스 값입니다.
	 */
	void SetParent(uint32_t index, int32_t parent);


private:
	/**
	 * @brief Pose의 변환 목록입니다.
	 */
	std::vector<Transform> joints_;


	/**
	 * @brief Pose의 부모를 나타내는 정수(인덱스)입니다.
	 */
	std::vector<int32_t> parents_;
};