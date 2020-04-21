#pragma once
#include"Common.h"

class ThreadCache
{
public:
	//�����ڴ�
	void* Alloc(size_t size);

	//�ͷ��ڴ�
	void Dellocte(void* ptr, size_t size);

	//�����Ļ���ȥ�ÿռ�
	void* FetchFromCentralCache(size_t index);

	//�������������ĳ�����󳬹�һ��������ô���仹�����Ļ���CentralCache
	void ListTooLong(FreeList& freelist, size_t num, size_t size);

private:
	FreeList _freelists[NFREELIST];//��һ����������
};