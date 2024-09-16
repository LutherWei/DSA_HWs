#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"
#define int long long 


struct node{
    long long value;
    struct node *next;
    struct node *pre;
    struct node *abo;
    struct node *bel;
};

typedef struct node Node;
Node *heads[65],*tails[65];
int last_lev = 0;
void init_node(int num,Node* New){
    New->abo = NULL;
    New->bel = NULL;
    New->next = NULL;
    New->pre = NULL;
    New->value = num;
}
void init(){
    for(int i=0;i<65;i++){
        heads[i] = (Node*)malloc(sizeof(Node));
        tails[i] = (Node*)malloc(sizeof(Node));
        heads[i]->pre = NULL;
        tails[i]->pre = heads[i];
        heads[i]->next = tails[i];
        tails[i]->next = NULL;
        heads[i]->value = -1;
        tails[i]->value = -1;
    }
    heads[0]->bel = NULL;
    tails[0]->bel = NULL;
    heads[0]->abo = heads[1];
    tails[0]->abo = heads[1];
    for(int i=1;i<64;i++){
        heads[i]->bel = heads[i-1];
        tails[i]->bel = tails[i-1];
        heads[i]->abo = heads[i+1];
        tails[i]->abo = heads[i+1];
    }
    heads[64]->abo = NULL;
    tails[64]->abo = NULL;
    heads[64]->bel = heads[63];
    tails[64]->bel = tails[63];
}
bool Flip(int k,int i){
    int t,d;
    d = pow(2,i-1);
    t = k/d;
    return t%2;
}
Node *fast_g(int data,Node *record[3002]){
    Node* tmp = heads[last_lev];
    int lev = last_lev;
    while(tmp->bel != NULL){
        while(tmp->next != tails[lev] && data<=(tmp->next->value))
            tmp = tmp->next;
        record[lev] = tmp;
        lev--;
        tmp = tmp->bel;
    }
    //printf("%d\n",lev);
    while(tmp->next!=tails[0] && data<=(tmp->next->value))
        tmp = tmp->next;
    return tmp;
}

signed main(){
    init();
    int M;scanf("%lld",&M);
    
    for(int j=0;j<M;j++){
        int t; scanf("%lld",&t);
        
        if(t==1){
            Node* Tmp = heads[0];
            int data;
            scanf("%lld",&data);
            
            bool printed = 0;
            while(Tmp->next!=tails[0] && Tmp->next->value>=data){
                Tmp = Tmp->next;
                printed = 1;
                printf("%lld ",(Tmp->value));
                
            }
            if(!printed)    printf("-1");
            printf("\n");
        }
        else if(t==2){
            Node* tmp = heads[last_lev];
            int data;scanf("%lld",&data);
            
            bool printed = 0;
            int lev = last_lev;
            while(tmp->bel!= NULL){
                while(tmp->next != tails[lev] && data<=(tmp->next->value)){
                    if(tmp!=heads[lev]){
                        printed = 1;
                        printf("%lld ",tmp->value);
                        
                    }
                    tmp = tmp->next;
                }
                if(tmp!=heads[lev]){
                    printed = 1;
                    printf("%lld ",tmp->value);
                }
                lev--;
                tmp = tmp->bel;
            }
            //printf("%d\n",lev);
            while(tmp->next!=tails[0] && data<=(tmp->next->value)){
                if(tmp!=heads[0]){
                    printed = 1;
                    printf("%lld ",tmp->value);
                }
                tmp = tmp->next;
            }
            printf("%lld ",tmp->value);
            //if(!printed)    printf("-1");
            printf("\n");
        }
        else if(t==3){
            long long num;scanf("%lld",&num);
            Node* New = (Node*)malloc(sizeof(Node));
            init_node(num,New);
            Node* record[3002];
            for(int i=0;i<3002;i++) record[i] = heads[i];
            Node* target = fast_g(num,record);
            Node* tmp = target->next;
            target->next = New;
            New->pre = target;
            tmp->pre = New;
            New->next = tmp;
            int layer = 1;
            Node* curr = New;
            while(Flip(num,layer)){
                Node* uppers = (Node*)malloc(sizeof(Node));
                init_node(New->value,uppers);
                Node* Tmp = record[layer]->next;
                record[layer]->next = uppers;
                uppers->pre = record[layer];
                Tmp->pre = uppers;
                uppers->next = Tmp;
                curr->abo = uppers;
                uppers->bel = curr;

                curr = curr->abo;
                last_lev = last_lev>layer?last_lev:layer;
                layer++;
            }
        }
        
        else if(t==4){//remove the layer without node
            Node* tmp = heads[last_lev];
            int data;scanf("%lld",&data);
            
            int lay = last_lev;
            while(tmp->bel != NULL){
                while(tmp->next != tails[lay] && data<=(tmp->next->value))
                    tmp = tmp->next;
                    if(tmp->value==data){
                        tmp->pre->next = tmp->next;
                        tmp->next->pre = tmp->pre;
                        if(tmp->pre==heads[last_lev] && tmp->next==tails[last_lev]) last_lev--;
                    }
                tmp = tmp->bel;
                lay--;
            }
            //printf("%d\n",lev);
            while(tmp->next!=tails[0] && data<=(tmp->next->value))
                tmp = tmp->next;
            if(tmp->value==data){
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
            }
        }
    }
    return 0;
}