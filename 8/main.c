#include "stdio.h"
#include "stdlib.h"

struct node{
    struct node *next;
    int id;
};
typedef struct node Node;

int main(){
    int n;scanf("%d",&n);
    Node *nodes[n+1];
    for(int i=0;i<=n;i++)   nodes[i] = (Node*)malloc(sizeof(Node));
    for(int i=1;i<=n;i++){
        int ID,ind;
        scanf("%d%d",&ID,&ind);
        nodes[i]->id = ID;
        if(ind==0){
            nodes[i]->next = NULL;
            continue;
        }
        nodes[i]->next = nodes[ind];
    }
    Node *hare = nodes[1], *tor = nodes[1];
    while(hare != NULL && hare->next !=NULL ){
        printf("%d ",hare->id);
        hare = hare->next->next;
        tor = tor->next;
        if(hare == tor)
            break;
    }
    if(hare!=NULL)  printf("%d ",hare->id);
    

}