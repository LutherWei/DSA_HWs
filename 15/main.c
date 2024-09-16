#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#define SIZE 100004
#define int long long

typedef struct lists{
    struct lists* next;
    int id;
}nodes;
typedef struct vertex{
    struct vertex* p;
    int id,d,f,color,group;//white=0,gray=1,black=2
}ver;
int time = 0,group_count = 0,in[SIZE]= {0};
ver* uf_to_ver[2*SIZE] = {NULL};
nodes vertice_list[SIZE],Re_vertice_list[SIZE],SCC_list[SIZE];
ver* vertice[SIZE],*SCC[SIZE];
void init(){
    for(int i=0;i<SIZE;i++){
        vertice_list[i].id = i;
        vertice_list[i].next = NULL;
        Re_vertice_list[i].id = i;
        Re_vertice_list[i].next = NULL;
        SCC_list[i].id = i;
        SCC_list[i].next = NULL;
        vertice[i] = (ver*)malloc(sizeof(ver));
        vertice[i]->id = i;
        vertice[i]->p = NULL;
        vertice[i]->color = 0;
        vertice[i]->group = -1;
        SCC[i] = (ver*)malloc(sizeof(ver));
        SCC[i]->id = i;
        SCC[i]->p = NULL;
        SCC[i]->color = 0;
    }
}
int max_(int a,int b){   return a>b?a:b;}
void DFS_(ver* node){
    time++;
    node->d = time;
    node->color = 1;
    for(nodes* tmp = vertice_list[node->id].next;tmp!=NULL;tmp = tmp->next){
        if(vertice[tmp->id]->color==0){
            vertice[tmp->id]->p = node;
            DFS_(vertice[tmp->id]);
        }
    }
    node->color = 2;
    time++;
    node->f = time;
    uf_to_ver[time] = node;
}
void DFS_Re(ver* node){
    node->color = 1;
    node->group = group_count;
    for(nodes* tmp = Re_vertice_list[node->id].next;tmp!=NULL;tmp = tmp->next){
        if(vertice[tmp->id]->color==0){
            vertice[tmp->id]->p = node;
            DFS_Re(vertice[tmp->id]);
        }
        if(vertice[tmp->id]->group !=-1 && vertice[tmp->id]->group != group_count){       
            //nodes* temp = SCC_list[group_count].next;
            nodes* temp = SCC_list[vertice[tmp->id]->group].next;
            nodes* new = (nodes*)malloc(sizeof(nodes));
            //new->id = vertice[tmp->id]->group;
            new->id = group_count;
            new->next = temp;
            //SCC_list[group_count].next = new;
            SCC_list[vertice[tmp->id]->group].next = new;
            //printf("%lld ",SCC_list[vertice[tmp->id]->group].next->id);
            in[group_count]++;
        }
    }
    node->color = 2;
}
//int SCC_count = 0;
/*int DFS_SCC(ver* node){
    //printf("hi:%lld ",node->id);
    //node->color = 1;
    int cnt = 0,plugger;
    for(nodes* tmp = SCC_list[node->id].next;tmp!=NULL;tmp = tmp->next){
        in[tmp->id]--;
        if(in[tmp->id]==0){  
            cnt++;
            plugger = tmp->id;
        }
    }
    //printf("cnt = %lld",cnt);
    if(cnt==0)  return 1;
    else if(cnt>1)  return 0;
    else    return DFS_SCC(SCC[plugger]);
    //node->color = 2;
    //SCC_count++;
}*/
signed main(){
    init();
    int B,A,mode;
    scanf("%lld%lld%lld",&B,&A,&mode);
    for(int i=0;i<A;i++){
        int a,b;
        scanf("%lld%lld",&a,&b);
        nodes* tmp = vertice_list[a].next;
        nodes* newone = (nodes*)malloc(sizeof(nodes));
        newone->id = b; newone->next = NULL;
        vertice_list[a].next = newone;
        newone->next = tmp;

        nodes* tmp_ = Re_vertice_list[b].next;
        nodes* newone_ = (nodes*)malloc(sizeof(nodes));
        newone_->id = a;newone_->next = NULL;
        Re_vertice_list[b].next = newone_;
        newone_->next = tmp_;
    }
    for(int i=1;i<=B;i++){
        if(vertice[i]->color==0){
            DFS_(vertice[i]);
        }
    }
    
    for(int i=1;i<=B;i++){
        vertice[i]->p = NULL;
        vertice[i]->color = 0;
    }
    bool fla = 0;
    int head_vertex;
    for(int i=B*2;i>=0;i--){
        if(uf_to_ver[i]!=NULL && uf_to_ver[i]->color==0){
            if(fla==0){
                head_vertex = uf_to_ver[i]->id;
                fla = 1;
            }
            //printf("the vertex now is: %d\n",uf_to_ver[i]->id);
            DFS_Re(uf_to_ver[i]);
            group_count++;
        }
        
    }
    //for(int i=1;i<=B;i++)   printf("%lld ",vertice[i]->group);
    printf("%lld\n",group_count);
    if(mode==2){
        int cnt = 0,curr;
        for(int i=0;i<group_count;i++){
            //printf("%lld ",in[i]);
            if(in[i]==0){
                cnt++;
                curr = i;
            }
        }
        //printf("\n");
        if(cnt!=1)   printf("0");
        else{
            bool resume=1;
            while(resume){
                int counter = 0,successor;
                nodes* tmp=SCC_list[curr].next;
                if(tmp==NULL)   break;
                for(;tmp!=NULL;tmp = tmp->next){
                    in[tmp->id]--;
                    if(in[tmp->id]==0){
                        counter++;
                        successor = tmp->id;
                    }
                }
                if(counter==1)  curr = successor;
                else    resume = 0;
            }
            if(resume)    printf("1");
            else    printf("0");
            //printf("%lld ",head_vertex);
            /*int SCC_count = DFS_SCC(SCC[vertice[head_vertex]->group]);
            //printf("\n%lld ",SCC_count);
            if(SCC_count==1)    printf("1");
            else    printf("0");*/
            
        }
    }
}
/*
8 10 2
1 2
2 3
3 1
3 4
4 5
5 6
6 7
7 8
7 5
5 8
*/