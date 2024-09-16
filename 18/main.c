#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Node{
    struct Node* p;
    int rank,id;
}node;
node* nodes[1000002];
node* find_set(node *x){
    if(x != x->p)
        x->p = find_set(x->p);
    return x->p;
}
int main(){
    int N,M;
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++){
        nodes[i] = (node*)malloc(sizeof(node));
        nodes[i]->p = nodes[i];
        nodes[i]->rank = 0;
        nodes[i]->id = i;
    }
    char buffer;
    char ope;
    while(M--){
        scanf("%c%c",&buffer,&ope);
        if(ope=='P'){
            int n;scanf("%d",&n);
            node* tmp = nodes[n];
            while(tmp->p!=tmp){
                printf("%d ",tmp->id);
                tmp = tmp->p;
            }
            printf("%d\n",tmp->id);
        }
        else if(ope=='F'){
            int n;scanf("%d",&n);
            nodes[n]->p = find_set(nodes[n]->p);
        }
        else if(ope=='U'){
            int x,y;scanf("%d%d",&x,&y);
            node* v = find_set(nodes[x]),*w = find_set(nodes[y]);
            if(v!=w){
                if(v->rank>w->rank) w->p = v;
                else{
                    v->p = w;
                    if(v->rank==w->rank)    (w->rank)++;
                }
            }
        }
    }
}