#include "stdio.h"
#include "stdlib.h"
int getMin(int arr[],int l,int r){
    int m=l;
    for(int i=l+1;i<r;i++){
        if(arr[m]>arr[i])
            m = i;
    }
    return m;
}
void swap(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
int main(){
    int len,B,count = 0;
    scanf("%d%d",&len,&B);
    int arr[1027];
    for(int i=0;i<len;i++)  scanf("%d",&arr[i]);
    for(int i=0;i<len;i++){
        int m = getMin(arr,i,len);
        if(i != m && count<B){
            swap(&arr[i],&arr[m]);
            count++;
        }
    }
    B = B > count?count:B;
    printf("The array is ");
    for(int i=0;i<len;i++)  printf("%d ",arr[i]);
    printf("after %d swaps.",B);
    return 0;
}