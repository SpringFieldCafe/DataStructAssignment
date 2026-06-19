#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10

typedef struct sqlist{
    char data[MaxSize];
    int Size;
}SqList;
int isList(SqList* list){
    return list==NULL;
}

SqList* CreateList(){
    SqList* PSqList=(SqList*)malloc(sizeof(SqList));
    int count=0;
    char ch;
    if (PSqList!=NULL){
        while((ch=getchar()) && count<MaxSize && ch!='\n'){
            if(ch==' '){
                continue;
            }
            PSqList->data[count++]=ch;
        }
        PSqList->Size=count;
    }
    else{
        exit(-1);
    }
    return PSqList;
}

void ReadList(SqList* begin){
    if(begin==NULL){
        return;
    }
    int i=0;
    for(;i<(begin->Size);i++){
        printf("%c\t",begin->data[i]);
    }
}

void Destroy(SqList* begin){
    if(!(isList(begin))){
        free(begin);
    }
    else{
        return;
    }
}



int getLength(SqList* list){
    if(isList(list)){
        return 0;
    }
    else{
        return list->Size;
    }

}

int GetItem(SqList* L,int i,char* e){
    if(isList(L)){
        return 0; 
    }
    if(i<0||i>getLength(L)){
        return 0;
    }
    *e=L->data[i];
    return 1;
}

int FindItem(SqList* L,char* p){
    if(L==NULL){
        return 0;
    }
    int i=0;
    for(;i<getLength(L);i++){
        if((L->data[i])==*p){
            return i;
        }
    }
    return 0;
}

int InsertItem(SqList* L,char* p,int i){
    if(L==NULL){
        return 0;
    }
    if(i<0||i>getLength(L)){
        return 0;
    }
    if(i>MaxSize-1){
        return 0;
    }
    int j;
    for(j=getLength(L);j>i;j--){
        L->data[j]=L->data[j-1];
    }
    L->data[j]=*p;
    (L->Size)++;
    return 1;
}

int DeleteItem(SqList* L,int i){
    if(L==NULL){
        return 0;
    }
    if(i<0||i>(L->Size)-1||i>MaxSize-1){
        return 0;
    }
    int j;
    for(j=i;j<(L->Size);j++){
        L->data[j]=L->data[j+1];
    }
    (L->Size)--;
    return 1;
}

int main(){
    SqList* array=CreateList();
    ReadList(array);
    char h=' ';
    int i;
    scanf("%d",&i);
    if(GetItem(array,i,&h)){
        printf("%c\n",h);
    }
    char k=' ';
    scanf(" %c",&k);
    int index=FindItem(array,&k);
    printf("%d\n",index);
    char l=' ';
    scanf(" %c",&l);
    if(InsertItem(array,&l,3)){
        printf("\n");
        ReadList(array);
    }
    if(DeleteItem(array,5)){
        printf("\n");
        ReadList(array);
    }
}