#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void swap(int i, int j, int* arr){
    auto temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int low, int high, int* arr){
    int pivot = arr[low], i = low+1, j = high;

    while(i <= j){

        while(i <= high && arr[i] <= pivot)
            i++;

        while(j > low && arr[j] > pivot)
            j--;

        if(i < j)
            swap(i, j, arr);
    }
    swap(j, low, arr);

    return j;
}

void print(int N, int *arr){
    for(int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void quick_sort(int low, int high, int* arr){

    if(low >= high) return;

    auto pivot = partition(low, high, arr);
    quick_sort(low, pivot-1, arr);
    quick_sort(pivot+1, high, arr);
}

int main(){

    int N;
    cin >> N;
    auto arr = new int[N];

    for(int i = 0; i < N; i++)
        cin >> arr[i];

    print(N, arr);
    quick_sort(0, N-1, arr);
    print(N, arr);

    free(arr);
    return 0;
}