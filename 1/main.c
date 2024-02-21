#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define ll long long

int cmp(const void *A, const void *B){
    int a = *(int*)A, b = *(int*)B;
    if((a)>(b))   return 1;
    if((a)<(b))   return -1;
    else    return 0;
}
void Dfs(int sta, int arr[21],int tmp[21], int storage[20001][21], bool check[21],int ind_arr,int ind_tmp,int len, int* size){
    
    tmp[ind_tmp] = arr[ind_arr];
    //printf("%d ",tmp[ind_tmp]);
    check[ind_arr] = 1;
    if(sta==1){
        for(int i=ind_arr+1;i<len;i++){
            if(check[i]==0 && arr[ind_arr]<arr[i]){
                //printf("kkkk");
                Dfs(-1,arr,tmp,storage,check,i,ind_tmp+1,len,size);
            }
        }
    }
    else{
        for(int i=0;i<ind_arr;i++){
            if(check[i]==0 && arr[ind_arr]>arr[i]){
                //printf("hi");
                Dfs(1,arr,tmp,storage,check,i,ind_tmp+1,len,size);
            }
        }
    }
    if(ind_tmp==len-1){
        //printf("okok\n");
        for(int i=0;i<len;i++){
            storage[(*size)][i] = tmp[i];
        }
        (*size)++;
    }
    check[ind_arr] = 0;

}
int main(){
    int n,arr[21],storage[20001][21],tmp[21];
    bool check[21] = {0};
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    qsort(arr, n, sizeof(int), cmp);
    if(n==1)    printf("1\n%d",arr[0]);
    else{
        int size = 0;
        for(int i=0;i<n;i++){
            if(arr[i]!=arr[i-1]){
                Dfs(-1,arr,tmp,storage,check,i,0,n,&size);
                Dfs(1,arr,tmp,storage,check,i,0,n,&size);
            }
        }

        printf("%d\n",size);
        for(int i=0;i<size;i++){
            for(int j=0;j<n;j++){
                printf("%d ",storage[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}