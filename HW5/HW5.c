/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №5. Сложные сортировки массивов
HW5.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-10-24
*/

#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b);
void fillRandom(int* arr, int len, int border);
void printArr(int* arr , int len);
int partition(int *arr, int left, int right);
void insertSort(int *arr, int left, int right);
int median(int a, int b, int c);


//Задание №1. Описать в коде улучшенный алгоритм быстрой сортировки
// Если оставшихся значений > 10 рекурсивный вызов, иначе сортировка вставками
void improvedQuickSort(int * arr, int left, int right){
    if (right-left < 11){
        insertSort(arr, left, right);		// Сортировка вставкаи
        return;
    }
    //Быстрая сортировка вокруг медианы если значений >10
    int med = median(arr[left], arr[(left+right) / 2], arr[right]); // Получение медианы
    swap(&arr[(arr[left] == med ? left : (arr[right] == med ? right : ((left+right) / 2)))], &arr[(left+right) / 2]); // установка медианы в середину
    int i = partition(arr, left, right);		// Поулчение 2х последовательностей вогруг медианного значения
    //Рекурсивный вызов двух половин
    improvedQuickSort(arr, left, i);
    improvedQuickSort(arr, i+1, right);

}
//Сортировка вставками
void insertSort(int *arr, int left, int right){
    int temp , poz;
    for (int i = left+1; i <= right; ++i){
        temp = arr[i];
        poz = i-1;
        while (poz>= 0 && arr[poz] > temp){
            arr[poz+1] = arr[poz];
            poz--;
        }
        arr[poz+1] = temp;
    }
}
//Частичная сортировка массива вокруг медианного значения
int partition(int *arr, int left, int right){
    int v = arr[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j){
        while (arr[i] < v) i++;
        while (arr[j] > v) j--;
        if (i >= j) break;
        swap(&arr[i++], &arr[j--]);
    }
    return j;
 }

 /* Задание №2. Сортировать в массиве целых положительных чисел только чётные числа,
 нечётные оставив на своих местах при помощи алгоритма блочной сортировки, то есть массив вида 
 [0 2 8 3 4 6 5 9 8 2 7 3] превратить в [0 2 2 3 4 4 5 9 8 8 7 3]*/

void oddBucketSort(int* arr, int len){
	const int max = len;
	const int b = 11; // Добавим дополнительное "ведро" только для нечетных элементов массива которые не будут сортироваться

	int buckets [b][max+1];
	for (int i = 0; i < b; ++i){
		buckets[i][max] = 0;
	}

	for (int digit = 1; digit < 1000000000; digit *=10){
		for (int i = 0; i < max; ++i){
			int counter;
			// Добавим условие что если число четное то оно сортируется методом блочной сортировки, если нет то перемещеается в дополнительное "ведро"
			if (arr[i]%2 == 0){
				int d = (arr[i] / digit) % (b-1);
				counter = buckets[d][max];
				buckets[d][counter] = arr[i];
				counter++;
				buckets[d][max] = counter;
			} 
			 else 
			{
			 	counter = buckets[10][max];
			 	buckets[10][counter] = arr[i];
			 	counter++;
			 	buckets[10][max] = counter;
			 }
		}

		int idx = 0;
		for (int i = 0; i < b; ++i) {
			for (int j = 0; j < buckets[i][max]; j++){
				arr[idx++] = buckets[i][j];
			}
			buckets[i][max]=0;
		}
	}
}

int main()
{
    // Задание №1.
    const int SZ = 15;
    int arr[SZ];
    fillRandom(arr, SZ, 100);
    printArr(arr, SZ);
    improvedQuickSort(arr, 0, SZ-1);
    printArr(arr, SZ);
    // Задание №2.
	fillRandom(arr, SZ, 100);
	printArr(arr, SZ);
    oddBucketSort(arr, SZ);
   	printArr(arr, SZ);

    return 0;
}


//Вспомогательные функции
//Своп значений
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b =  temp;
}

// Заполнение массива рандомными значениями по знаменателю border
void fillRandom(int* arr, int len, int border){
    for (int i = 0; i < len; ++i){
        *(arr+i) = rand() % border;
    }
}

// Печать переданного массива
void printArr(int* arr , int len){
    for (int i = 0; i < len; ++i){
        printf("%3d,", arr[i]);
    }
    printf("\n");
}

// Получение миданы 3х значений
int median(int a, int b, int c){
    return (a >= b && a <= c) || (a <= b && a >= c) ? a : ((b >= a && b <= c) || (b <= a && b >= c) ? b : c);
}

