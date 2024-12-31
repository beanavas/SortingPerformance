
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//problems, same number

#define arr_length 6
#define THRESHOLD 25

void fillArray(int arr[], int n);
void selectionSort(int arr[], int n);
long timediff(clock_t t1, clock_t t2);
void bubbleSort(int arr[], int n);
void insertSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void mergeInsertionSort(int arr[], int l, int r, int n);
void quickSort(int arr[], int low, int high);

int main(){

    srand(time(0));

    int size[arr_length] = {10000, 20000, 30000, 40000, 50000, 100000};
    int *originalArr, *sortedArr;
    
    clock_t start, end;
    long elapsed;

    //runs for each array 
    for(int i = 0; i < 6; i++){

        originalArr = (int *)malloc(sizeof(int)*size[i]);
        sortedArr = (int *)malloc(sizeof(int)*size[i]);

        fillArray(originalArr, size[i]);

        //quick sort
        memcpy(sortedArr, originalArr, size[i]*sizeof(int));
        start = clock();
        quickSort(sortedArr, 0, size[i]-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("Quick Sort Sort took %ld ms for %d values\n", elapsed, size[i]);

        //selection sort 
        memcpy(sortedArr, originalArr, size[i]*sizeof(int));
        start = clock();
        selectionSort(sortedArr, size[i]);
        end = clock();
        elapsed = timediff(start, end);
        printf("Selection Sort took %ld ms for %d values\n", elapsed, size[i]);

        //bubble sort
        memcpy(sortedArr, originalArr, size[i]*sizeof(int));
        start = clock();
        bubbleSort(sortedArr, size[i]);
        end = clock();
        elapsed = timediff(start, end);
        printf("Bubble Sort took %ld ms for %d values\n", elapsed, size[i]); 

        //merge Sort
        memcpy(sortedArr, originalArr, size[i]*sizeof(int));
        start = clock();
        mergeSort(sortedArr, 0, size[i]-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("Merge Sort took %ld ms for %d values\n", elapsed, size[i]);

        //merge insertion Sort 
        memcpy(sortedArr, originalArr, size[i]*sizeof(int));
        start = clock();
        mergeInsertionSort(sortedArr, 0, size[i]-1, size[i]);
        end = clock();
        elapsed = timediff(start, end);
        printf("Merge Insertion Sort took %ld ms for %d values\n", elapsed, size[i]);

        //insert sort
        memcpy(sortedArr, originalArr, size[i]*sizeof(int));
        start = clock();
        insertSort(sortedArr, size[i]);
        end = clock();
        elapsed = timediff(start, end);
        printf("Insert sort took %ld ms for %d values\n", elapsed, size[i]);
    }

free(originalArr);
free(sortedArr);

}

void fillArray(int arr[], int n){

     

    for(int i = 0; i < n; i++){

        arr[i] = rand() % 10000 + 1;

        

    }
}

long timediff(clock_t t1, clock_t t2) {

    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;

}

// selection sort //
void selectionSort(int arr[], int n){

    int min_index, temp;


    for(int i = 0; i < n-1; i++){

        min_index = i;

        for(int j = i+1; j < n; j++){

            if(arr[j] < arr[min_index]){
                min_index = j;
            }

        }

        temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;

    }

}

// bubble sort //
void bubbleSort(int arr[], int n){

    for(int i = 0; i < n-1; i++){

        for(int j = 0; j < n-i+1; j++){

            if(arr[j] > arr[j+1]){
                
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

            }
        }
    }
}

// insert sort //
void insertSort(int arr[], int n){


    for(int i = 1; i < n; i++){

        int temp = arr[i];
        int j = i-1;

        while(j >= 0 && arr[j] > temp){

            arr[j+1] = arr[j];
            j--;

        }

    arr[j+1] = temp;


    }
}

// merge sort //

void mergeSort(int arr[], int l, int r){

    if(l<r){

        int mid = (l+r)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);
        merge(arr,l,mid,r);

    }
}

void merge(int arr[], int l, int m, int r){

    int i, j, k;

    int n1 = m-l+1;
    int n2 = r-m;

    int *L = (int *)malloc(sizeof(int)*n1);
    int *R = (int *)malloc(sizeof(int)*n2);

    for(i = 0; i < n1; i++){

        L[i] = arr[l+i];

    }
    for(j = 0; j < n2; j++){

        R[j] = arr[m+1+j];

    }

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2){

        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
            k++;
        }
        else {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

free(L);
free(R);

}

// merge insertion sort //
void mergeInsertionSort(int arr[], int l, int r, int n) {
    
    if((r-l)<THRESHOLD){

    insertSort(arr+l, r-l+1);

}else {
    if(l < r){
        int m = (l+r)/2;
        mergeInsertionSort(arr,l,m,n);
        mergeInsertionSort(arr,m+1,r,n);
        merge(arr,l,m,r);
    }
}}

// quick sort //

void quickSort(int arr[], int low, int high){

    if(low < high){

        int pivot = arr[high];
        int i = low-1;

        for(int j = low; j < high; j++){

            if(arr[j] < pivot){

                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;

            }
        }
        
        int temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;

        //int x = i + 1;

        quickSort(arr, low, i);
        quickSort(arr, i+2, high);


    }
}


