#pragma once
#include <openssl/safestack.h>
#include <stdlib.h> 
#include <string.h>
#include <iostream>

typedef struct Student_st
{
	char* name;
	int age;
	char* otherInfo;
}Student;

DEFINE_STACK_OF(Student);

void Student_Free(Student* a)
{
	delete a;
	a = nullptr;
}

int Student_cmp(const Student* const *a, const Student* const *b)
{
	int ret;
	ret = strcmp((*a)->name, (*b)->name);
	return ret;
}

void testOpensslStack()
{
	STACK_OF(Student)* students = sk_Student_new(Student_cmp);
	Student* pS1 = new Student
	{
		(char*)"lin",
		12,
		(char*)"man"
	};
	sk_Student_push(students, pS1);

	Student* pS2 = new Student
	{
		(char*)"liu",
		12,
		(char*)"woman"
	};

	sk_Student_push(students, pS2);

	for (int i = 0; i < sk_Student_num(students); i++)
	{
		auto pStu = sk_Student_value(students, i);
		std::cout << pStu->name << " " << pStu->age << " " << pStu->otherInfo << std::endl;
	}

	Student* pPopST = static_cast<Student*>(sk_Student_pop(students));

	std::cout << pPopST->name << " " << pPopST->age << " " << pPopST->otherInfo;

	delete pPopST;
	pPopST = nullptr;

	sk_Student_pop_free(students, Student_Free);
}
