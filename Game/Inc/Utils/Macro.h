#pragma once

/** �� ��ũ�ΰ� ���ǵǾ� ���� ���� Ÿ���� �ݵ�� ��������� ���� �����ڿ� ���� �����ڸ� ���� �����ڸ� �����ؾ� �մϴ�. */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)    \
TypeName(TypeName&&) = delete;                \
TypeName(const TypeName&) = delete;           \
TypeName& operator=(TypeName&&) = delete;     \
TypeName& operator=(const TypeName) = delete;
#endif