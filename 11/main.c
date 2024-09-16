#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#define int long long
#define SIZE 1000004

typedef struct deque{
    int value;
    struct deque *next,*prev;
}dq;

typedef struct Node{
    int id,deepest,length,reward;
    struct Node *left_sib,*right_sib,*first_chi,*last_chi,*parent;
    dq *dq_depth_head,*dq_depth_tail, *dq_id_head, *dq_id_tail;
}node;
typedef struct trea
{
    int place,value;
}Trea;

//deque:小孩深度單調隊列，deque_id:小孩深度對應的index的單調隊列
node *dungeons[1000003],*stack[1000002];//stack is used to record the nodes that have been traversed
int stack_depth[1000002];//小到大 0,d1,d1+d2,d1+d2+d3..
int curr_depth = 0;
void init(int N){
    for(int i=0;i<N;i++){
        dungeons[i] = (node*)malloc(sizeof(node));
        dungeons[i]->first_chi = NULL;
        dungeons[i]->id = i;
        dungeons[i]->last_chi = NULL;
        dungeons[i]->parent= NULL;
        dungeons[i]->left_sib = NULL;
        dungeons[i]->right_sib = NULL;
        dungeons[i]->length = 0;
        dungeons[i]->reward = -1;
        dungeons[i]->dq_depth_head = (dq*)malloc(sizeof(dq));
        dungeons[i]->dq_depth_tail = (dq*)malloc(sizeof(dq));
        dungeons[i]->dq_id_head = (dq*)malloc(sizeof(dq));
        dungeons[i]->dq_id_tail = (dq*)malloc(sizeof(dq));

        dungeons[i]->dq_depth_head->next = dungeons[i]->dq_depth_tail;
        dungeons[i]->dq_depth_head->prev = NULL;
        dungeons[i]->dq_depth_tail->prev = dungeons[i]->dq_depth_head;
        dungeons[i]->dq_depth_tail->next = NULL;
        dungeons[i]->dq_id_head->next = dungeons[i]->dq_id_tail;
        dungeons[i]->dq_id_head->prev = NULL;
        dungeons[i]->dq_id_tail->prev = dungeons[i]->dq_id_head;
        dungeons[i]->dq_id_tail->next = NULL;
    }
    stack[0] = dungeons[0];
    stack_depth[0] = 0;
}
void setup(int u,int v,int l){
    dungeons[v]->length = l;
    dungeons[v]->parent = dungeons[u];
    if(dungeons[u]->first_chi == NULL){
        dungeons[u]->first_chi = dungeons[v];
        dungeons[u]->last_chi = dungeons[v];
    }
    else{
        dungeons[u]->last_chi->right_sib = dungeons[v];
        dungeons[v]->left_sib = dungeons[u]->last_chi;
        dungeons[u]->last_chi = dungeons[v];
    }
}
int Dfs(node* root){
    //printf("%lld ",root->id);
    if(root->first_chi!=NULL){
        node* children = root->first_chi;
        for(;children!=NULL;children = children->right_sib){
            int depth;
            depth = children->length+Dfs(children);
            dq *num = (dq*)malloc(sizeof(dq)), *ID = (dq*)malloc(sizeof(dq));
            num->value = depth; ID->value = children->id;//obtaining value
            
            root->dq_depth_tail->prev->next = num;
            num->prev = root->dq_depth_tail->prev;
            root->dq_depth_tail->prev = num;
            num->next = root->dq_depth_tail;
            
            root->dq_id_tail->prev->next = ID;
            ID->prev = root->dq_id_tail->prev;
            root->dq_id_tail->prev = ID;
            ID->next = root->dq_id_tail;
            if(root->dq_depth_tail->prev->value >= root->dq_depth_head->next->value){
                root->dq_depth_head->next = root->dq_depth_tail->prev;
                root->dq_depth_tail->prev->prev = root->dq_depth_head;
                
                root->dq_id_head->next = root->dq_id_tail->prev;
                root->dq_id_tail->prev->prev = root->dq_id_head;
            }
            else{
                while(root->dq_depth_tail->prev->value > root->dq_depth_tail->prev->prev->value){
                    dq *tmp = root->dq_id_tail->prev;
                    //printf("%lld ",root->id);
                    tmp->prev->prev->next = tmp;
                    tmp->prev = tmp->prev->prev;
                    
                    dq *tmp1 = root->dq_depth_tail->prev;
                    tmp1->prev->prev->next = tmp1;
                    tmp1->prev = tmp1->prev->prev;
                }
            }
        }//else    printf(":NULL ");
        return  root->dq_depth_head->next->value;
    }
    return 0;
}

signed main(){
    int N,Q,M; scanf("%lld%lld%lld",&N,&M,&Q);
    init(N);
    while(M--){
        int u,v,l;
        scanf("%lld%lld%lld",&u,&v,&l);
        setup(u,v,l);
    }
    Dfs(dungeons[0]);
    //printf("%lld %lld",dungeons[0]->dq_depth_head->next->value,dungeons[0]->dq_id_head->next->value);
    node *curr = dungeons[0];
    Trea* trea_q[SIZE];
    //for(int i=0;i<N;i++)    trea_q[i] = (Trea*)malloc(sizeof(Trea));
    int trea_stack[SIZE], trea_layer_stack[SIZE],trea_stack_l = 0,trea_stack_r = 0;
    int trea_l = 0,trea_r = 0;
    while(Q--){
        int ope;scanf("%lld",&ope);
        if(ope==1){
            if(curr->first_chi != NULL){
                curr_depth++;
                curr = curr->first_chi;
                printf("%lld\n",curr->id);
                stack[curr_depth] = curr;
                stack_depth[curr_depth] = stack_depth[curr_depth-1]+curr->length;
            }
            else    printf("-1\n");
        }
        else if(ope == 2){
            if(curr->parent!=NULL){
                
                node* Parent = curr->parent;
                if(Parent->first_chi->id==Parent->dq_id_head->next->value){
                    Parent->dq_id_head->next->next->prev = Parent->dq_id_head;
                    Parent->dq_id_head->next = Parent->dq_id_head->next->next;

                    Parent->dq_depth_head->next->next->prev = Parent->dq_depth_head;
                    Parent->dq_depth_head->next = Parent->dq_depth_head->next->next;
                }
                if(Parent->first_chi == Parent->last_chi){
                    Parent->last_chi = NULL;
                    Parent->first_chi = NULL;
                    curr->parent = NULL;
                }
                else{
                    Parent->first_chi = curr->right_sib;
                    Parent->first_chi->left_sib = NULL;
                    curr->parent = NULL;
                }
                curr = Parent;
                printf("%lld\n",curr->id);
                if(trea_stack_r-1>=0 && trea_layer_stack[trea_stack_r-1]==curr_depth){
                    if(trea_stack_r-2>=0 && trea_layer_stack[trea_stack_r-2]>=trea_layer_stack[trea_stack_r-1])
                        trea_layer_stack[trea_stack_r-2] = trea_layer_stack[trea_stack_r-1]-1;
                    trea_stack_r--;
                    trea_r--;
                }
                curr_depth--;
            }
            else    printf("-1\n");
        }
        else if(ope==3){
            int t;scanf("%lld",&t);
            int L = 0,R = curr_depth,target;
            bool found = 0;
            while(L<R){
                int m = (L+R)/2;
                if(stack_depth[curr_depth]-stack_depth[m]>t){
                    if(m<=curr_depth && stack_depth[curr_depth]-stack_depth[m+1]<=t){
                        found = 1;
                        target = m+1;
                        break;
                    }
                    else    L = m+1;
                }
                else{
                    if(m>0 && stack_depth[curr_depth]-stack_depth[m-1]>t){
                        found = 1;
                        target = m;
                        break;
                    }
                    else    R = m-1;
                }
            }
            if(found==0)    target = L;
            printf("%lld\n",stack[target]->id);
        }
        else if(ope==4){
            //printf("%lld",curr->id);
            printf("%lld\n",curr->dq_depth_head->next->value);
        }
        else if(ope==5){
            int p;
            scanf("%lld",&p);
            int L = 0,R = curr_depth,target;
            bool found = 0;
            while(L<R){
                int m = (L+R)/2;
                if(stack_depth[curr_depth]-stack_depth[m]>p){
                    if(m<=curr_depth && stack_depth[curr_depth]-stack_depth[m+1]<=p){
                        found = 1;
                        target = m+1;
                        break;
                    }
                    else    L = m+1;
                }
                else{
                    if(m>0 && stack_depth[curr_depth]-stack_depth[m-1]>p){
                        found = 1;
                        target = m;
                        break;
                    }
                    else    R = m-1;
                }
            }
            if(found==0)    target = L;
            
            Trea* curr_treasure = (Trea*)malloc(sizeof(Trea));
            curr_treasure->place = target-1;
            if(target==0){
                curr_treasure->value = p-(stack_depth[curr_depth]-stack_depth[0]);
                curr_treasure->place = -1;
            }
            else{
                curr_treasure->value = p;
                curr_treasure->place = stack[target-1]->id;
            }
            //printf("place:%lld\n",curr_treasure->place);
            trea_q[trea_r] = curr_treasure;
            trea_r++;
            trea_stack[trea_stack_r] = curr_treasure->value;
            trea_layer_stack[trea_stack_r] = curr_depth;
            trea_stack_r++;
            if(trea_r-trea_l>curr_depth){
                if(trea_q[trea_l]->place == -1){
                    printf("value remaining is %lld\n",trea_q[trea_l]->value);
                }
                else{
                    printf("value lost at %lld\n",trea_q[trea_l]->place);
                }
                trea_l++;
                trea_stack_l++;
            }
            
        }
        else if(ope == 6){

        }
    }
}
/*
7 6 18
0 1 7
1 2 8
2 3 6
3 6 1
1 4 3
4 5 2
1
5 4
1
1
1
5 8
5 7
5 6
5 5
2
2
2
1
1
5 100
5 30
2
5 70
*/

