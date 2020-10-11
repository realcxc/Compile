#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
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
        else if(ch=='*'){
            puts("Star");
            continue;
        }
        else if(ch==','){
            puts("Comma");
            continue;
        }
        else if(ch=='('){
            puts("LParenthesis");
            continue;
        }
        else if(ch==')'){
            puts("RParenthesis");
            continue;
        }
        else if(ch==':'){
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
        else if(isdigit(ch)){
            int ans=ch-'0';
            while((ch=getc(fp))!=EOF&&isdigit(ch)){
                ans=ans*10+ch-'0';
            }
            printf("Int(%d)\n",ans);
            fseek(fp,-1L,1);
        }
        else if(isalpha(ch)){
            char s[500];
            int i=0;
            s[i++]=ch;
            while((ch=getc(fp))!=EOF&&(isdigit(ch)||isalpha(ch))){
                s[i++]=ch;
            }
            s[i]=0;
            if(strcmp(s,"BEGIN")==0||strcmp(s,"END")==0||strcmp(s,"FOR")==0||strcmp(s,"IF")==0||strcmp(s,"THEN")==0||
            strcmp(s,"ELSE")==0){
                for(int j=1;j<strlen(s);j++){
                    s[j]=tolower(s[j]);
                }
                puts(s);
            }
            else{
                printf("Ident(%s)\n",s);
            }
        }
        else if(ch==' '||ch=='\n'||ch=='\t'){
            continue;
        }
        else{
            puts("Unknown");
            break;
        }
    }
    fclose(fp);
    return 0;
}