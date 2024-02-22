#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct Node{
    struct Node* pre;
    struct Node* next;
    int id;
    
};
typedef struct Node node;

int main(){
    node* decks_h[100001];
    node* decks_t[100001];
    for(int i=0;i<100001;i++){
        decks_h[i] = (node*)malloc(sizeof(node));
        decks_t[i] = (node*)malloc(sizeof(node));
        decks_h[i]->pre = NULL;
        decks_h[i]->next = decks_t[i];
        decks_t[i]->pre = decks_h[i];
        decks_t[i]->next = NULL;
    }
    node *tmp_h, *tmp_t;
    tmp_h = (node*)malloc(sizeof(node));
    tmp_t = (node*)malloc(sizeof(node));
    tmp_h->pre = NULL;
    tmp_h->next = tmp_t;
    tmp_t->pre = tmp_h;
    tmp_t->next = NULL;

    int N,M;
    scanf("%d%d",&N,&M);
    for(int i=0;i<M;i++){
        int t;scanf("%d",t);
        if(t==1){
            int group,ID;
            scanf("%d%d",&group,&ID);
            
        }
        else if(t==2){

        }
        else if(t==3){

        }
        else if(t==4){

        }
    }
    return 0;
}