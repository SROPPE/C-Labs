#include <iostream>
#include <fstream>
using namespace std;
int len(char* str)
{
	int size = 0;
	for (int i = 0; i < 10000; i++)
	{
		size++;
		if (str[i] == '\0')
			break;
	}
	return size;
}
int strin(char* str1, char* str2)
{
	int size1 = len(str1);
	int size2 = len(str2);
	int start = 0;
	int j = 0;
	for (int i = 0, k = 0; i < size1; i++)
	{
		if (j > 0 && str1[i] != str2[k])
		{
			k = 0;
			j = 0;
		}
		if (str1[i] == str2[k])
		{
			j++;
			k++;
		}
		else
			j = 0;
		if (j == 1)
			start = i;
		if (j == size2 - 1)
		{
			break;
		}
	}
	if (j == size2 - 1)
		return start;
	return -1;
}
bool CheckForDouble(int* a, int num, int size)
{
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		if (a[i] == num)
		{
			k++;
		}
	}
	if (k>=2)
	{
		return true;
	}
	return false;
}
void Substr(char* str, int start, int length)
{
	char* p = new char[len(str) - length - 1];
	for (int i = 0, z = 0; i < len(str); i++)
	{
		if (i >= start + length || i < start)
		{
			p[z] = str[i];
			z++;
		}
	}
	for (int i = 0; i < len(str) - length; i++)
	{
		str[i] = p[i];
	}

}
int strInChecker(char* str1, char* str2, int length)
{
	int p = 0;
	while (strin(str1, str2) != -1)
	{
		Substr(str1, strin(str1, str2), length);
		p++;
	}
	return p;
}
int inArr(int *a,int num,int size)
{
	for (int i = 0;i < size; i++)
	{
		if (a[i] == num)
		{
			if (CheckForDouble(a,a[i],size))
			{
				a[i] = -1;
			}
			return i;
		}
	}
	return -1; 
}
void Sort(int* arr,int *size ,int n) 
{
	int k = 0;
	for (int i = 1; i < n; i++) 
	{
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
		{
			k++;
			int t = size[j - 1];
			int tmp = arr[j - 1];
			size[j - 1] = size[j];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
			size[j ] = t;
		}
	}
}
void main()
{
	setlocale(LC_ALL, "ru");
	char currentBuffer[100]; 
	fstream filein("Text.txt");
	int n = 0;
	while (!filein.eof())
	{
		filein.getline(currentBuffer, 100);
		n++;
	}
	int *entry = (int*)malloc(100 * sizeof(int));
	int *sizes = (int*)malloc(100 * sizeof(int));
	char** entrySizes = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		entrySizes[i] = (char*)malloc(40 * sizeof(char));
	}
	char** strs = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		strs[i] = (char*)malloc(40 * sizeof(char));
	}
	int k = 0;
	filein.seekg(0, ios_base::beg);
	while (!filein.eof())
	{
		filein.getline(currentBuffer, 100);
		for (int i = 0; i < len(currentBuffer); i++)
		{
			strs[k][i] = currentBuffer[i];
		}
		k++;
	}
	int currentPos = 0;
	int *changeSaver = new int[n];
	
	for (int i = 0; i < n; i++)
	{
		int z = 0;
		for (int j = 0; j < n;j++)
		{
			if ( j!=i)
			{
				char buf[40];
				for (int k = 0; k < strlen(strs[i]); k++)
				{
					buf[k] = strs[i][k];
				}
				buf[strlen(strs[i])] = '\0';
				int time = strInChecker(buf, strs[j], strlen(strs[j]));
				for (int k = 0; k < len(strs[i]); k++)
				{
					buf[k] = strs[i][k];
				}
					int mult = 0;
					while (time != 0)
					{
						entry[z] = strin(buf, strs[j]) + strlen(strs[j])*mult;
						sizes[z] = len(strs[j]);
						Substr(buf, strin(buf, strs[j]), strlen(strs[j]));
						z++;
						time--;
						mult++;
					}
			}
			else
			{
				entry[z] = -1;
				sizes[z] = -1;
				z++;
			}
		}
		Sort(entry,sizes, z);
		int last = 0, now=0;
		for (int k = 0,p=0;k<n*n; k++)
		{
			
			int j = inArr(entry, currentPos, z);
			if (j > -1)
			{
				changeSaver[p] = sizes[j] - 1;
				last = sizes[j] - 1;
				p++;
				currentPos += sizes[j] - 1;
				if (currentPos == len(strs[i]) - 1)
				{
					printf("%s\n", strs[i]);
					break;
				}
			}
			else if (currentPos >= 0 && j == -1 && p-1>-1)
			{
				
				if (now == last)
				{
					p--;
					currentPos -= changeSaver[p];
					now = last;
				}
					p--;
					currentPos -= changeSaver[p];
					now = last;
				
			}
			else break;
			
		}
		currentPos = 0;
		for (int i = 0; i < z; i++)
		{
			entry[i] = -1;
			sizes[i] = -1;
		}
	}

	free(entry);
	free(sizes);
	for (int i = 0; i < n; i++)  
	{
		free(strs[i]);
		free(entrySizes[i]);
	}  
	free(strs);
	free(entrySizes);
}