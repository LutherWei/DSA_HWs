#include "stdio.h"
#include "stdlib.h"

int main(){
    int n,b;
    scanf("%d",&n);
    int arr[n+1];
    for(int i=1;i<=n;i++)   scanf("%d",&arr[i]);
    int times = 0;
    for (int m = 1; m<=n;m++){
        int data = arr[m];
        int i = m - 1;
        while (i > 0 && arr[i] > data ){
            times++;
            arr[i + 1] = arr[i];
            i = i - 1;
        }
        arr[i + 1] = data;
    }
    printf("The array is ");
    for(int i=1;i<=n;i++)   printf("%d ",arr[i]);
    //int out = times<b?times:b;
    printf("after %d back-moves.", times);
    return 0;
}