/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №10. Хеш-таблицы
HW10.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-11-11
*/


#include <stdio.h>
#include <stdlib.h>

// Задание №1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
int stringHash(char *ch) {
    int result = 0;
    while (*ch != 0) {
        result = result + *ch;
        ch += 1;
    }
    return result;
}
/* Задание №2. Имеются монеты номиналом 50, 10, 5, 2, 1 коп. Напишите функцию которая минимальным 
количеством монет наберет сумму 98 коп. Для решения задачи используйте “жадный” алгоритм.*/

int moneyType[5] = {50, 10, 5, 2, 1};

int* howMachMoney(int sum) {
	int *moneyArr = (int*) malloc(sizeof(int[5]));
	for (int i = 0; i < 5; ++i){
		moneyArr[i] = 0;
	}
	while (sum != 0){
		for (int i = 0; i < 5; ++i){
			if(moneyType[i] <= sum) {
				++moneyArr[i];
				sum -= moneyType[i];
				break;
			}
		}
	}
	return moneyArr;
}

void printMoney(int *arr){
	for (int i = 0; i < 5; ++i){
		printf("You need take %d coins for %d kop.\n", arr[i], moneyType[i]);
	}
}

int main()
{
	// Задание №1. Проврка в main
	printf("\n%s\n\n", "**** Task No.1 ****");
	printf("%d\n", stringHash("Jim-Bim"));
	

	// Задание №2. Проверка в main
	printf("\n%s\n\n", "**** Task No.2 ****");
	printMoney(howMachMoney(54));

	return 0;
}