/*
 *      Proyecto 2 de Sistemas Operativos
 *      quicksort.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

/*http://www.geeksforgeeks.org/quick-sort/*/
/* C implementation QuickSort */
#include "tree.h"
void swap(Data * a, Data * b){
    Data t = *a;
    *a = *b;
    *b = t;
}

int partition (Data * arr, int low, int high){
    Data pivot = arr[high];
    int i = (low - 1);
	int j;
    for (j = low; j <= high- 1; j++){
        if (arr[j].frequency <= pivot.frequency)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Data * arr, int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
