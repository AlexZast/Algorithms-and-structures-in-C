/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №7. Динамические структуры данных
HW7.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-11-01
*/

#include <stdio.h>
#include <stdlib.h>

// Задание №1. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.

typedef struct {
    int dat;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} Stack;

void pushStack(Stack* lst, int data);
Node* popStack(Stack* lst);
void init(Stack* lst);

//Функция проверки, если функция возращает -1 - все корректно, иначе функция возращает адрес позиции с ошибкой
int Check(char* string) {
    const int TYPES = 3;
    char braces[][2] = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    Stack *st = (Stack*) malloc(sizeof(Stack));
    init(st);
    int countIndex = 0;
    while (*string != '\0') {
        for (int i = 0; i < TYPES; ++i) {
            if (*string == braces[i][0])
                pushStack(st, i);
        }
        for (int i = 0; i < TYPES; ++i) {
            if (*string == braces[i][1]) {
                if (st->size == 0)
                    return countIndex+1;
                if (i == st->head->dat)
                    popStack(st);
                else
                    return countIndex+1;
            }
        }
        string++;
        countIndex++;
    }
    return -1;
}

// Задание №2. Создать функцию, копирующую односвязный список (без удаления первого списка).
typedef struct {
    Node *head;
    int size;
} List;

void initList(List* lst);
void insert(List* lst, int data);
void printNode(Node *n);
void printList(List* lst);

// Копировать будем путем перебора нодов первого списка и копирование данных второго списка
void listCopy(List* fst, List* scnd){
    Node* current = fst->head;

    if(current == NULL){
        printf("%s\n", "List is empty!");
        return;
    }
    while(current != NULL){
        insert(scnd, current->dat);
        current = current->next;
    }
}

// Задание №3. Реализуйте алгоритм, который определяет, отсортирован ли связный список.
// Список может быть отсортирован в прямом и обратном порядке, если отортировано в прямом будем возращать 1 если в обратном -1, если не отсортирован то 0, а если все элементы листа равны то 5

int isSort(List* lst){
    int flag;
    Node* current = lst->head;
    Node* currnext = current->next;
    if(current == NULL){ //элементов нету
    printf("%s\n", "Empty list" );
    return 0;
    } else if(current->next == NULL) { // Список из одного элемента считается отсортированным
        return 1;
    }
    do {
    flag = (current->dat > currnext->dat) ? -1 : ((current->dat < currnext->dat) ? 1 : 5); // 5 - в данном случае показывает равентсво 2х значений
    current = current->next;
    currnext = current->next;
    } while(!(current->next !=NULL || flag == 5));
    if (flag == 5) return flag; // если мы вышли из прошого цикла с флагом 5 то все элементы цикла равны

    while (current->next != NULL){		// Начнем поочередно сравнивать элементы
        int s = (current->dat >= currnext->dat) ? -1 : ((current->dat <= currnext->dat) ? 1 : 5);
        if (flag != s){
            return 0; 
        }
        current = current->next;
        currnext = current->next;
    }
    return flag;
}



int main()
{
    //Задание №1. Проверка в Main
    printf("%s\n", "\n***** No.1 *****\n");
    // Правильные
    printf("%d \n", Check("()"));
    printf("%d \n", Check("([])()"));
    printf("%d \n", Check(" {}()"));
    printf("%d \n", Check("([{}])"));
    // Не правильные
    printf("%d \n", Check(")("));
    printf("%d \n", Check("())({)"));
    printf("%d \n", Check("])})"));
    printf("%d \n", Check("([(])"));
    // Выражения
    printf("%d \n", Check("(2+(2*2))"));
    printf("%d \n", Check("[2/{5*(4+7)}]"));

    // Задание №2. Проверка в Main
    printf("%s\n", "\n***** No.2 *****\n");
    List *fst = (List*) malloc(sizeof(List));
    List *scnd = (List*) malloc(sizeof(List));
    initList(fst);
    initList(scnd);

    printList(fst);
    printList(scnd);
    // Наполнене первого листа
    insert(fst, 15);
    insert(fst, 12);
    insert(fst, 11);
    insert(fst, 10);
    // Вывод первого листа
    printList(fst);
    // Копирование из первого во второй
    listCopy(fst, scnd);
    // Вывод второго листа
    printList(scnd);

    // Задание №3. Проверка в Main
    printf("%s\n", "\n***** No.3 *****\n");

    printList(fst);
    printf("%d\n", isSort(fst));

    insert(scnd, 12);
    printList(scnd);
    printf("%d\n", isSort(scnd));
    return 0;
}






// Дополнительные функции
void init(Stack* lst){
    lst->head = NULL;
    lst->size = 0;
}

void pushStack(Stack* lst, int data){
    Node *new = (Node*) malloc(sizeof(Node));
    new->dat = data;
    new->next = lst->head;
    lst->head = new;
    lst->size++;
}
Node* popStack(Stack* lst){
    Node* current = lst->head;
    Node* parent = NULL;
    if(current == NULL)
        return NULL;
    lst->head = current->next;
    lst->size--;
    return current;
}

void printNode(Node *n){
    if(n == NULL){
        printf("[]");
        return;
    }
    printf("[%d] ",n->dat);
}

void printList(List* lst){
    Node* current = lst->head;
    if (current == NULL){
        printNode(current);
    } else {
        do {
            printNode(current);
            current = current->next;
        } while(current != NULL);
    }
    printf("Size: %d\n", lst->size);
}


void initList(List* lst){
    lst->head = NULL;
    lst->size = 0;
}

void insert(List* lst, int data){
    Node* new = (Node*) malloc(sizeof(Node));
    new->dat = data;
    new->next = NULL;

    Node* current = lst->head;
    if(current == NULL){
        lst->head = new;
        lst->size++;
    }
    else {
        while(current->next !=NULL){
            current = current->next;
        }
        current->next = new;
        lst->size++;
    }

}
