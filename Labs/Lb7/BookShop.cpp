#include "Book.h"
#include <iostream>
#include <fstream>
using namespace std;
typedef struct
{
	const int warehouseSize = 100;
	int numberOfBooks = 0;
	int numberOfBooksSold = 0;
	float earnings = 0;
	int numberOfOrders = 0;
	ofstream bookInfoOutput;
	ifstream bookInfoInput;
	char bookInform[30] = "BookInformation.txt";
	Book* books = new Book[warehouseSize];
	void ReceivingShopOrder()
	{
		Book book;
		scanf_s("Автор: %s",&book.author);
		scanf_s("Название: %s", &book.name);
		scanf_s("Количество экзепляров: %f", &book.numberOfCopies);
		scanf_s("Цена покупки: %f", &book.purchasePrice);
		scanf_s("Цена продажи: %f", &book.sellingPrice);
		PutBookOnWarehouse(book);
		SaveBookInFile(book);
	}
	void SetBookShop()
	{

	}
	void SaveBookInFile(Book book)
	{
		bookInfoOutput.open(bookInform);
		bookInfoOutput
			<< book.author + ' '
			<< book.name + ' '
			<< book.numberOfCopies << ' '
			<< book.purchasePrice << ' '
			<< book.sellingPrice <<'\n';
	}
	void PutBookOnWarehouse(Book book)
	{
		int numberOfBook = FindBookIndexOnWarehose(book);
		if (numberOfBook)
			books[numberOfBook].numberOfCopies++;
		else 
			AddNewBook(book);
	}
	void AddNewBook(Book newBook)
	{
		if (numberOfBooks > warehouseSize)
			printf("На складе нет места");
		else
		{
			books[numberOfBooks] = newBook;
			numberOfBooks++;
		}
	}
	int FindBookIndexOnWarehose(Book book)
	{
		for (int i = 0; i < numberOfBooks; i++)
		{
			if (book.name == books[i].name)
				return i;
		}
		return -1;
	}
	void UpdateSalesHistory(Book bookSaled, int amount, int earn)
	{
		ofstream fin;
		fin.open("SalesHistory.txt",ios_base::app);
		fin << "Название: " << bookSaled.name << endl
			<< "Автор: "<< bookSaled.author << endl
			<< "Количество проданных копий: "<< amount << endl
			<< "Цена продажи: "<< earn << endl;
		fin.close();
	}
	void Checkout(Book book,int amount)
	{
		int numberOfBook = FindBookIndexOnWarehose(book);
		if (numberOfBook)
		{
			if (books[numberOfBook].numberOfCopies >= amount)
			{
				books[numberOfBook].numberOfCopies -= amount;
				numberOfBooks -= amount;
				numberOfBooksSold += amount;
				int earn = amount* books[numberOfBook].sellingPrice;
				earnings += earn;
				numberOfOrders++;
				UpdateSalesHistory(book,amount,earn);
			}
			else
				printf("На складе недостаточно экземпляров\n(Текущее количество: %d\n)", books[numberOfBook].numberOfCopies);
		}
		else
			printf("Книга отсутсвует на складе\n");
	}
	float CalcCost()
	{
		float cost = 0;
		for (int i = 0; i < numberOfBooks; i++)
		{
			cost += books[i].numberOfCopies*books[i].sellingPrice;
		}
		return cost;
	}
	void ShowShopReport()
	{
		printf("Количество книг на складе: %d", numberOfBooks);
		printf("Общая стоимость: %f", CalcCost());
		printf("Количество заказов: %d", numberOfOrders);
		printf("Количество проданных книг: %d", numberOfBooksSold);
		printf("Прибыль: %f", earnings);
	}
	void ShowBookReport()
	{
		for (int i = 0; i < numberOfBooks; i++)
		{
			books[i].BookReport();
		}
	}
}BookShop;