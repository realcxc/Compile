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
        aa=6;
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
        bb=6;
        break;
    }
    if(aa>5||bb>5)
        return 2;
    return matrix[aa][bb];
}
int main(int argc, char ** argv){
    FILE *fp=NULL;
    char ch;
    //打开文件
    fp = fopen(argv[1],"r");
    //第一个双引号里面放的是文件具体路径，第二个是对文件进行的操作
    char op_stack[1050];
    int op_pointer=0;
    op_stack[0]='#';
    char s[1050];
    int i=0;
    while((ch=getc(fp))!=EOF){
        s[i++]=ch;
    }
    s[i-1]=0,s[i-2]='#';
    fclose(fp);
    int read=0;
    while(!(op_pointer<=1&&s[read]=='#')){
        op_stack[op_pointer+1]=0;
        char curread=s[read],curop;
        for(int i=op_pointer;i>=0;--i){
            if(op_stack[i]!='N'){
                curop=op_stack[i];
                break;
            }
        }
        switch (get_priority(curop,curread))
        {
        case -1:
            op_stack[++op_pointer]=s[read++];
            printf("I%c\n",curread);
            break;
        case 0:
            printf("I%c\n",curread);
            op_stack[++op_pointer]=s[read++];
            break;
        case 1:
            if(curop=='i'){
                if(op_stack[op_pointer]=='i'){
                    op_stack[op_pointer]='N';
                    puts("R");
                }
                else{
                    puts("RE");
                    return 0;
                }
            }
            else if(curop=='+'||curop=='*'){
                    if(op_pointer>2&&op_stack[op_pointer-2]=='N'&&op_stack[op_pointer]=='N'){
                        op_pointer-=3;
                        op_stack[++op_pointer]='N';
                        puts("R");
                    }
                    else{
                        puts("RE");
                        return 0;
                }
            }
            else if(curop==')'){
                    if(op_pointer>2&&op_stack[op_pointer-2]=='('&&op_stack[op_pointer-1]=='N'){
                        op_pointer-=3;
                        op_stack[++op_pointer]='N';
                        puts("R");
                    }
                    else{
                        puts("RE");
                        return 0;
                }
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
