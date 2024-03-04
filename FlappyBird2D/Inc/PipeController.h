#pragma once

#include <vector>

#include "IEntity.h"
#include "IResource.h"

class Pipe;


/**
 * @brief �������� �����ϴ� ��Ʈ�ѷ� ��ƼƼ�Դϴ�.
 */
class PipeController : public IEntity
{
public:
	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ��� �����Դϴ�.
	 */
	enum class EStatus : int32_t
	{
		Wait   = 0x00,
		Active = 0x01,
	};


public:
	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ� ��ƼƼ�� �������Դϴ�.
	 *
	 */
	explicit PipeController(const std::vector<Pipe*>& pipes, float gap);


	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ� ��ƼƼ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PipeController();


	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ� ��ƼƼ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PipeController);


	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ��� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ��� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @note �� ��ƼƼ�� �ƹ� �׸��⵵ �������� �ʽ��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �������� �����ϴ� ��Ʈ�ѷ� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ ��Ʈ�ѷ��� ���¸� �����մϴ�.
	 * 
	 * @param status ������ ������ ��Ʈ�ѷ��� �����Դϴ�.
	 */
	void SetStatus(const EStatus& status) { status_ = status; }


	/**
	 * @brief ������ ��Ʈ�ѷ��� �����ϴ� ������ ����� ����ϴ�.
	 * 
	 * @return ������ ��Ʈ�ѷ��� �����ϴ� �������� ����� ��ȯ�մϴ�.
	 */
	const std::vector<Pipe*>& GetPipes() const { return pipes_; }


private:
	/**
	 * @brief ������ ��Ʈ�ѷ��� �����Դϴ�.
	 */
	EStatus status_ = EStatus::Wait;


	/**
	 * @brief ������ ��Ʈ�ѷ��� �����ϴ� ������ ����Դϴ�.
	 */
	std::vector<Pipe*> pipes_;


	/**
	 * @brief ������ ���� �����Դϴ�.
	 */
	float gap_ = 0.0f;
};