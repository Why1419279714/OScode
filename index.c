#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include "./source/ls.h"
#include "./source/rm.h"
#include "./source/vi.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "./source/copy.h"
#include "./source/cat.h"

#include "./source/echo.h"
#include "./source/mkdir_1.h"
#include "./source/rmdir_.h"
#define MAX 100
#define LEN 100

char *arglist[MAX];  //shell指令参数表
int num;             //shell指令参数个数


/*struct history{
    char a[100];
    struct history *next;

}


void history_ai(char list[100][256])
{
    if(strcmp(list[0],"history")==0)
    {
       read_history(NULL);
    }

}*/

int execute(char* arglist[])//执行外部命令
{
    if(strcmp(arglist[0],"rm\0")==0)
    {
        rm(arglist);
    }
    else if(strcmp(arglist[0],"vi\0")==0)
    {
        vi(num,arglist);
    }
    else if(strcmp(arglist[0],"copy\0")==0)
        {
                copy_();
        }
    else if(strcmp(arglist[0],"echo\0")==0)
    {
        echo(num,arglist);
    }
    else if(strcmp(arglist[0],"ls\0")==0)
    {
        ls(num,arglist);
    }
    else if(strcmp(arglist[0],"cat\0")==0)
    {
        cat(num,arglist);
    }
    else if(strcmp(arglist[0],"mkdir\0")==0)
    {
        mkdir_(num,arglist);
    }
    else if(strcmp(arglist[0],"rmdir\0")==0)
    {
        rmdir_(num,arglist);
    }
    exit(1);
}

char* make(char *buf)//将字符串传入参数表内
{
    char *cp;
    cp=malloc(strlen(buf)+1);
    if (cp==NULL)
    {
        fprintf(stderr,"no memory\n");
        exit(1);
    }
    strcpy(cp,buf);
    return cp;
}

int my_system(char *buf,char *arglist[])//对于字符串进行分割
{
    int num,j,i,last;
    char buffer[LEN];
    num=0;
    i=0;
    while (num<MAX)
    {
        if (buf[i]=='\n')
        {
            arglist[num]=NULL;
            return num;
        }
        if (buf[i]==' ') i++;
        last=i;
        while (buf[i]!=' ' && buf[i]!='\n') i++;
        for (j=last;j<i;j++) buffer[j-last]=buf[j];
        buffer[j-last]='\0';
        arglist[num++]=make(buffer);
    }
}

int inner(char *arglist[])//执行内置指令
{
    if (strcmp(arglist[0],"exit\0")==0)//exit
    {
        exit(0);
        return 1;
    }
   else
         if (strcmp(arglist[0],"pwd\0")==0)//pwd
           {
             char buf[LEN];
             getcwd(buf,sizeof(buf));//获得当前目录
             printf("%s\n",buf);
            // pwd(num,arglist);        
             return 1;
    }
    else
         if (strcmp(arglist[0],"cd\0")==0)//cd
            {
            char buf[LEN];
            if (chdir(arglist[1])>=0)
            {
              getcwd(buf,sizeof(buf));
              printf("Current dir is:%s\n",buf);
            }
            return 1;
    }
   /* else 
         if (strcmp(arglist[0],"history\0")==0)//history
            {
            read_history(NULL);
            return 1;
    }*/
    else return 0;
}
void print_prompt()
{
    char buf[LEN];
    printf("[why@myshell%s]$",getcwd(buf,LEN));
}

int main()
{
    int i,pid;
    char buf[LEN];
    while (1)
    {
        print_prompt();
        //stty erase '^H';
        fflush(stdout);
        // buf=readline("myshell&");
        fgets(buf,LEN,stdin);//读入单行指令
        // add_history(buf);
        //write_history(NULL);
        num=my_system(buf,arglist);//指令分割//printf("%d",num);
        int inner_flag;
        inner_flag=inner(arglist);//内置指令判断//printf("%d",inner_flag);
        if (inner_flag==0)//外部指令
        {
            pid=fork();//建立新的进程
            if (pid==0)//子进程
            {
               execute(arglist);//执行        
            }
            waitpid(pid,NULL,0);
        }
        //重定向


    }
    return 0;
}


