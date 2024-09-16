#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#define INF 10e9+1
void swap(int* a,int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int main(){
    /*int n;scanf("%d",&n);
    int size = 0,arr[1000003];
    while(n--){
        int key;
        scanf("%d",&key);
        size++;
        int i = size;
        arr[i] = key;
        while(i>1 && arr[i/2]<arr[i]){
            swap(&arr[i/2],&arr[i]);
            i = i/2;
        }
    }
    for(int i=1;i<=size;i++)    printf("%d ",arr[i]);*/
    for(int i=1;i<=1000;i++){
        if((9*i-1)%8==0 && (9*i+1)%7==0){
            printf("%d",i);
            break;
        }
    }
}