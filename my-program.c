#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
int matrix[6][6]={ 1,-1,-1,-1, 1, 1,
                   1, 1,-1,-1, 1, 1,
                   1, 1, 2, 2, 1, 1,
                  -1,-1,-1,-1, 0, 2,
                   1, 1, 2, 2, 1, 1,
                  -1,-1,-1,-1, 2, 2,
};
int get_priority(char a,char b){
    int aa,bb;
    switch (a)
    {
    case '+':
        aa=0;
        break;
    case '*':
        aa=1;
        break;
    case 'i':
        aa=2;
        break;
    case '(':
        aa=3;
        break;
    case ')':
        aa=4;
        break;
    case '#':
        aa=5;
        break;
    default:
        break;
    }
    switch (b)
    {
    case '+':
        bb=0;
        break;
    case '*':
        bb=1;
        break;
    case 'i':
        bb=2;
        break;
    case '(':
        bb=3;
        break;
    case ')':
        bb=4;
        break;
    case '#':
        bb=5;
        break;
    default:
        break;
    }
    return matrix[aa][bb];
}
int main(int argc, char ** argv){
    FILE *fp=NULL;
    char ch;
    //打开文件
    fp = fopen(argv[1],"r");
    //第一个双引号里面放的是文件具体路径，第二个是对文件进行的操作
    char op_stack[1050],sub_stack[1050];
    int op_pointer=0,sub_pointer=-1;
    op_stack[0]='#';
    char s[1050];
    int i=0;
    while((ch=getc(fp))!='\n'){
        s[i++]=ch;
    }
    s[i]=0,s[i-1]='#';
    fclose(fp);
    int read=0;
    while(op_stack[op_pointer]!='#'||s[read]!='#'){
        char curread=s[read],curop=op_stack[op_pointer];
        switch (get_priority(curop,curread))
        {
        case -1:
            if(curread=='i'){
                sub_stack[++sub_pointer]=curread;
            }
            op_stack[++op_pointer]=s[read++];
            printf("I%c\n",curread);
            break;
        case 0:
            read++;
            op_pointer--;
            break;
        case 1:
            if(curop=='i'){
                if(sub_stack[sub_pointer]=='i'){
                    sub_pointer--;
                    sub_stack[++sub_pointer]='N';
                    op_pointer--;
                    puts("R");
                }
                else{
                    puts("RE");
                    return 0;
                }
            }
            else if(curop=='+'||curop=='*'){
                    if(sub_pointer>0&&sub_stack[sub_pointer]=='N'&&sub_stack[sub_pointer-1]=='N'){
                        sub_pointer-=2;
                        sub_stack[++sub_pointer]='N';
                        op_pointer--;
                        puts("R");
                    }
                    else{
                        puts("RE");
                        return 0;
                }
            }
            else if(curop==')'){
                    op_pointer--;
            }
            break;
        case 2:
            puts("E");
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}