/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №2
HW2-part1.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-10-15
*/

//Задание №1. Написать функцию проверки, является ли число простым

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
	int a;
	bool flag = true;

	printf("Enter the numbers more that 0: ");
	scanf("%d", &a);

	if(a <= 3){
		printf("Number %d is simple\n", a);	
		return 0;
	}


	int arr[255] = {2};
	int cap = 1;
	for(int i = 3; i<=a; i+=2){
		flag = true;
		for(int j=0; j<cap; ++j){
			if(i % arr[j] == 0){
				flag = false;
				break;
			}
		}
		if(flag == true){
				arr[cap] = i;
				++cap;
		}
	}

	if(a == arr[cap-1]){
		printf("Number %d is simple\n", a);
	} 
	else {
		printf("Number %d is`n simple\n", a);
	}
	
	
	return 0;
}