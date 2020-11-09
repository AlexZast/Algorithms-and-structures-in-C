#include <stdio.h>
#include <stdlib.h>

#define SZ 14



// ***** Задание №1 Реализовать обход в глубину с использованием стека *****

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    struct Node *head;
    int size;
} Stack;

// Вспомогательные функции (реализация приведена ниже)
void pushStack(Stack* lst, int data);
int popIntStack(Stack* lst);
void initStack(Stack* lst);
void sortArr(int arr[2][SZ]);
void PrintArr(int arr[2][SZ]);
void cleanVisited();


// Матрица связей графа
int matrix[SZ][SZ] = {
//		A0  B1  C2  D3  E4  F5  G6  H7  I8  J9 K10 L11 M12 N13
/*A0*/	{0,  1,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0},
/*B1*/	{1,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0},
/*C2*/	{0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
/*D3*/	{0,  0,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1},
/*E4*/	{0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0},
/*F5*/	{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
/*G6*/	{1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0},
/*H7*/	{1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0},
/*I8*/	{0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0},
/*J9*/	{0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0},
/*K10*/	{0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  1,  0},
/*L11*/	{0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  0,  1,  0},
/*M12*/	{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1},
/*N13*/	{0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0},
};

// Флаги посещения графов
int visited[SZ] = {0};


// Обход в глубину с исользованием стека
void stackDeepTravel(int sz, int fist, Stack* stack){
    pushStack(stack, fist);
    while(stack->size > 0){
        int now = popIntStack(stack);
        if (visited[now] == 0){
            visited[now] = 1;
            printf("%d, ", now);
        } else continue;

        for (int i = 0; i < sz; ++i){
            if(matrix[now][i] == 1 && visited[i] !=1){
                pushStack(stack, i);
            }
        }
    }
    printf("\n");
}

/* Задание №2 Моделируем робот поисковой системы.
Дан готовый простой граф с циклическими связями.
Нужно обойти этот граф двумя способами и подсчитать количество ссылок на каждый из узлов графа (полустепень захода).
	обход графа рекурсивной функцией (с подсчётом только смежных со стартовой вершин)
	обход графа по матрице смежности (с подсчётом всех вершин графа)
В конце обхода вывести два получившихся списка всех узлов в порядке уменьшения количества ссылок на них. */

// 2.1 Обход графа рекурсивной функцией (с подсчётом только смежных со стартовой вершин)

int recursion[2][SZ] = {0};
void recursionCount(int graf){
	if(visited[graf] == 1){
		return;
	}
	visited[graf] = 1;
	for (int j = 0; j < SZ; ++j){
		if(matrix[graf][j] == 1 && graf != j){
			++recursion[1][graf];
			if(visited[j] != 1){
				recursionCount(j);
			}
		}
	}

	
}

// 2.2 Обход графа по матрице смежности (с подсчётом всех вершин графа)
int countMatrixArr[2][SZ] = {0};

void matrixCount(){
	for (int i = 0; i < SZ; ++i){
		for (int j = 0; j < SZ; ++j){
			if (matrix[i][j] == 1 && i != j){
				++countMatrixArr[1][i]; 
			}
		}
	}
}


int main()
{
	// Задание №1. Проверка в main
    printf("\n%s\n\n","*** 1. In Depth with Stack ***" );    
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    initStack(stack);
    stackDeepTravel(SZ, 0, stack);
    
    printf("\n%s\n\n","*** 2.1 Recursion Count ***" );
    cleanVisited();
    recursionCount(0);
    sortArr(recursion);
    PrintArr(recursion);

    printf("\n%s\n\n","*** 2.2 Matrix Count ***" );
    matrixCount();
    sortArr(countMatrixArr);
    PrintArr(countMatrixArr);

    return 0;
}



// Дополнительные функции
void initStack(Stack* lst){
    lst->head = NULL;
    lst->size = 0;
}

void pushStack(Stack* lst, int data){
    Node *new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = lst->head;
    lst->head = new;
    lst->size++;
}

int popIntStack(Stack* lst){
    Node* current = lst->head;
    if(current == NULL)
        return -1;
    lst->head = current->next;
    lst->size--;
    int n = current->data;
    return n;
}

void PrintArr(int arr[2][SZ]){
	for(int i = 0; i < SZ; ++i){
		printf(" Graf %c have %d link \n", arr[0][i], arr[1][i]);
	}
	printf("\n");
}

void sortArr(int arr[2][SZ]){
	//Заполнение буквенных значений
	for(int i = 0; i < SZ; ++i){
		arr[0][i] = i+65;
	}

	for (int j = 0; j< SZ; ++j){	
		for(int i = 0; i < SZ-1; ++i){
			if (arr[1][i] < arr[1][i+1]){
				int temp = arr[1][i];
				int temp2 = arr[0][i];
				arr[1][i] = arr[1][i+1];
				arr[0][i] = arr[0][i+1];
				arr[1][i+1] = temp;
				arr[0][i+1] = temp2;
			}
		}
	}
}

void cleanVisited(){
    for (int i =0; i < SZ; ++i){
        visited[i] = 0;
    }
}