#include <iostream>
#include <fstream>
using namespace std;
int len(char*str)
{
	int size=0;
	for (int i = 0; i < 10000; i++)
	{
		size++;
		if (str[i] == '\0')
			break;		
	}
	return size;
}
void main()
{
	char buffer[1000];
	fstream filein("Text.txt");
	while (!filein.eof())
	{
		filein.getline(buffer, 100);
		int size = len(buffer);
		for (int i = 0; i < size; i++)
		{
			if(buffer[i] < 48 || buffer[i] >= 58)
			printf("%c",buffer[i]);
			else if (buffer[i] >= 48 && buffer[i] < 58)
			{
				printf ("(");
				for (int  p = 0; p < buffer[i]-48; p++)
				{
					printf("+");
				}
				printf(")");
			}
		}
		printf("\n");
	}
	filein.close();
}