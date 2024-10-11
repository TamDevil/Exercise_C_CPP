#include <stdio.h>
#include <stdlib.h>

void binarySearch(int *arr, int l, int r, int x){
    while (l <= r)
    {
        int mid = l + (r - l)/2;
        if (arr[mid] == x)
        {
            printf("index cua gia tri can tim la %d\n", mid);
            return;
        }else if(arr[mid] > x)
        {
            r = mid - 1;
        }else
        l = mid + 1;
        
    }
    printf("Khong tim thay ket qua\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

bubblesort(int *arr, int size){
    for (int i = 0; i < size -1; i++)
    {
        for (int j = 0; j < size -i -1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
            
        }
        
    }
    
}


int main(int argc, char const *argv[])
{
   int arr[] = {2,31,63,1,2,7,2,56};
    bubblesort(arr,8);
    for (int i = 0; i < 8; i++)
    {
        
    printf("%d\n", arr[i]);
    }
    binarySearch(&arr,0,8,2);
    return 0;
}
