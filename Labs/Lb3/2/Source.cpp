#include <iostream>
using namespace std;

void main()
{

	setlocale(LC_ALL, "ru");
	int n, m;
	cout << "Введите n: ";
	cin >> n;
	cout << "Введите m: ";
	cin >> m;
	int** arrd2 = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		arrd2[i] = (int*)malloc(m * sizeof(int));
	}
	int sized1 = n * m;
	int* arrd1 = (int*)malloc(sized1 * sizeof(int));
	for (int row = 0, k = 0; row < n; row++)
	{
		for (int column = 0; column < m; column++)
		{
			cin >> arrd2[row][column];
			arrd1[k] = arrd2[row][column];
			k++;
		}
		printf("\n");
	}
	for (int row = 0,k = 0; row < n; row++)
	{
		for (int column = 0; column < m; column++)
		{		
		printf("%d ", arrd2[row][column]);
		}
		printf("\n");
	}
	bool horizontal = false;
	bool vertic= false,verticPas = true;
	bool rightLeft = false, rightLeftPas = true;
	bool leftRight = false, leftRightPas = true;
	for (int row = 0; row < n; row++)
	{
		for (int  column = 0, i = 0; column < m; column++)
		{
			if (arrd2[row][column] == 1)
				i++;
			else
				i = 0;
			if (i == 5) 
			{
				horizontal = true;
				break; 
			}
		}
	}
	for (int column = 0; column < m; column++)
	{
		for (int row = 0, i = 0; row < n; row++)
		{
			if (arrd2[row][column] == 1)
				i++;
			else
				i = 0;
			if (i == 5)
			{
				vertic = true;
				break;
			}
		}
	}
	int row = m ;
	for (int i = 0; i <sized1 ; i++)
	{ 
		if (i == m)
			row += m;
		if (arrd1[i] == 1)
		{
			for (int j = i,k = 0; j < sized1; j+=m+1,row+=m)
			{
				if (arrd1[j] == 0)
					break;	
				else
					k++;
				if (k == 5)
				{
					leftRight = true;
					break;
				}
				if (row  <= j + m + 1 && j + m + 1 < row  + m)
				{

				}
				else
					break;
				
			}
	    }
		if (leftRight)
			break;
		
	}
	row = m;
	for (int i = 0; i < sized1; i++)
	{
		if (i == m)
			row += m;
		if (arrd1[i] == 1)		
		{

			for (int j = i, k = 0; j < sized1; j += m - 1, row += m)
			{
				if (arrd1[j] == 0)
					break;
				else
					k++;
				if (k == 5)
				{
					rightLeft = true;
					break;
				}
				if (row - m <= j + (m - 1) && j + (m - 1) < row)
					break;
			}
		}
		if (rightLeft)
			break;
	}
	
	if (vertic || rightLeft || leftRight || horizontal)
	{
		printf("\nПобеда");
	}

	for (int i = 0; i < n; i++)  
		free(arrd2[i]);   
	free(arrd2);
	free(arrd1);
}