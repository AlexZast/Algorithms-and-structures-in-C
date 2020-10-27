/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №3. Стеки, очереди и списки
HW6.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-10-27
*/

#include <stdio.h>
#include <stdlib.h>

// Задача №1. Описать очередь с приоритетным исключением
#define SIZE 10
// Структура нода
typedef struct
{
	int priority;
	int date;
} Node;

// Инициализация указателя на массив нодов
Node* arr[SIZE];

int pointer = -1;
int items = 0;

//Инициализация массива
void init(){
	for (int i =0; i < SIZE; ++i){
		arr[i] = 0;
	}
	items = 0;
}

//Вставка элемента в стэк
void insert(int pr, int dt){
	Node *node = (Node*) malloc(sizeof(Node));
	node->date = dt;
	node->priority = pr;

	if (items == SIZE){
		printf("%s\n", "Stack full");
		return;
	}
	arr[++pointer] = node;
	++items;
}

// Приоритетное извлечение нода
Node* extract(){
	// Если элементов нету то вывод что пусто
	if (pointer == -1){
		printf("%s\n", "Is empty");
		return NULL;
	}

	// Если элементы есть то задаем нулевой адрес массива как временный
	Node *tmp = arr[0];
	int ptr = 0;

	// если нулевой элемент единственный то его и вернем
	if(items==1){
		arr[pointer] = NULL;
		items--;
		pointer--;
		return tmp;
	}

	//если нулевой элемент не единственный то поочередно сравним его с другими элементами стека
	//Находим первый добавленный нод с минимальным приоритетом
	for(int i = 1; i < items; ++i){
		if(tmp->priority > arr[i]->priority){
			tmp = arr[i];
			ptr = i;
		}
	// Теперь tmp содержит указатель на память нода и ptr - его номер в массиве
	// Сдвинем указтели находящиеся правее до изъятого значения (данная функция обеспечивает стабильность функции, если взамен изятого элемента ставить последний - то стабильность теряется(элементы с одинаковым приоритетом могут меняться местами))
	}
	for(int i = ptr; i < items-1; ++i){
		arr[i] = arr[i+1];
	}
	//Затрем последний элемент который продублировался
	arr[items-1] = NULL;
	items--;
	pointer--;
	// Вернем указатель на нужный нам нод
	return tmp;
}

void printStack(){
	printf("[ ");
	for (int i = 0; i < SIZE; ++i)
	{
		if (arr[i] == NULL)
			printf("[*,*] " );
		else
			printf("[%d, %d] ", arr[i]->priority, arr[i]->date);
	}
	printf("]\n");
}

// Задача №2. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
#define SZ 100

// Инициализируем массива для его испльзования как стека
char stackArr[SZ];
int stackPtr = -1;

// Функция добавления элемента
void push(char c){
	if(stackPtr < SIZE){
		stackArr[++stackPtr] = c;
	} else {
		printf("%s\n", "Stack overflow." );
	}
}
// Функция извлечения элемента
char pop(){
	if (stackPtr != -1){
		return stackArr[stackPtr--];
	} else {
		printf("%s\n","Stack empty" );
		return -1;
	}
}

// Функция печати стека
void printArr(){
	printf("\n Number in binary: [ ");
	while (stackPtr != -1){
		printf("%c", pop());
	}
	printf(" ]\n");
}
// Функция перевода из десятичной в двоичную
void intToBin(int dt){
	stackPtr = -1;
	int temp = dt;
	while(temp > 0){
		if (temp%2 == 1) push('1');
		else push('0');
		temp /= 2;
	}
}


int main(int argc, char const *argv[])
{
	//Задача №1. Проверка в main
	init();
	insert(1,2);
	insert(3,234);
	insert(6,123);
	insert(1,23);
	insert(4,255);
	insert(6,123);
	insert(5,66);
	insert(3,22);
	insert(1,77);
	insert(1,88);

	printStack();
	
	while (items != 0){
		Node *tmp = extract(); // "Забарем" элемент из памяти 
		printf("[%d, %d] ", tmp->priority, tmp->date); // вывод на печать
		free(tmp); // Очистим занимаемую память
		tmp = NULL;
	}
	printf("\n");

	//Заданча №2. Проверка в main
	printf("Enter the number: ");
	int p;
	scanf("%d", &p);
	intToBin(p);
	printArr();

	return 0;
}