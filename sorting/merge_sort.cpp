#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void merge(int l, int m, int n, int* arr){

    int a = m-l+1, b = n-m, i = 0, j = 0, k = 0, x = l, y = m+1;
    int c[a+b];

    while(i < a && j < b){
        if(arr[x] <= arr[y]) {
            c[k++] = arr[x++];
            i++;
        }
        else {
            c[k++] = arr[y++];
            j++;
        }
    }
    while(i < a){
        c[k++] = arr[x++];
        i++;
    }
    while(j < b){
        c[k++] = arr[y++];
        j++;
    }
    for(k = 0; k < a+b; k++)
        arr[l+k] = c[k];
}

void merge_sort(int low, int high, int* arr){

    if(low >= high) return;

    int mid = (low+high)/2;
    merge_sort(low, mid, arr);
    merge_sort(mid+1, high, arr);
    merge(low, mid, high, arr);
}

void print(int N, int *arr){
    for(int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main(){

    int N;
    cin >> N;
    auto arr = new int[N];

    for(int i = 0; i < N; i++)
        cin >> arr[i];

    print(N, arr);
    merge_sort(0, N-1, arr);
    print(N, arr);

    free(arr);
    return 0;
}