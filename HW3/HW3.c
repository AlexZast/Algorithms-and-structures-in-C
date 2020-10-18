/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №3. Рекурсия, рекурсивные алгоритмы
HW3.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-10-18
*/



#include <stdio.h>

//Задание №1. Реализовать функцию перевода чисел из десятичной системы в двоичную, используя рекурсию.

//Вариант 1. Функция которая сразу выводит значение в двоичной системе:
void DecToBin(int n){
	if (n==0) return; // Условие выхода из рекурсии
	int a = n%2;
	DecToBin(n/2);
	printf("%d", a);
}
//Вариант 2. Функция которая возвращает число
long DecToBin2(int n){	
	if (n==0) return 0;
	return n%2 + 10*DecToBin2(n/2);
 }


//Задание №2. Реализовать функцию возведения числа [a] в степень [b]:
//-Рекурсивно.
 int toDegree(int a, int b){
 	if (b==1) return a;
 	return a*toDegree(a, b-1);
 }


//-Рекурсивно, используя свойство чётности степени (то есть, если степень, в которую нужно возвести число, чётная, 
//основание возводится в квадрат, а показатель делится на два, а если степень нечётная - результат умножается на основание, а показатель уменьшается на единицу)
int toDegree2(int a, int b){
 	if (b==1) return a;
 	if(b%2==0) return toDegree2(a*a, b/2);
 	else return a*toDegree2(a, b-1);
 }


// 3. Задание №3. Реализовать нахождение количества маршрутов шахматного короля с препятствиями (где единица - это наличие препятствия, а ноль - свободная для хода клетка)

//S(m, n) = S(m-1, n) + S(m, n-1)
//S(m,n) = 1; если одна из координат равана 0, или есть одно препятствие
// S(m,n) = 0 если клетка начальная или сверху и слева есть припятствие

#define sizeX 5
#define sizeY 5
int board[sizeX][sizeY];

//очистка доски
void annull(){
	for (int y = 0; y < sizeY; ++y){
		for (int x = 0; x < sizeX; ++x){
			board[x][y] = 0;
		}
	}
}

//Вывод доски
void printBoard(){
	printf("***Desck***\n");
	for (int y = 0; y < sizeY; ++y){
		for (int x = 0; x < sizeX; ++x){
			printf("%3d", board[x][y]);
		}
		printf("\n\n");
	}
	printf("***End of deck***\n\n");
}



int routes (int x, int y){
	if (board[sizeX][sizeY] != 0 || board[0][0] != 0) return 0; // Если начало и конец препятствие то путей точно нету
	
	if (board[x][y] != 0) return 0;								// точка где препятствие - не дает путей
	
	if (((x == 0) && (board[0][1] == 0)&& y==1)){				// условия выхода из начальной точки если ячайки [1][0] и [0][1] свободны то вернем по 1 (Рекурентное выражение)
		return 1;
	}
	if (((y == 0) && (board[1][0] == 0) && x==1)){
		return 1;
	}

	if (((x == 0) && (board[0][y] == 0))){						// проверки выхода за границы. Если идем вдоль верха или левой стороны, то суммируем возможные пути. 
		return routes(x, y-1);
	} 
	if ((y == 0) && (board[x][0] == 0)){
		return routes(x-1, y);
	}
	else if (x==0 && y ==0 ) return 0;
	else return routes(x, y-1) + routes(x-1, y);				// стандартный подсчет путей для точки без особых условий, указанных выше
}



int main(int argc, char const *argv[])
{
	//Задание №1. Проверка в main.
	printf("\n ***Dec number to binary number*** \n \n");
	int n;
	printf("Enter Dec number: ");
	scanf("%d", &n);
	//Вариант 1.
	printf("Fist Function - You`s number in binary is ");
	DecToBin(n);
	printf("\n");
	//Вариант 2.
	printf("Second Function - You`s number in binary is %d\n", DecToBin2(n));

	//Задание №2
	printf("\n ***Exponentiation*** \n");
	int a, b;
	printf("\nInsert the number: ");
	scanf("%d", &a);
	printf("Enter degree: ");
	scanf("%d", &b);

	//-Рекурсивно.
	printf("I. The %d in degree %d is %d\n", a, b, toDegree(a,b));
	//-Рекурсивно, используя свойство чётности степени 
	printf("II. The %d in degree %d is %d\n", a, b, toDegree2(a,b));

	//Задание №3
	printf("\n ***King Ways*** \n \n");

	annull();			//очистим доску	

	board[2][2] = 1;	// Задаем препятствия на доске - любое число отличное от 0
	board[3][0] = 1;

	printBoard();		// отрисовываем доску с препядсвием
	printf("***Ways***\n");
	for (int y = 0; y < sizeY; ++y){
		for (int x = 0; x < sizeX; ++x){
			printf("%3d",routes(x,y));
		}
		printf("\n\n");
	}


	return 0;
}