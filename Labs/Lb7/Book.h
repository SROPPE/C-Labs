#pragma once
#include"Book.h"
#include <iostream>
typedef struct
{
	char author[50];
	char name[20];
	char requisites[30];
	int numberOfCopies = 0;
	float purchasePrice = 0;
	float sellingPrice = 0;
	void BookReport()
	{
		printf("�����: %s\n", &author);
		printf("��������: %s\n", &name);
		printf("����������� �� ������ %d\n", numberOfCopies);
		printf("���� �������: %f\n", purchasePrice);
		printf("���� �������: %f\n", sellingPrice);
	}
} Book;