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
    if(ind_tmp<len){
        tmp[ind_tmp] = arr[ind_arr];
        //tmp[ind_tmp] = ind_arr;
        //printf("%d ",tmp[ind_tmp]);
        check[ind_arr] = 1;
        if(sta==1){
            int rec_1[21], ind_1 = 0;
            for(int i=ind_arr+1;i<len;i++){
                if(check[i]==0 && arr[ind_arr]<arr[i] ){
                    //printf("kkkk");
                    if(ind_1>0 && arr[i]==rec_1[ind_1-1]) continue;
                    rec_1[ind_1] = arr[i];
                    ind_1++;
                    Dfs(-1,arr,tmp,storage,check,i,ind_tmp+1,len,size);
                }
            }
        }
        else{
            int rec__1[21], ind__1 = 0;
            for(int i=0;i<ind_arr;i++){
                if(check[i]==0 && arr[ind_arr]>arr[i] ){
                    //printf("hi");
                    if(ind__1>0 && arr[i]==rec__1[ind__1-1])  continue;
                    rec__1[ind__1] = arr[i];
                    ind__1++;
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
            if(i>0 && arr[i]==arr[i-1]) continue;
            Dfs(-1,arr,tmp,storage,check,i,0,n,&size);
            Dfs(1,arr,tmp,storage,check,i,0,n,&size);
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