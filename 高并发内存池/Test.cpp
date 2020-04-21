#include"ThreadCache.h"
#include<vector>

void UnitThreadCache()
{

	ThreadCache tv;
	vector<void*> v;

	for (int i = 0; i < 21; i++)
	{
		v.push_back(tv.Alloc(7));
	}

	for (size_t i = 0; i < v.size(); ++i)
	{
		printf("[%d]->%p\n", i, v[i]);
	}

	for (auto ptr : v)
	{
		tv.Dellocte(ptr, 7);
	}
}


int main()
{
	UnitThreadCache();
	return 0;
}