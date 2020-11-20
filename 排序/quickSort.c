#include<stdio.h>

void quickSort(int a[], int left, int right)
{
    if(left >= right)
    {
        return;
    }
    a[0] = a[left];
    int low = left;
    int high = right;
    while(low < high)
    {
        while(low < high && a[high] > a[0])
        {
            high--;
        }
        if(low < high)
        {
            a[low] = a[high];
        }
        while(low < high && a[low] < a[0])
        {
            low++;
        }
        if(low < high)
        {
            a[high] = a[low];
        }
    }
    a[low] = a[0];
    
    quickSort(a,left,low-1);
    quickSort(a,low+1,right);
}

int main(){
    int a[21] = {0, 20,18,16,14,12,10,8,6,4,2,1,3,5,7,9,11,13,15,17,19};
    quickSort(a, 1, 20);
    for(int i = 1;i<=20;i++){
        printf("%d ",a[i]);
    }
}