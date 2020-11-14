/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №11. Введение в криптографию
HW11.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW) + QT Creator
2020-11-14
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Задание №1. Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
// Загравные 65 - 90, прописные 97-122, остальное - спецсимволы(не меняються). (*прим: сдвиг только по тому регистру - по которму написан символ)
void encryptionCaesar(unsigned char *messenge, int key){
    int shift = key % 26;                           // Максимальный сдвиг по алфавиту
    while (*messenge != 0){
        if (*messenge >= 65 && *messenge <= 90){ // Для заглавных букв
            *messenge = *messenge + shift;
            if (*messenge > 90 || *messenge < 65){
                *messenge = 65 + (*messenge - 90) % 26; // Если ушли за буквенные символы по ASCII
            }
        }
        if (*messenge >=97 && *messenge <=122){	// Для строковых букв
            *messenge = *messenge + shift;
            if (*messenge > 122 || *messenge < 97){
                *messenge = 97 + (*messenge - 122) % 26;
            }
        }
        ++messenge;
    }
}

void decryptionCaesar(unsigned char *messenge, int key){
    int shift = key % 26;
    while (*messenge != 0){
        if (*messenge >= 65 && *messenge <= 90){ // Для заглавных букв
            *messenge = *messenge - shift;
            if (*messenge > 90 || *messenge < 65){
                *messenge = 90 - (65 - *messenge) % 26;
            }
        }
        if (*messenge >=97 && *messenge <=122){	// Для строковых букв
            *messenge = *messenge - shift;
            if (*messenge > 122 || *messenge < 97){
                *messenge = 122 - (97 - *messenge) % 26;
            }
        }
        ++messenge;
    }
}

// Задание №2. Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов.

void encruptionTabel(char *str, const int colum){
    // Получим количество строк
    int row;
    if (strlen(str) % colum == 0){
        row = strlen(str) / colum;
    } else {
        row = strlen(str) / colum + 1;
    }
    //создаем временный массив для заполнения
    unsigned char **array = malloc(sizeof (char*[row]));
    for (int i = 0; i < row; ++i){
        array[i] = malloc(sizeof (char[colum]));
    }
    //очищаем массив
    for(int i = 0; i<row; ++i){
        for(int j = 0; j< colum; ++j){
            array[i][j] = 0;
        }
    }
    // заполняем массив по столбцам
    for(int j = 0; j < colum; ++j){
        for(int i = 0; i<row; ++i){
        int indx = i + j * row;
        if(indx < strlen(str)){
            array[i][j] = str[indx];
        } else if(i*j == (colum-1)*(row-1)){
            array[i][j] = 0;
        } else {
            array[i][j] = 120;
        }
      }
    }
    // считываем массив по строкам
    for(int i = 0; i < row; ++i){
        for(int j = 0; j< colum; ++j){
            int indx = j + i * (colum);
            str[indx] = array[i][j];
        }
    }

    // выведем массив
    printf("\n");
    for(int i = 0; i < row; ++i){
        for(int j = 0; j< colum; ++j){
            printf("%c, ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Выполним дейстия по шифрованию в обратном порядке
void decryptionTabel(char *str, const int colum){
    // Получим количество строк
    int row;
    if (strlen(str) % colum == 0){
        row = strlen(str) / colum;
    } else {
        row = strlen(str) / colum + 1;
    }
    //создаем временный массив для заполнения
    unsigned char **array = malloc(sizeof (char*[row]));
    for (int i = 0; i < row; ++i){
        array[i] = malloc(sizeof (char[colum]));
    }
    //очищаем массив
    for(int i = 0; i<row; ++i){
        for(int j = 0; j< colum; ++j){
            array[i][j] = 0;
        }
    }
    // заполняем массив по строкам (при расшифровке мы уверены что размеры массива и строки одинаковые поэтому проверок уже не надо)
    for(int i = 0; i < row; ++i){
        for(int j = 0; j< colum; ++j){
            int indx = j + i * (colum);
            array[i][j] = str[indx];
        }
    }
    // считываем массив по столбцам
    for(int j = 0; j < colum; ++j){
        for(int i = 0; i<row; ++i){
            int indx = i + j * row;
            str[indx] = array[i][j];
        }
    }
}

int main()
{
    //Задание №1. Проверка в Main
    unsigned char messenge[] = "Hellow World and V";

    printf("%s\n", messenge);
    encryptionCaesar(messenge, 79);
    printf("%s\n", messenge);
    decryptionCaesar(messenge, 79);
    printf("%s\n", messenge);

    //Задание №2. Проверка в Main

    char str[] = "The secret messenge";
    printf("\n%s\n", str);
    encruptionTabel(str, 6);
    printf("%s\n", str);
    decryptionTabel(str, 6);
    printf("\n%s\n", str);

    return 0;
}
