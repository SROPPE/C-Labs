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
		scanf_s("�����: %s",&book.author);
		scanf_s("��������: %s", &book.name);
		scanf_s("���������� ����������: %f", &book.numberOfCopies);
		scanf_s("���� �������: %f", &book.purchasePrice);
		scanf_s("���� �������: %f", &book.sellingPrice);
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
			printf("�� ������ ��� �����");
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
		fin << "��������: " << bookSaled.name << endl
			<< "�����: "<< bookSaled.author << endl
			<< "���������� ��������� �����: "<< amount << endl
			<< "���� �������: "<< earn << endl;
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
				printf("�� ������ ������������ �����������\n(������� ����������: %d\n)", books[numberOfBook].numberOfCopies);
		}
		else
			printf("����� ���������� �� ������\n");
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
		printf("���������� ���� �� ������: %d", numberOfBooks);
		printf("����� ���������: %f", CalcCost());
		printf("���������� �������: %d", numberOfOrders);
		printf("���������� ��������� ����: %d", numberOfBooksSold);
		printf("�������: %f", earnings);
	}
	void ShowBookReport()
	{
		for (int i = 0; i < numberOfBooks; i++)
		{
			books[i].BookReport();
		}
	}
}BookShop;