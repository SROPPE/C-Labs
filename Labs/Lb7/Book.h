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
		printf("Автор: %s\n", &author);
		printf("Название: %s\n", &name);
		printf("Экзмепляров на складе %d\n", numberOfCopies);
		printf("Цена покупки: %f\n", purchasePrice);
		printf("Цена продажи: %f\n", sellingPrice);
	}
} Book;