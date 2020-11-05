/*
Алгоритмы и структуры на С. Интерактивный курс 2020/04/24
Урок №8. Деревья
HW8.c
Created by Zastupnevich Aleksey
Sublime Text + GCC (WinGW)
2020-11-04
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1 == 1
#define false 1 != 1
typedef int boolean;

const int size = 1000;
const int repit = 50;

typedef struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
} TreeNode;

TreeNode* treeInsert(TreeNode *t, int data);
void printTree(TreeNode *root);
void printNode(TreeNode* node);

/* Задание №1. 1. Написать функцию проверяющую является ли переданное в неё бинарное дерево сбалансированным 
и написать программу, которая: создаст [50] деревьев по [10000] узлов и заполнит узлы случайными целочисленными значениями; 
рассчитает, какой процент из созданных деревьев является сбалансированными.*/


// Получение максимальной "глубины" левой и правой стороны "дерева"
int countDeep(TreeNode *t){
	if (t == NULL) {
		return 0;
	}
	if(t->left == NULL && t->right == NULL) {
		return 1;
	}

	int left = countDeep(t->left);
	int right = countDeep(t->right);
	return 1 + (left > right ? left : right);
}

//Проверка сбалансированое ли дерево или нет
boolean isBalans(TreeNode *tree){
	return abs(countDeep(tree->left) - countDeep(tree->right)) <= 1;
}

//Заполнение дерева случайными числами
void fillTree(TreeNode *tree){
	for (int i = 0; i < size; ++i){
		treeInsert(tree, rand()%1000);
	}
}


// Задание №2. Написать рекурсивную функцию бинарного поиска в дереве хранящемся в узлах, а не в массиве.
 
TreeNode* TreeSearch(TreeNode* tree, int searchData){
	//если значение не найдено и мы опустились до самого "низа" вернем NULL
	if (tree == NULL || tree->key == searchData){
		return tree;
	}
	if (tree->key > searchData){
		return TreeSearch(tree->left, searchData);
	} else {
		return TreeSearch(tree->right, searchData);
	}
}

int main(int argc, char const *argv[])
{
	//Задание №1. Проверка в main
	int procent = 0;
	for (int i = 0; i < repit; ++i){
		TreeNode *tree = (TreeNode*) malloc(sizeof(TreeNode));
		tree = NULL;
		tree = treeInsert(tree, rand()%1000);
		fillTree(tree);
		if (isBalans(tree)){
			procent +=1; 
		}
	}
	printf("%d %% \n", procent*100/repit);

	// Задание №2. Проверка в main
	TreeNode *searchCheck = (TreeNode*) malloc(sizeof(TreeNode));
		searchCheck = NULL;
		searchCheck = treeInsert(searchCheck, 6);
		treeInsert(searchCheck, 2);
		treeInsert(searchCheck, 4);
		treeInsert(searchCheck, 3);
		treeInsert(searchCheck, 6);
		treeInsert(searchCheck, 9);
		treeInsert(searchCheck, 15);
		treeInsert(searchCheck, 11);

		//printTree(searchCheck);
		TreeNode *search = NULL;
		search = TreeSearch(searchCheck, 9);
		printNode(search);
		search = TreeSearch(searchCheck, 16);
		printNode(search);

	return 0;
}


// Реалзиация вспомогательных функций:
void printNode(TreeNode* node){
	if (node != NULL){
		printf("%d\n", node->key);
	} else {
		printf("Nothing\n");
	}
}

TreeNode* treeInsert(TreeNode *t, int data) {
    TreeNode *newNode;
    newNode = (TreeNode*) malloc(sizeof (TreeNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;

    TreeNode *current = t;
    TreeNode *parent = t;

    if (t == NULL) {
        t = newNode;
    } else {
        while(current->key != data){
            parent = current;
            if (current->key > data)
            {
                current = current->left;
                if(current == NULL){
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL)
                {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printTree(TreeNode *root) {
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right){
            printf("(");
            if (root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}
