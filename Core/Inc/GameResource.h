#pragma once

#include "IResource.h"

namespace GameResource
{
	/** ��� ���� ���ҽ��� �ݵ�� �� �Լ��� ���� �����ؾ� ��. */
	template <typename TResource, typename... Args>
	TResource* Create(Args&&... args);

	void Destroy(const IResource* resource);
}