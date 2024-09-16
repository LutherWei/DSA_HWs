#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Node{
    int id, depth,priority,max_child;//the num of children, must call max_child-1 if wanting to call the child with the largest size
    struct Node* parents, *sib;
    //struct Node* chil[20];
    struct Node* chil;
    
} node;

void __init(node* n){
    //n->chil = (node **)malloc( sizeof(node*));
    //for(int i=0;i<20;i++)   n->chil[i] = NULL;
    //n->chil[0] = NULL;
    n->chil = NULL;
    n->depth = 1;
    n->max_child = 0;
    n->parents = NULL;
    n->priority = 0;
    n->sib = NULL;
}


node* HeapUnion(node* H1, node* H2){
    node* H = (node*)malloc(sizeof(node));
    __init(H);
    if(H1==NULL && H2==NULL)    return H;
    node *tmp1 = H1,*tmp2 = H2,*curr = H;
    while(tmp1!=NULL && tmp2!=NULL){
        if(tmp1->depth<=tmp2->depth){
            curr->sib = tmp1;
            tmp1 = tmp1->sib;
        }
        else{
            curr->sib = tmp2;
            tmp2 = tmp2->sib;
        }
        curr = curr->sib;
    }
    if(tmp1==NULL && tmp2!=NULL){
        curr->sib = tmp2;
        //printf("hhu : %d \n",tmp2->id);
    }
    else if(tmp1!=NULL && tmp2==NULL)   curr->sib = tmp1;

    node* prev = NULL, *x = H->sib, *next = x->sib;
    while(next != NULL){
        if(x->depth!=next->depth || (next->sib!=NULL && next->sib->depth==x->depth)){
            prev = x;
            x = next;
        }
        else{
            if(x->priority > next->priority){ //insert next as a child of x, and update degree[x]
                x->sib = next->sib;
                /*if(x->max_child==0) next->sib = NULL;
                else    next->sib = x->chil[x->max_child-1];*/
                if(x->chil==NULL)   next->sib = NULL;
                else    next->sib = x->chil;
                x->chil = next;
                next->parents = x;
                x->max_child++;
                x->depth++;
                //x->chil = (node**)realloc(x->chil,(x->max_child+1)*sizeof(node*));
            }
            else{//x as a child of next, and update degree[next
                if(prev == NULL)
                    H->sib = next;
                else    prev->sib = next;

                /*if(next->max_child==0)  x->sib = NULL;
                else    x->sib = next->chil[next->max_child-1];*/
                if(next->chil==NULL)   x->sib = NULL;
                else    x->sib = next->chil;
                x->parents = next;
                next->chil = x;
                next->max_child++;
                next->depth++;
                x = next;
                //next->chil = (node**)realloc(next->chil,(next->max_child+1)*sizeof(node*));
            }
        }
        next = x->sib;
    }

    return H;
}

int main(){
    int N,M; scanf("%d%d",&N,&M);
    node* printers_H[N+1];//heads of each printer
    int printer_nums[N+1];
    for(int i=1;i<=N;i++){
        printers_H[i] = (node*)malloc(sizeof(node));
        __init(printers_H[i]);
        printer_nums[i] = 0;
    }
    //printf("%lu",sizeof(node*));
    while(M--){
        int t;scanf("%d",&t);
        if(t==1){
            int job_id,pri,printer;
            scanf("%d%d%d",&job_id,&pri,&printer);
            node* job = (node*)malloc(sizeof(node));
            printer_nums[printer]++;
            __init(job);
            job->id = job_id;
            job->priority = pri;
            job->sib = printers_H[printer]->sib;
            printers_H[printer]->sib = job;
            node* tmp = job;
            while(tmp->sib!=NULL && tmp->sib->depth==tmp->depth){
                node* T;
                if(tmp->priority<tmp->sib->priority){
                    T = tmp;
                    tmp = tmp->sib;
                    printers_H[printer]->sib = tmp;
                }
                else{
                    T = tmp->sib;
                    tmp->sib = T->sib;
                }
                /*if(tmp->max_child>0)    T->sib = tmp->chil[(tmp->max_child)-1];
                else    T->sib = NULL;*/
                if(tmp->chil==NULL) T->sib = NULL;
                else    T->sib = tmp->chil;
                T->parents = tmp;
                tmp->chil = T;
                tmp->max_child++;
                tmp->depth++;
                //tmp->chil = (node**)realloc(tmp->chil,(tmp->max_child+1)*sizeof(node*));
            }
            printf("%d jobs waiting on printer %d\n",printer_nums[printer],printer);
        }
        else if(t==2){
            int printer;
            scanf("%d",&printer);
            if(printer_nums[printer]==0)    printf("no documents in queue\n");
            else{
                printer_nums[printer]--;
                node* curr = printers_H[printer], *max = curr;
                while(curr->sib!=NULL){
                    curr = curr->sib;
                    if(curr->priority>max->priority){
                        max = curr;
                    }
                }
                //printf("jjj");
                printf("%d printed\n",max->id);
                //remove
                
                curr = printers_H[printer];
                while(curr->sib!=max){
                    curr = curr->sib;
                    //printf("kkkk");
                }
                curr->sib = max->sib;
                //mind the case curr = printers_H
                //reverse
                
                /*for(int i=0;i<max->max_child;i++){
                    max->chil[i]->sib = max->chil[i+1];
                }*/
                
                //in case there is no children
                if(max->chil!=NULL){
                    max->chil->parents = NULL;
                    node* curr = max->chil->sib;
                    node* tar = max->chil;
                    max->chil->sib = NULL;
                    while(curr!=NULL){
                        node* temp = tar;
                        tar = curr;
                        curr = curr->sib;
                        tar->sib = temp;

                    }
                    printers_H[printer] = HeapUnion(printers_H[printer]->sib,tar);
                }
                free(max);
            }
        }
        else if(t==3){
            int id1,id2;scanf("%d%d",&id1,&id2);
            printer_nums[id2] += printer_nums[id1];
            printer_nums[id1] = 0;
            printf("%d jobs waiting on printer %d after moving\n",printer_nums[id2],id2);
            
            printers_H[id2] = HeapUnion(printers_H[id2]->sib,printers_H[id1]->sib);
            printers_H[id1]->sib = NULL;
        }
    }

    return 0;
}
