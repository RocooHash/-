/**
 * name:10-排序4 统计工龄
*/

#include <stdio.h>

#define TOTAL_PEOPLE 55

int main()
{
	int N, workAge;
	int workYear[TOTAL_PEOPLE] = { 0 };
	scanf("%d", &N);
	for (int i = 0; i < N;i++)
	{
		scanf("%d", &workAge);
		workYear[workAge]++;
	}
	for (int i = 0; i < TOTAL_PEOPLE;i++)
	{
		if (workYear[i])
		{
			printf("%d:%d\n", i, workYear[i]);
		}
	}
	return 0;
}
