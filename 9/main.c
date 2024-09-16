#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define int long long 

bool isdigit_(char c){
    return (c<='9' && c>='0')?1:0;
}
int weight(char o){
    if(o=='(' || o==')')    return 0;
    if(o=='*' || o=='/' || o=='%')  return 2;
    else    return 1;
}
signed main(){
    for(int qq = 0;qq<3;qq++){
        char ori[4010] = {'\0'};
        char stack_1[4010] = {'\0'},stack_t[4010] = {'\0'};
        int nums_2[4010] = {0},nums_t[4010] = {0};
        int s_1,s_2,n_1,n_2,s_t,n_t;
        s_1=s_2=n_1=n_2=s_t=n_t=0;
        scanf("%s",ori);
        for(int i=0;i<strlen(ori);i++){
            if(isdigit_(ori[i])){
                int tmp = ori[i]-'0';
                while(i+1<strlen(ori) && isdigit_(ori[i+1])){
                    i++;
                    tmp = tmp*10+(ori[i]-'0');
                }
                stack_t[s_t] = 'a';
                s_t++;
                nums_t[n_t] = tmp;
                n_t++;
            }
            else if(ori[i]=='+'||ori[i]=='-'||ori[i]=='*'||ori[i]=='/'||ori[i]=='%'||ori[i]==')'||ori[i]=='('){
                if(ori[i]=='('){
                    stack_1[s_1] = '(';
                    s_1++;
                }
                else if(ori[i]==')'){
                    while(s_1>0 && stack_1[s_1-1]!='('){
                        stack_t[s_t] = stack_1[s_1-1];
                        s_1--;
                        s_t++;
                    }
                    s_1--;
                }
                else{
                    while(s_1>0 && weight(stack_1[s_1-1])>=weight(ori[i])){
                        stack_t[s_t] =  stack_1[s_1-1];
                        s_1--;
                        s_t++;
                    }
                    stack_1[s_1] = ori[i];
                    s_1++;
                }
            }
            
        }
        while(s_1>0){
            stack_t[s_t] = stack_1[s_1-1];
            s_1--;
            s_t++;
        }
        /*for(int i=0;i<n_t;i++)
            printf("%d ",nums_t[i]);
        printf("\n");*/
        n_t = 0;
        for(int i=0;i<s_t;i++){
            if(stack_t[i]!='a') {
                printf("%c",stack_t[i]);
                int n1 = -1,n2 = -1;
                bool check_1 = 0,check_2 = 0;
                if(n_2>0){
                    n2 = nums_2[n_2-1];
                    n_2--;
                    check_1 = 1;
                }
                if(n_2>0){
                    n1 = nums_2[n_2-1];
                    n_2--;
                    check_2 = 1;
                }
                //printf("n1=%d,n2=%d,ope=%c\n",n1,n2,stack_t[i]);
                if(check_1 && check_2){
                    if(stack_t[i]=='+'){
                        nums_2[n_2] = n1+n2;
                        n_2++;
                    }
                    else if(stack_t[i]=='-'){
                        nums_2[n_2] = n1-n2;
                        n_2++;
                    }
                    else if(stack_t[i]=='*'){
                        nums_2[n_2] = n1*n2;
                        n_2++;
                    }
                    else if(stack_t[i]=='/'){
                        nums_2[n_2] = n1/n2;
                        n_2++;
                    }
                    else if(stack_t[i]=='%'){
                        nums_2[n_2] = n1%n2;
                        n_2++;
                    }
                }
            }
            else{
                printf("%lld",nums_t[n_t]);
                nums_2[n_2] = nums_t[n_t];
                n_2++;
                n_t++;
            }
        }
        printf("=%lld\n",nums_2[0]);
    }
    return 0;
}


