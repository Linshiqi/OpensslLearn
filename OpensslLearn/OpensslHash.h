#pragma once
#include <openssl/lhash.h>
#include <string.h>
#include <iostream>

typedef struct Student_st
{
	char name[20];
	int age;
	char otherInfo[200];
} Student;

static int Student_cmp(const void* a, const void* b)
{
	char* namea = ((Student*)a)->name;
	char* nameb = ((Student*)b)->name;

	return strcmp(nameb, nameb);
}

static void PrintValue(Student* a)
{
	std::cout << "name: " << a->name << " age: " << a->age << " otherInfo: " << a->otherInfo << std::endl;
}

static void PrintValueArg(Student* a, void* b)
{
	int flag = 0;

	flag = *(int*)b;

	std::cout << "用户参数： " << flag << std::endl;
	std::cout << "name: " << a->name << " age: " << a->age << " otherInfo: " << a->otherInfo << std::endl;
}

void testOpensslHash()
{
	Student s1 = { "lin", 28, "man" },
		s2 = { "liu", 26, "woman" },
		s3 = { "hu", 30, "man" };
	
	auto pHash = lh_new(NULL, Student_cmp);		// 创建hash对象

	if (pHash == nullptr)
	{
		return;
	}

	auto data = &s1;
	lh_insert(pHash, data);						// 添加数据
	data = &s2;
	lh_insert(pHash, data);
	data = &s3;
	lh_insert(pHash, data);

	lh_doall(pHash, (OPENSSL_LH_DOALL_FUNC)PrintValue);		// 遍历hash表执行函数

	int flag = 11;
	lh_doall_arg(pHash, (OPENSSL_LH_DOALL_FUNCARG)PrintValueArg, (void*)(&flag));	// 带参数的遍历执行函数

	data = (Student*)lh_retrieve(pHash, "liu");	// 获取执行数据对象

	if (data != nullptr)
	{
		std::cout << "Found data : " << data->name << std::endl;
	}

	lh_free(pHash);								// 释放清理
}
