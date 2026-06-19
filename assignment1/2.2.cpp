#include<stdio.h>
#include<time.h>
#define N 100000000
typedef unsigned long long li;

li force(unsigned int n){
    li sum=0;
    for(unsigned int i=1;i<n+1;i++){
        sum+=i;
    }
    return sum;
}

li Gaussian(unsigned int n){
    return ((li)n)*(n+1)/2;
}

void ShowTime(long b,long e){
    printf("time:   %f  \n",(double)(e-b)/CLOCKS_PER_SEC);
}


int main(){
    long begin,end;
    begin=clock();
    printf("%llu",force(N));
    end=clock();
    ShowTime(begin,end);

    begin=clock();
    printf("%llu",Gaussian(N));
    end=clock();
    ShowTime(begin,end);


    return 0;
}