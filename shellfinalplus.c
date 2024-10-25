/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l) {
    l->head=NULL;
    return;
}

/**
销毁一个log，释放所有内存空间，log的“析构函数”
 */

void log_destroy(log_t* l) {
     if(l->head!=NULL) {
         node *pre=l->head,*p=l->head->next;
         while(p!=NULL) {
             free(pre->cmd);
             free(pre);
             pre=p;
             p=pre->next;
         }
         free(pre->cmd);
         free(pre);
         l->head=NULL;
     }
     return;
}

/**
向log中推入一个字符串，你可以将log视为一个由链表组成的栈
 */

void log_push(log_t* l, const char *item) {
      if(l->head==NULL) {
          node *p=(node *)malloc(sizeof(node));
          p->cmd = (char *)malloc(sizeof(char) * (strlen(item) + 1));
          strcpy(p->cmd,item);
          p->next=l->head;
          l->head=p;
      } else {
          node *p=(node *)malloc(sizeof(node)),*q;
          p->cmd = (char *)malloc(sizeof(char) * (strlen(item) + 1));
          strcpy(p->cmd,item);
          p->next=NULL;
          q=l->head;
          while(q->next!=NULL) {
              q=q->next;
          }
          q->next=p;
      }
      return;
}


/**
搜索log中是否含有对应前缀的字符串
 */

char *log_search(log_t* l, const char *prefix) {
    int len=strlen(prefix),i;
    // str=(char *)malloc(sizeof(char)*100);
    // node *p=(node *)malloc(sizeof(node));
    // p->cmd=(char *)malloc(sizeof(char)*(len+1));
    node *p;
    p=l->head;
    while(p!=NULL) {
        for(i=0;i<len;i++) {
            // printf("p->cmd[%d]=%c\n",i,p->cmd[i]);
            // printf("perfix[%d]=%c\n",i,prefix[i]);
            if(p->cmd[i]!=prefix[i]) {
                break;
            }
        }
        if(i<len) {
            p=p->next;
        } 
        else if(i==len) {
            // strcpy(str,p->cmd);
            // free(p);
            return p->cmd;
        }
    }
    return NULL;
}




#include "shell.h"
/**
 * shell的入口
 */
void prefix() {
    char *path = NULL;
    path = getcwd(NULL,0);
    printf("%s$ ",path);
    free(path);
    return;
}

int execute(char* buffer) {
    if(buffer[0]=='c') {
        char str[100]={'\0'};
        int i,j;
        int len=strlen(buffer);
        for(i=0,j=3;j<len;i++,j++) {
            str[i]=buffer[j];
            //printf("i=%d,str[%d]=%c\n",i,i,str[i]);
        }
        //printf("str: %s\n", str);
        if(chdir(str)<0) {
            printf("No such file or directory\n");
        }
        else {
            log_push(&Log,buffer);
            return 1;
        }    
    }
    else if(buffer[0]=='e') {
        return 0;
    }
    else if(buffer[0]=='!'&&buffer[1]=='#') {
        node *p;
        p=Log.head;
        while(p!=NULL) {
            printf("%s\n",p->cmd);
            p=p->next;
        }
        return 1;
    }
    else if(buffer[0]=='!'&&buffer[1]!='#') {
        char str[100]={'\0'};
        int i,j;
        int len=strlen(buffer);
        for(i=0,j=1;j<len;i++,j++) {
            str[i]=buffer[j];
        }
        buffer=log_search(&Log,str);
        if(buffer==NULL) {
            printf("No Match\n");
        } else {
            execute(buffer);
        }
        return 1;
    }
    else if(buffer[0]=='l') {
        system("ls");
        log_push(&Log,buffer);
        return 1;
    }
    else {
        int i=0,j=0,k=0;
        char *argv[10];
        do{
            argv[j] = (char *)malloc(sizeof(char)*100);
            while(buffer[i]!=' '&&buffer[i]!='\0') {
                argv[j][k++]=buffer[i++];
            }
            argv[j++][k]='\0';
            k=0;
        }while(buffer[i++]!='\0');
        argv[j]=NULL;
        log_push(&Log,buffer);
        int pid=fork();
        if(pid>0) {

            int status;
            int ret=wait(&status);
            for(int i=0;argv[i]!=NULL;i++) {
                free(argv[i]);
            }
            return 1;
        } else if (pid == 0){
            int result=execv(argv[0],argv);
            if(result==-1)
                printf("%s: no such command\n",buffer);
            exit(0);
        }
    }
}