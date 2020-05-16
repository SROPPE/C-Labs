#include <iostream>
#include<conio.h>
using namespace std;
bool Check(char* p)
{
	bool c = true;
	for (int i = 0; i < strlen(p); i++)
	{
		if (p[i] - 48 >= 0 && p[i] - 48 <= 9 || p[i] == 44)
		{
			if (p[i] == 44 && c)
				c = false;
			else if (p[i] == 44 && c == false)
				return true;
		}
		else return true;
	}
	return false;
}
typedef struct Node {
	int queueNumber;
	int value;
	struct Node* next;
	struct Node* prev;
	bool behavior;
} Node;
typedef struct DblLinkedList
{
	int size;
	Node* head;
	Node* tail;
} DblLinkedList;
DblLinkedList* CreateDblLinkedList()
{
	DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}
void* PopFront(DblLinkedList* list)
{
	Node* prev;
	int* tmp;
	if (list->head == NULL) {
		exit(2);
	}

	prev = list->head;
	list->head = list->head->next;
	if (list->head) {
		list->head->prev = NULL;
	}
	if (prev == list->tail) {
		list->tail = NULL;
	}
	tmp =&prev->value;
	free(prev);

	list->size--;
	return tmp;
}
void PushBackQueue(DblLinkedList* list, int value) 
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}
void PushBackList(DblLinkedList* list, int value, int size) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(3);
	}
	char a=0;
	printf("Введите необходимый признак 'A' или 'B'\n");
	
	while (true)
	{
		a = _getch();
		if (a == 'A') 
		{
			tmp->behavior = true;
			break;
		}
		else if (a == 'B')
		{
			tmp->behavior = false;
			break;
		}
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	
	char queueNumberS[10];
	while (true)
	{
		printf("Введите номер очереди: ");
		do
		{
			gets_s(queueNumberS);
		} while (Check(queueNumberS) || atoi(queueNumberS) <= 0);
		if (atoi(queueNumberS)>= 0 && atoi(queueNumberS)<size)
			break;
	}
	int queueNumber = atoi(queueNumberS);
	tmp->queueNumber = queueNumber;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}
Node* GetNth(DblLinkedList* list, int index) {
	Node* tmp = NULL;
	size_t i;

	if (index < list->size / 2) {
		i = 0;
		tmp = list->head;
		while (tmp && i < index) {
			tmp = tmp->next;
			i++;
		}
	}
	else {
		i = list->size - 1;
		tmp = list->tail;
		while (tmp && i > index) {
			tmp = tmp->prev;
			i--;
		}
	}

	return tmp;
}
void QueueProcessing(Node* currentNode, DblLinkedList* queue)
{
	if (currentNode->behavior)
	{
		PushBackQueue(queue, currentNode->value);
	} 
	else
	{
		PopFront(queue);
	}
}

void PrintDblLinkedList(DblLinkedList* list) {
	Node* tmp = list->head;
	while (tmp) {
		printf("%d",tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}
int main()
{
	setlocale(LC_ALL, "ru");
	char listSizeS[10];
	int value = 1;
	printf("Введите размер списка: ");
	DblLinkedList* queueHandler = CreateDblLinkedList();
	do
	{
		gets_s(listSizeS);
	} while (Check(listSizeS) || atoi(listSizeS) <= 0);
	int listSize = atoi(listSizeS);
	DblLinkedList* queueList = new DblLinkedList[listSize];
	for (int i = 0; i < listSize; i++)
	{
		char valueS[10];
		printf("Введите значение для [%d]: ", i);
		do
		{
			gets_s(valueS);
		} while (Check(valueS) || atoi(valueS) <= 0);
		int value = atoi(valueS);
		PushBackList(queueHandler, value,listSize);
		queueList[i] = *CreateDblLinkedList();
	}
	char action;
	while (true)
	{
		printf("\n1.Укажите номер элемента списка.\n2.Выйти\n");
		action = _getch();
		if (action == '1')
		{
			int queueNumber = 1;
			while (true)
			{
				printf("Номер списка: ");
				scanf_s("%d", &queueNumber);
				if (queueNumber < listSize) break;
			}
			Node* currentNode = GetNth(queueHandler, queueNumber);
			PrintDblLinkedList(&queueList[currentNode->queueNumber]);
			QueueProcessing(currentNode,&queueList[currentNode->queueNumber]);
			PrintDblLinkedList(&queueList[currentNode->queueNumber]);
		}
		else if (action == '2') break;
	}
}