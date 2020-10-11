#include <stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char ** argv){
    FILE *fp=NULL;
    char ch;
    char *s=NULL;
    //打开文件
    fp = fopen(argv[1],"r");
    //第一个双引号里面放的是文件具体路径，第二个是对文件进行的操作
    while((ch=getc(fp))!=EOF){
        if(ch=='+'){
            puts("Plus");
            continue;
        }
        if(ch=='*'){
            puts("Star");
            continue;
        }
        if(ch==','){
            puts("Comma");
            continue;
        }
        if(ch=='('){
            puts("LParenthesis");
            continue;
        }
        if(ch==')'){
            puts("RParenthesis");
            continue;
        }
        if(ch==':'){
            char ch1=getc(fp);
            if(ch1=='='){
                puts("Assign");
            }
            else{
                puts("Colon");
                if(ch1==EOF){
                    return 0;
                }
                fseek(fp,-1L,1);
            }
            continue;
        }
    }
    fclose(fp);
    return 0;
}