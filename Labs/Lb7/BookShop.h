#pragma once
#include "Book.h"
#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
typedef struct
{
	const int warehouseSize = 1000;
	int numberOfUnicBooks = 0;
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
		bool exit = false;
		while (!exit)
		{
			system("cls");
			printf("1.Добавить книгу\n");
			printf("2.Назад\n");
			char action = _getch();
			switch (action)
			{
			case '1': 
				printf("Автор: ");
				gets_s(book.author);
				printf("Название: ");
				gets_s(book.name);
				printf("Количество экземпляров: ");
				scanf_s("%d", &book.numberOfCopies);
	
				printf("Цена покупки: ");
				scanf_s("%f", &book.purchasePrice);
				printf("Цена продажи: ");
				scanf_s("%f", &book.sellingPrice);
				cin.ignore();
				PutBookOnWarehouse(book,true);
				break;
			case '2': 
				exit = true;
				break;
			}
		}
	}
	void SetBookShop()
	{
		ifstream shopInfo("ShopInformation.txt");
		bookInfoInput.open("BookInformation.txt");
		Book buffer;
		int i = 0, k = 0;
		while (!bookInfoInput.eof())
		{
			if (i == 0)
			{		
				int j = 0;
				char author[30];
				char a = bookInfoInput.get();
				while (a!='_')
				{
					if (bookInfoInput.eof())
					{
						break;
					}
					author[j] = a;
					a = bookInfoInput.get();
					j++;
				}
				author[j] = '\0';
				for (int i = 0; i <= j; i++)
				{
					buffer.author[i] = author[i];
				}
				i++;
			}
			else if (i == 1)
			{
				int j = 0;
				char name[30];
				char a = bookInfoInput.get();
				while (a != '_')
				{
					name[j] = a;
					a = bookInfoInput.get();
					j++;
				}
				name[j] = '\0';
				for (int i = 0; i <= j; i++)
				{
					buffer.name[i] = name[i];
				}
				i++;
			}
			else if (i == 2)
			{
				int j = 0;
				char numberOfCopies[30];
				char a = bookInfoInput.get();
				while (a != '_')
				{
					numberOfCopies[j] = a;
					a = bookInfoInput.get();
					j++;
				}
				numberOfCopies[j] = '\0';
				buffer.numberOfCopies = atoi(numberOfCopies);
				i++;
			}
			else if (i == 3)
			{
				int j = 0;
				char purchasePrice[30];
				char a = bookInfoInput.get();
				while (a != '_')
				{
					purchasePrice[j] = a;
					a = bookInfoInput.get();
					j++;
				}
				purchasePrice[j] = '\0';
				buffer.purchasePrice = atof(purchasePrice);
				i++;
			}
			else if (i == 4)
			{
				int j = 0;
				char sellingPrice[30];
				char a = bookInfoInput.get();
				while (a != '\n')
				{
					sellingPrice[j] = a;
					a = bookInfoInput.get();
					j++;
					if (bookInfoInput.eof())
						break;
				}
				sellingPrice[j] = '\0';
				buffer.sellingPrice = atof(sellingPrice);
				PutBookOnWarehouse(buffer);
				i = 0;
			}
		}
		i = 0;
		while (!shopInfo.eof())
		{
			if (i == 0)
			{
			int j = 0;
			char numberOfBooks[30];
			char a = shopInfo.get();
			while (a != '_')
			{
				numberOfBooks[j] = a;
				a = shopInfo.get();
				j++;
			}
			numberOfBooks[j] = '\0';
			int value = 0;
			for (int i = 0; i < numberOfUnicBooks; i++)
			{
				value += books[i].numberOfCopies;
			}
			this->numberOfBooks = value;
			i++;
			}
			else if (i == 1)
			{
				int j = 0;
				char  numberOfBooksSold[30];
				char a = shopInfo.get();
				while (a != '_')
				{
					numberOfBooksSold[j] = a;
					a = shopInfo.get();
					j++;
				}
				numberOfBooksSold[j] = '\0';
				this->numberOfBooksSold = atof(numberOfBooksSold);
				i++;
			}
			else if (i == 2)
			{
				int j = 0;
				char  earnings[30];
				char a = shopInfo.get();
				while (a != '_')
				{
					earnings[j] = a;
					a = shopInfo.get();
					j++;
				}
				earnings[j] = '\0';
				this->earnings = atof(earnings);
				i++;
			}
			else if (i == 3)
			{
				int j = 0;
				char  numberOfOrders[30];
				char a = shopInfo.get();
				while (a != '\n')
				{
					numberOfOrders[j] = a;
					a = shopInfo.get();
					j++;
					if (shopInfo.eof())
						break;
				}
				numberOfOrders[j] = '\0';
				this->numberOfOrders = atof(numberOfOrders);
				i = 0;
			}
		}
	}
	void SaveBookInFile(Book book)
	{
		bookInfoOutput.open("BookInformation.txt", ios_base::app);
		if(bookInfoOutput.is_open())
		bookInfoOutput
			<< book.author << '_'
			<< book.name << '_'
			<< book.numberOfCopies << '_'
			<< book.purchasePrice << '_'
			<< book.sellingPrice << '\n';
		bookInfoOutput.close();
	}
	void PutBookOnWarehouse(Book book, bool isNewBook = false)
	{
		if (numberOfBooks + book.numberOfCopies > warehouseSize)
			printf("На складе нет места\n");
		else
		{
			int indexOfBook = FindBookIndexOnWarehose(book);
			if (indexOfBook != -1)
			{
				books[indexOfBook].numberOfCopies += book.numberOfCopies;
				UpdateBookInfo();
				UpdateShopInfo(book.numberOfCopies,indexOfBook,false);
			}
			else
				AddNewBook(book,isNewBook);
			if(isNewBook && indexOfBook == -1)
			SaveBookInFile(book);
		}
	}
	void AddNewBook(Book newBook, bool isNewBook = false)
	{
		if (numberOfBooks > warehouseSize)
			printf("На складе нет места\n");
		else
		{
			bool isFreePlace = false;
			for (int i = 0; i < numberOfUnicBooks; i++)
			{
				if (books[i].numberOfCopies == 0)
				{
					books[i] = newBook;
					isFreePlace = true;
					break;
				}
			}
			if (isNewBook)
			{
				UpdateShopInfo(newBook.numberOfCopies, numberOfUnicBooks, false);
			}
			if (!isFreePlace)
			{
				books[numberOfUnicBooks] = newBook;
				numberOfUnicBooks++;
				numberOfBooks += newBook.numberOfCopies;
				printf("Книга успешно добавлена\n");
			}
		}
	}
	int FindBookIndexOnWarehose(Book book)
	{
		for (int i = 0; i < numberOfUnicBooks; i++)
		{
			if (strcmp(book.name,books[i].name) ==0
				&& strcmp(book.author,books[i].author) ==0)
				return i;
		}
		return -1;
	}
	void ShowSalesHistory()
	{
		ifstream fin("SalesHistory.txt");
		while (!fin.eof())
		{
			printf("%c", fin.get());
		}
	}
	void UpdateSalesHistory(Book bookSaled, int amount, int earn)
	{
		ofstream fin;
		fin.open("SalesHistory.txt", ios_base::app);
		fin << "Название: " << bookSaled.name << endl
			<< "Автор: " << bookSaled.author << endl
			<< "Количество проданных копий: " << amount << endl
			<< "Цена продажи: " << earn << endl;
		fin.close();
	}
	void UpdateShopInfo(int amount, int numberOfBook, bool isCheckout = true)
	{
		if (isCheckout)
		{
			numberOfBooksSold += amount;
			numberOfBooks -= amount;
			int earn = amount * books[numberOfBook].sellingPrice;
			earnings += earn;
			numberOfOrders++;
		}
		else
		{
			numberOfBooks += amount;
		}
		PutShopInfoInFile();
	}
	void UpdateBookInfo()
	{
		bookInfoOutput.open("BookInformation.txt", ios_base::out);
		for (int i = 0; i < numberOfUnicBooks; i++)
		{
			if (books[i].numberOfCopies == 0) {}
			else
				bookInfoOutput
				<< books[i].author << '_'
				<< books[i].name << '_'
				<< books[i].numberOfCopies << '_'
				<< books[i].purchasePrice << '_'
				<< books[i].sellingPrice << '\n';
		}
		bookInfoOutput.close();
	}
	void PutShopInfoInFile()
	{
		ofstream shopInfo("ShopInformation.txt", ios_base::trunc);
		shopInfo
			<< numberOfBooks << '_'
			<< numberOfBooksSold << '_'
			<< earnings << '_'
			<< numberOfOrders;
	}
	void Checkout(Book book, int amount)
	{
		int numberOfBook = FindBookIndexOnWarehose(book);
		if (numberOfBook !=-1)
		{
			if (books[numberOfBook].numberOfCopies >= amount)
			{
				books[numberOfBook].numberOfCopies -= amount;
				int earn = amount * books[numberOfBook].sellingPrice;
				UpdateSalesHistory(book, amount, earn);
				UpdateShopInfo(amount, numberOfBook);
				UpdateBookInfo();
				printf("Заказ размещён.\n");
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
		for (int i = 0; i < numberOfUnicBooks; i++)
		{
			cost += books[i].numberOfCopies * books[i].sellingPrice;
		}
		return cost;
	}
	void ShowShopReport()
	{
		printf("Количество книг на складе: %d\n", numberOfBooks);
		printf("Общая стоимость: %f\n", CalcCost());
		printf("Количество заказов: %d\n", numberOfOrders);
		printf("Количество проданных книг: %d\n", numberOfBooksSold);
		printf("Прибыль: %f\n", earnings);
	}
	void ShowBookReport()
	{
		for (int i = 0; i < numberOfUnicBooks; i++)
		{
			books[i].BookReport();
		}
	}
}BookShop;