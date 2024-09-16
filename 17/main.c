#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct vertex{
    int id,d,f,color;//white = 0,gray =1,black = 2
}ver;

typedef struct Node{
    int id;
    char type;
    struct Node *next;
}edge;


int time = 0;
ver vertexes[1003];
edge *edges[1003];

void Dfs(int u){
    time++;
    vertexes[u].d = time;
    vertexes[u].color = 1;
    for(edge *tmp = edges[u]->next;tmp!=NULL;tmp = tmp->next){
        int v = tmp->id;
        if(vertexes[v].color==0){
            tmp->type = 'T';
            Dfs(v);
        }
        else if(vertexes[v].color==1)   tmp->type = 'B';
        else{
            if(vertexes[u].d<vertexes[v].d) tmp->type = 'F';
            else    tmp->type = 'C';
        }
    }
    vertexes[u].color = 2;
    time++;
}

int main(){
    int V;scanf("%d",&V);
    for(int i=1;i<=V;i++){
        vertexes[i].color = 0;
        vertexes[i].id = i;
        edges[i] = (edge*)malloc(sizeof(edge));
        edges[i]->id = i;
        edges[i]->next = NULL;
        int t;scanf("%d",&t);
        edge *tmp = edges[i];
        while(t--){
            edge* new = (edge*)malloc(sizeof(edge));
            scanf("%d",&(new->id));
            new->next = NULL;
            tmp->next = new;
            tmp = new;
        }
    }
    for(int i=1;i<=V;i++){
        if(vertexes[i].color == 0)  Dfs(i);
    }
    for(int i=1;i<=V;i++){
        printf("%d ",i);
        for(edge* tmp = edges[i]->next;tmp !=NULL;tmp = tmp->next){
            printf("%c",tmp->type);
        }
        printf("\n");
    }
}