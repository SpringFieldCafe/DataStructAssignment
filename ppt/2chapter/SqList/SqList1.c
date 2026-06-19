#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef struct sqlist{
    char data[MaxSize];
    int size;
}SqList;

SqList* CreateList(){
    SqList* PList=(SqList*)malloc(sizeof(SqList));
    if(PList!=NULL){
        char ch;
        int count=0;
        while((ch=getchar())!=EOF && count<MaxSize && ch!='\n'){
            if(ch==' '){
                continue;
            }
        PList->data[count++]=ch;
        PList->size=count;
        }
        return PList;
    }
    else{
        printf("create fail!\n");
        return NULL;
    }
}

int ReadList(SqList* L){
    if(L==NULL){
        printf("error!\n");
        return 0;
    }
    printf("%d",L->size);
    int i;
    for(i=0;i<L->size;i++){
        printf("%c\t",L->data[i]);
    }
    return 1;
}

int DeleteItem(SqList* L,int p){
    int i=0,j=0;
    for(i;i<L->size;i++){
        if(L->data[i]==(char)p){
            j++;
        }
    }
}

int main(){
    SqList* array=CreateList();
    ReadList(array);
}