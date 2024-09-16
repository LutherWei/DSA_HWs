#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#define ll long long
#define int long long

struct vector
{
    struct vector* next;
    struct vector* pre;
    long long value;
};
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Vector;

Vector* create_vector(size_t initial_capacity) {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        fprintf(stderr, "Failed to allocate memory for vector\n");
        exit(1);
    }
    
    vec->data = (int*)malloc(initial_capacity * sizeof(int));
    if (vec->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for vector data\n");
        free(vec);
        exit(1);
    }
    
    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

void push_back(Vector* vec, int value) {
    if (vec->size >= vec->capacity) {
        // Double the capacity when the vector is full
        vec->capacity *= 2;
        vec->data = (int*)realloc(vec->data, vec->capacity * sizeof(int));
        if (vec->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for vector data\n");
            free(vec);
            exit(1);
        }
    }
    
    vec->data[vec->size] = value;
    vec->size++;
}

void free_vector(Vector* vec) {
    free(vec->data);
    free(vec);
}
struct Players
{
    long long id;
    long long score;
    long long rank;
    int last_re;
    
};
typedef struct vector vecc;
typedef struct Players player;

signed main(){
    long long N,M,T;
    scanf("%lld%lld%lld",&N,&T,&M);
    Vector* attack[N+1];
    long long count[N+1],sum[N+1];
    player *order[N+1], players[N+1];//array order is for binary search, array players stores the rank, id and score
    vecc *list_h[N+1],*list_last[N+1]/*,*att_rec_h[N+1],*att_rec_t[N+1]*/;
    int **att_rec;
    att_rec = (int**)malloc(sizeof(int*)*(N+1));
    long long reward_count = 0;
    for(int i=1;i<=N;i++){
        attack[i] = create_vector(4);
        //att_rec[i] = (int*)malloc(sizeof(int)*500002);
        list_h[i] = (vecc*)malloc(sizeof(vecc));
        list_h[i]->value = 0;
        list_last[i] = (vecc*)malloc(sizeof(vecc));
        list_h[i]->next = list_last[i];
        list_last[i]->pre = list_h[i];
        /*att_rec_t[i] = (vec*)malloc(sizeof(vec));
        att_rec_h[i] = (vec*)malloc(sizeof(vec));
        att_rec_t[i]->pre = att_rec_h[i];
        att_rec_h[i]->next = att_rec_t[i];*/
        count[i] = 0;
        sum[i] = 0;

        players[i].id = i;
        players[i].last_re = 0;
        scanf("%lld",&players[i].score);
        order[i] = &(players[i]);
        players[i].rank = i;

    }
    while (T--){
        int t;scanf("%lld",&t);
        if(t==1){
            long long a;
            scanf("%lld",&a);
            long long curr_r = players[a].rank;
            if(curr_r!=1){
                //add the reward
                order[curr_r]->score += (N-curr_r)*(reward_count-order[curr_r]->last_re);
                order[curr_r]->last_re = reward_count;
                order[curr_r-1]->score += (N-curr_r+1)*(reward_count-order[curr_r-1]->last_re);
                order[curr_r-1]->last_re = reward_count;
                
                long long curr_sco = order[curr_r]->score, target_sco = order[curr_r-1]->score;
                
                players[a].score = order[curr_r-1]->score;//attack applies here
                //swap the rank
                long long temp = players[a].rank;
                players[a].rank = order[curr_r-1]->rank;
                order[curr_r-1]->rank = temp;
                //swap the position
                player* tmp = order[curr_r];
                order[curr_r] = order[curr_r-1];
                order[curr_r-1] = tmp;
                //add node to the record list
                (list_h[a]->value)++;
                vecc *new = (vecc*)malloc(sizeof(vecc));
                new->value = target_sco-curr_sco;
                new->pre = list_last[a]->pre;
                new->next = list_last[a];
                list_last[a]->pre = new;
                new->pre->next = new;
                //add node to the attack record list that sum up
                /*vec *New = (vec*)malloc(sizeof(vec));
                New->value = target_sco-curr_sco;
                if(count[a]<M){
                    count[a]++;
                    sum[a]+=New->value;
                    att_rec_t[a]->pre->next = New;
                    New->pre = att_rec_t[a]->pre;
                    att_rec_t[a]->pre = New;
                    New->next = att_rec_t[a];
                }
                else{
                    sum[a]-=att_rec_h[a]->next->value;
                    att_rec_h[a]->next = att_rec_h[a]->next->next;
                    att_rec_h[a]->next->pre = att_rec_h[a];
                    sum[a]+=New->value;
                    att_rec_t[a]->pre->next = New;
                    New->pre = att_rec_t[a]->pre;
                    att_rec_t[a]->pre = New;
                    New->next = att_rec_t[a];
                }*/
                
                //if(count[a]>0)  att_rec[a][count[a]] = att_rec[a][count[a]-1]+target_sco-curr_sco;
                if(count[a]>0)  push_back(attack[a], attack[a]->data[count[a]-1]+target_sco-curr_sco);
                //else    att_rec[a][count[a]] = target_sco-curr_sco;
                else    push_back(attack[a], target_sco-curr_sco);
                count[a]++;
            }
        }
        else if(t==2){
            reward_count++;
        }
        else if(t==3){
            ll tar,l = 1,r = N; scanf("%lld",&tar);
            if(order[1]->score+(N-1)*(reward_count-order[1]->last_re)<tar) printf("0 0\n");
            else{
            //binary search
                while(l<r){
                    ll m = (l+r+1)/2;
                    if(tar<=order[m]->score+(N-m)*(reward_count-order[m]->last_re))    l = m;
                    else r = m-1;
                }
                printf("%lld %lld\n",order[l]->rank,order[l]->id);
            }   
        }
        else if(t==4){
            ll b,m,time = 0,adder = 0;
            scanf("%lld%lld",&b,&m);
            if(count[b]==0) printf("0\n");
            else{
                //if(count[b]-1-m<0)  printf("%lld\n",att_rec[b][count[b]-1]);
                if(count[b]-1-m<0)  printf("%lld\n",attack[b]->data[count[b]-1]);
                //else    printf("%lld\n",att_rec[b][count[b]-1]-att_rec[b][count[b]-1-m]);
                else    printf("%lld\n",attack[b]->data[count[b]-1]-attack[b]->data[count[b]-1-m]);
            }
            /*if(m==M || (list_h[b]->value<=m))    printf("%lld\n",sum[b]);
            else{
                vec* tmp = att_rec_t[b];
                for(;time<m && tmp->pre!=att_rec_h[b];time++){
                    tmp = tmp->pre;
                    adder += tmp->value;
                    //printf("%lld ",tmp->value);
                }
                printf("%lld\n",adder);
            }*/
        }
        /*for(int i=1;i<=N;i++){
            printf("%lld: %lld(%lld), ",order[i]->rank,order[i]->id,order[i]->score);
        }
        printf("\n");*/
        
    }
    printf("\n");
    for(int i=1;i<=N;i++){
        vecc* tmp = list_h[i];
        printf("%lld ",tmp->value);
        while(tmp->next!=list_last[i]){
            tmp = tmp->next;
            printf("%lld ",tmp->value);
        }
        printf("\n");
    }
}