#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#define int long long
#define SIZE 5000006

signed main(){
    char S[SIZE],C[SIZE];
    int cnt[SIZE] = {0},counter[SIZE] = {0};
    scanf("%s%s",S,C);
    int pi[SIZE],k = -1,m = strlen(C);
    pi[0] = -1;
    int scores[SIZE];
    scores[0] = 1;
    for(int q = 1;q<m;q++){
        scores[q] = 1;
        while(k>=0 && C[k+1]!=C[q]) k = pi[k];
        if(C[k+1]==C[q])    k++;
        pi[q] = k;
        if(pi[q]>=0)    scores[q] += scores[pi[q]];
    }
    int size_s = strlen(S);
    int q = -1,starter = 0,matcher[SIZE] = {0};
    for(int i=0;i<size_s;i++){
        while(q>=0 && C[q+1]!=S[i]) q = pi[q];
        if(C[q+1]==S[i]){
            matcher[q+1]++;
            q++;
        }
        if(q==m-1){
            q = pi[q];
        }
    }
    /*for(int i=0;i<m;i++)    printf("%d ",matcher[i]);
    printf("\n");*/
    for(int i=m-1;i>=0;i--) if(pi[i]>=0) matcher[pi[i]] += matcher[i];
    for(int i=0;i<m;i++)   printf("%lld\n",matcher[i]*scores[i]);
}