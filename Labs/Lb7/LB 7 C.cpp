#include<iostream>
#include<conio.h>
#include<fstream>
#include"BookShop.h"
#include"Book.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	BookShop bookShop;
	bookShop.SetBookShop();
	bool exit = false;
		while (!exit)
		{

			system("cls");
			printf("1.Добавить новую партию книг.\n");
			printf("2.Оформить заказ для покупателя.\n");
			printf("3.Список книг, имеющихся на складе.\n");
			printf("4.История продаж.\n");
			printf("5.Отчёт.\n");
			printf("6.Выход.\n");
			char action = _getch();
			switch (action)
			{
			case '1': 
				bookShop.ReceivingShopOrder();
				break;
			case '2':
			{
				system("cls");
				Book bookSealed;
				printf("Автор: ");
				gets_s(bookSealed.author);
				printf("Название: ");
				gets_s(bookSealed.name);
				printf("Количество: ");
				scanf_s("%d", &bookSealed.numberOfCopies);
				cin.ignore();
				bookShop.Checkout(bookSealed, bookSealed.numberOfCopies);
				_getch();
				break; }
			case '3':
				bookShop.ShowBookReport();
				_getch();
				break;
			case '4':
				bookShop.ShowSalesHistory();
				_getch();
				break;
			case '5':
				bookShop.ShowShopReport();
				_getch();
				break;
			case '6':
				exit = true;
				break;
			}
		}
		bookShop.UpdateBookInfo();
}