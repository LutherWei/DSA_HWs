#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#define int long long

int char_to_int(char c){
    if(c<='Z' && c>='A')    return (int)c-65;
    return (int)c-71;
}

signed main(){
    int k,n,m,d;
    scanf("%lld%lld%lld%lld",&k,&n,&m,&d);
    char T[k+5][n+10],P[k+5][m+10];
    for(int i=0;i<k;i++)    scanf("%s",T[i]);
    for(int i=0;i<k;i++)    scanf("%s",P[i]);
    int T_[n+10],P_[m+10];
    for(int i=0;i<=n;i++)   T_[i] = 0;
    for(int i=0;i<=m;i++)   P_[i] = 0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            T_[i] = ((T_[i]*52)%d+char_to_int(T[j][i-1])%d)%d;

        }
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<k;j++){
            P_[i] = ((P_[i]*52)%d+char_to_int(P[j][i-1])%d)%d;
        }
    }
    for(int i=1;i<=n;i++)    printf("%lld ",T_[i]);
    printf("\n");
    for(int i=1;i<=m;i++)    printf("%lld ",P_[i]);
    printf("\n");
    int pi[m+10],K = 0;
    pi[1] = 0;
    for(int i = 2;i<=m;i++){
        while(K>0 && P_[K+1]!=P_[i])   K = pi[K];
        if(P_[K+1]==P_[i])   K++;
        pi[i] = K;
    }

    /*for(int i=1;i<=m;i++)   printf("%lld ",pi[i]);
    printf("\n");*/
    
    int q = 0;K = 0;
    int hits[n+10],fakehits[n+10],ind_h = 0,ind_f = 0;
    for(int i=1;i<=n;i++){
        while(q<n && q>0 && P_[q+1]!=T_[i])   q=pi[q];
        if(q<n&&P_[q+1]==T_[i])   q++;
        if(q==m){
            q = pi[q];
            int shift = i-m;
            bool fla = 0;
            for(int j = 0;j<0+m;j++){
                for(int l = 0;l<k;l++){
                    if(T[l][j+shift]!=P[l][j]){
                        fla=1;
                        break;
                    }
                }
                if(fla==1)  break;
            }
            if(fla==1){
                fakehits[ind_f] = shift;
                ind_f++;
            }
            hits[ind_h] = shift;
            ind_h++;
        }
    }
    if(ind_h==0)    printf("-1\n");
    else{
        for(int i=0;i<ind_h;i++){
            printf("%lld ",hits[i]);
        }
        printf("\n");
    }

    if(ind_f==0)    printf("-1\n");
    else{
        for(int i=0;i<ind_f;i++){
            printf("%lld ",fakehits[i]);
        }
        printf("\n");
    }
    return 0;
}
