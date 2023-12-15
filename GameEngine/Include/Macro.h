#pragma once

/**
 * @brief 타입(클래스 혹은 구조체)의 복사 생성자 및 대입 연산자를 사용하지 못하도록 삭제합니다.
 * 
 * @note 이 매크로가 정의되어 있지 않은 타입은 반드시 명시적으로 복사 생성자와 대입 연산자를 복사 생성자를 정의해야 합니다.
 * 
 * @param TypeName 복사 생성자 및 대입 연산자를 삭제할 타입의 이름입니다.
 */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)\
TypeName(TypeName&&) = delete;\
TypeName(const TypeName&) = delete;\
TypeName& operator=(TypeName&&) = delete;\
TypeName& operator=(const TypeName) = delete;
#endif