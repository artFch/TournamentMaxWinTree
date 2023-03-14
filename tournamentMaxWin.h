#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct TournamentTree {
    int key; // ключ
    struct TournamentTree* right; // указатель на правый дочерний узел
    struct TournamentTree* left; // указатель на левый дочерний узел
    int depth; // глубина узла
} tTree;

tTree* Create(int count, int* array); // создает дерево
tTree* InitNode(int depth); // создает узел с ключом -2147483648 (int -inf)
void InitDFS(tTree* node, int tree_depth, int* array, int* i, int count); // шагает в глубину и заполняет листья значениями из массива
int Ceil(int n); // возвращает округленную глубину дерева
void DeleteRoundWinner(tTree* node, tTree* parent); // определяет нового победителя, удаляя прежнего из дерева
double period(); // для замера времени алгоритма
void PrintLeaves(tTree* root); // печатает листья дерева