#include "tournamentMaxWin.h"

int main()
{
    int array[] = { 844 ,585 ,219 ,238, 87, 310, 737, 295, 512, 325, 466, 651, 921,511, 657, 128, 422, 92 ,790 ,492};
    /* int array[] = {17,4,1,5,3,10,14,6}; */
    /* int k = 10000;
    int array[k];
    for (int i = 0; i < k; i++) {
        array[i] = i + 1;
    }  */
    int count = sizeof(array)/4; // int 4 байта
    printf("capacity = %d\n", count);

    double begin = period();
    tTree* root = Create(count, array);
    double end = period();
    printf("\nTime for adding %d elements: %.6f\n", count, end - begin);
    printf("\n\nИсходный массив: ");
    begin = period();
    /* PrintLeaves(root); */
    end = period();
    printf("\nTime for find leaves %d elements: %.6f\n", count, end - begin);
    /* printf("\nPrintLeaves\n\n"); */
    /* PrintLeaves(root);
    printf("\nroot->key = %d\n", root->key); */

    int sortarray[count];
    begin = period();

    int i = 0;
    /* sortarray[0] = root->key; */
    while (root->key != -2147483648) {
        sortarray[i] = root->key;
        DeleteRoundWinner(root, root);
        i++;
    }
    end = period();
    /* printf("\nPrintLeaves,again\n\n");
    PrintLeaves(root); */
    printf("\nTime for sorting %d elements: %f\n", count, end - begin);
    printf("\nИсходный массив: ");

    for (int i = 0; i < count; i++) {
    printf("%d ", array[i]);
    }
    printf("\nОтсортированыый массив: ");
    for (int i = 0; i < count; i++) {
    printf("%d ", sortarray[i]);
    }
    printf("\nНаибольший элемент: ");
    printf("\nsortarray[0] = %d\n", sortarray[0]); 

    return 0;
}
