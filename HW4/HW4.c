
/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №4. Массивы
HW4.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-10-21
*/

void swapInt(int *a, int *b);
void printArr(int arr[][3] , int col, int row);


#include <stdio.h>
#include <math.h>

//Задание №1 Реализовать пузырьковую сортировку двумерного массива
// индекс числа двумерного массива можно представить следующим произведением  index = (([i]*col * [j]*row) - 1)
// вернуть номер колонки и столца можно по формуле [i] = index / col , j = index % row+1
// Возможно преобразовать сортировку массива по следующей формуле

void bubleArrSort(int arr[][3] , int col, int row){
	int index = col * row -1;
	for (int i = 0; i < index; ++i){
		for(int j=0; j < index-1; ++j){
			if (arr[j / col ][j % row+1] > arr[(j-1) / col + 1][(j-1) % row])
				swapInt(&arr[j / col ][j % row+1], &arr[(j-1) / col + 1][(j-1) % row]);
		}
	}
}

// Задание №2 Описать подробную блок-схему алгоритма Трабба-Прадо-Кнутаю - приведена в архиве в формате .jpeg

// Задание №3 Реализовать алгоритм Трабба-Прадо-Кнута в коде на языке С
//Заполнение массива 3-1
void arrSet(float *arr, int length){
	for (int i = 0; i < length; ++i){
		printf("Input number %d/%d:", i+1, length);
		scanf("%f", &arr[i]);
	}
}

//Инверсия массива 3-2
void arrRevers(float *arr, int length){
	float temp;
	int left = 0;
	int right = length-1;
	while(left < right){
		temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		++left;
		--right;
	}
}


// Расчет по формуле ТРК 3-3
float getTPK(float x){
	return sqrt(fabs(x)) + 5 * pow(x, 3);
}
// Цикл для каждого элемента массива по расчету с выводом предупреждения при привышении 400
void arrvalueTPK(float *arr, int length){
	for(int i=0; i<length; ++i){
		if (getTPK(arr[i]) > 400) 
			printf("The TPK value of number %0.2f {index %d} more that 400.\n", arr[i], i);
		else printf("f(%0.2f) = %0.2f\n", arr[i], getTPK(arr[i]));
	}
}


int main(int argc, char const *argv[])
{
	//Задание №1 в main
	int arr[3][3]={{1,9,2}, {5,7,6}, {4,3,8}};
	printArr(arr, 3, 3);
	printf("\n **Buble Sort**\n");
	bubleArrSort(arr, 3, 3);
	printArr(arr, 3, 3);

	printf("\n **TPK algorithm**\n");
	
	//Задание №3
	float arrTPK[11] = {0}; 	// Инициализация массива
	arrSet(arrTPK, 11);			// 3-1. Запрос значений
	arrRevers(arrTPK, 11);		// 3-2. Инверсия массива - (по условиям базовой задачи TPK данную функцию можно было пропустить и при расчете занчений "пробегать" массив от большего индекса к меньшему т.к. листинг языка С это позволят в отличии от того же phyton) 
	arrvalueTPK(arrTPK, 11);	// 3-3. Вычисление по формуле значений массива с информаированием пользователя при привышении 400

	return 0;
}


//Своп значений инт
void swapInt(int *a, int *b){
	int temp = 0;
	temp = *a;
	*a = *b;
	*b= temp;
}

//Печать 2D массива
void printArr(int arr[][3] , int col, int row){
	for (int i = 0; i < col; ++i){
		for(int j=0; j < row; ++j){
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
}