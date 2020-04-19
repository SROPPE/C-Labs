#include <iostream>
#include <malloc.h>

using namespace std;
bool Check(char* p)
{
	for (int i = 0; i < strlen(p); i++)
	{
		if (p[i] - 48 >= 0 && p[i] - 48 <= 9) {}
		else return true;
	}
	return false;
}
void Swap(int* a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}
void PrintPermin(int* a, int size)
{
	for (int i = 0; i < size; i++)
		 printf("%d ",a[i]);
	printf("\n");
}
bool NextPermin(int* a, int size)
{
	int pos1 = size - 2;
	while (pos1 != -1 && a[pos1] >= a[pos1 + 1]) pos1--;
	if (pos1 == -1)
		return false;
	int pos2 = size - 1;
	while (a[pos1] >= a[pos2]) pos2--;
	Swap(a, pos1, pos2);
	int l = pos1 + 1, r = size - 1;
	while (l < r)
		Swap(a, l++, r--);
	return true;
}
int main()
{
	setlocale(LC_ALL, "ru");
	int size, * a;
	char r[20];
	printf("¬ведите n: ");
	do
	{
		gets_s(r);
	} while (Check(r));
	size = atoi(r);
	a = (int*)malloc(size * sizeof(int));;
	for (int i = 0; i < size; i++)
		a[i] = i + 1;
	PrintPermin(a, size);
	while (NextPermin(a, size))
		PrintPermin(a, size);
	free(a);
	return 0;
}