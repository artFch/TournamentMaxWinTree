#include "tournamentMaxWin.h"

tTree* Create(int count, int* array) // создаем дерево, вызов рекурсивной функции
{
    int tree_depth = Ceil(count); // глубина дерева, которое получится
    printf("tree_depth = %d\n", tree_depth);
    tTree* root = InitNode(0); // создали корень
    int i = 0; // присвоили уровню 0
    if (count == 0) {
        return root;
    }
    InitDFS(root, tree_depth, array, &i, count); // входим в рекурсию, строим дерево и заполняем его
    return root;
}

tTree* InitNode(int depth) // инициализирует лист
{
    tTree* node = malloc(sizeof(tTree));
    node->left = NULL;
    node->right = NULL;
    node->key = -2147483648;
    node->depth = depth;
    return node;
}

void InitDFS(tTree* node, int tree_depth, int* array, int* i, int count) // рекурсивное создание узлов и их заполнение весами из массива участников
{
    if (tree_depth != node->depth) { // пока не достигли листьев
        node->left = InitNode(node->depth + 1);
        node->right = InitNode(node->depth + 1);
        InitDFS(node->left, tree_depth, array, i, count); // рекурсия левого
        if (*i == count) { // если значения закончились ,а листья нет
            node->key = node->left->key;
            free(node->right);
            node->right = NULL;
            return; 
        }
        InitDFS(node->right, tree_depth, array, i, count); // рекурсия правого
        if (node->left->key > node->right->key) {
            node->key = node->left->key;
        } else {
            node->key = node->right->key;
        }
    }
    if (*i < count) { // заполняем лист
        if (tree_depth == node->depth) {
            node->key = array[*i];
            *i = *i + 1;
        }
    }
}

void DeleteRoundWinner(tTree* node, tTree* parent) // удаление текущего победителя и определение нового
{
    if (node->left != NULL && node->key == node->left->key) {
        node->key = -2147483648;
        DeleteRoundWinner(node->left, node);
    }

    if (node->right != NULL && node->key == node->right->key) {
        node->key = -2147483648;
        DeleteRoundWinner(node->right, node);
    }

    if (node->left == NULL && node->right == NULL) { // дошли до нужного листа
        node->key = -2147483648;
        if (parent->left != NULL && parent->left->key == -2147483648) { // удаляем его если он слева от родителя
            free(parent->left);
            parent->left = NULL;
        } else if (parent->right != NULL && parent->right->key == -2147483648) { // удаляем его если он справа от родителя
            free(parent->right);
            parent->right = NULL;
        }
        return;
    }
    /* В зависимости от ситуации определяется новый победитель */
    if (node->right == NULL) {
        node->key = node->left->key;
        return;
    } else if (node->left == NULL) {
        node->key = node->right->key;
        return;
    }

    if (node->right->key > node->left->key) {
        node->key = node->right->key;
    } else if (node->left->key > node->right->key) {
        node->key = node->left->key;
    }
}

int Ceil(int n) // возвращает глубину дерева
{
    return ceil(log2f(n));
}

double period() // для проверки времени работы алгоритма
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void PrintLeaves(tTree* node) // рекурсивно в глубину обходим дерево и печатаем значения в листьях
{
    if (node->left == NULL && node->right == NULL) {
        printf("%d ", node->key);
        return;
    }
    if (node->left != NULL) {
        PrintLeaves(node->left);
    }

    if (node->right != NULL) {
        PrintLeaves(node->right);
    }
}