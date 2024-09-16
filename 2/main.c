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
    int sizes[100001] = {0};
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
        int t;scanf("%d",&t);
        if(t==1){
            int group,ID;
            scanf("%d%d",&group,&ID);
            node* tmp = decks_t[group]->pre;
            node* cur = (node*)malloc(sizeof(node));
            cur->id = ID;
            tmp->next = cur;
            cur->next = decks_t[group];
            decks_t[group]->pre = cur;
            cur->pre = tmp;
            sizes[group]++;
        }
        else if(t==2){
            int group;
            scanf("%d",&group);
            node* target = decks_t[group]->pre;
            target->pre->next = decks_t[group];
            decks_t[group]->pre = target->pre;
            sizes[group]--;
        }
        else if(t==3){
            int s,d;
            scanf("%d%d",&s,&d);
            if(sizes[s]>0){
                node* head_s = decks_h[s]->next;
                node* tail_s = decks_t[s]->pre;
                node* head_d = decks_h[d]->next;
                node* tail_d = decks_t[d]->pre;

                tail_s->next = decks_t[d];
                decks_t[s]->pre = decks_h[s];
                decks_t[d]->pre = tail_s;
                decks_h[s]->next = decks_t[s];
                tail_d->next = head_s;
                head_s->pre = tail_d;

            }
            sizes[d] += sizes[s];
            sizes[s] = 0;
        }
        else if(t==4){
            int s,d;
            scanf("%d%d",&s,&d);
            int sum = sizes[s]+sizes[d];
            while(sizes[s]>0 && sizes[d]>0){
                node* Tar = decks_t[s]->pre;
                decks_t[s]->pre = Tar->pre;
                decks_t[s]->pre ->next = decks_t[s];
                Tar->pre = tmp_h;
                tmp_h->next->pre = Tar;
                Tar->next = tmp_h->next;
                tmp_h->next = Tar;
                Tar->next->pre = Tar;
                sizes[s]--;

                node* tar = decks_t[d]->pre;
                decks_t[d]->pre = tar->pre;
                decks_t[d]->pre ->next = decks_t[d];
                tar->pre = tmp_h;
                tmp_h->next->pre = tar;
                tar->next = tmp_h->next;
                tmp_h->next = tar;
                tar->next->pre = tar;
                sizes[d]--;
            
            }
            int deck_num = -1;
            if(sizes[s]>0)  deck_num = s;
            else if(sizes[d]>0) deck_num = d;
            if(deck_num!=-1){
                decks_t[deck_num]->pre->next = tmp_h->next;
                tmp_h->next = decks_h[deck_num]->next;
                decks_t[deck_num]->pre->next ->pre = decks_t[deck_num]->pre;
                decks_h[deck_num]->next->pre = tmp_h;
                decks_h[deck_num]->next = decks_t[deck_num];
                decks_t[deck_num]->pre = decks_h[deck_num];
                sizes[deck_num] = 0;
            }
            if(tmp_t->pre!=tmp_h){

                decks_h[d]->next = tmp_h->next;
                decks_h[d]->next->pre = decks_h[d];
                tmp_h->next = tmp_t;
                tmp_t->pre->next = decks_t[d];
                decks_t[d]->pre = tmp_t->pre;
                tmp_t->pre = tmp_h;
            }
            sizes[d] = sum;
            sizes[s] = 0;
        }
    }
    for(int i=1;i<=N;i++){
        printf("%d ",sizes[i]);
        node* curr = decks_t[i];
        while(curr->pre!=decks_h[i]){
            curr = curr->pre;
            printf("%d ",curr->id);
        }
        printf("\n");
    }
    return 0;
}