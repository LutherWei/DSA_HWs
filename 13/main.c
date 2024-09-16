#include "stdio.h"
#include "stdlib.h"

int count = 0, arr[1030],B,N;

void swap(int* a,int* b){
    int t = *a;
    *a = *b;
    *b = t;
    count++;
    if(count==B){
        printf("The array is ");
        for(int i=1;i<=N;i++){
            printf("%d ",arr[i]);
        }
        printf("after %d swaps.",B);
    }
}

int P(int l,int r){
    int pivot = arr[l];
    int i = l+1, j = r;
    while(i<j){
        while(i<=r && arr[i]<=pivot)    i++;
        while(j>=l && arr[j]>pivot) j--;
        if(i>=j)    break;
        swap(&arr[i],&arr[j]);
    }
    if(l<j && arr[l]>arr[j])    swap(&arr[l],&arr[j]);
    return j;
}

void QS(int l,int r){
    if(l<r){
        int m = P(l,r);
        QS(l,m-1);
        QS(m+1,r);
    }
}

int main(){
    scanf("%d%d",&N,&B);
    for(int i=1;i<=N;i++){
        scanf("%d",&arr[i]);
    }
    QS(1,N);
    if(count<B){
        printf("The array is ");
        for(int i=1;i<=N;i++){
            printf("%d ",arr[i]);
        }
        printf("after %d swaps.",count);
    }
    return 0;
}