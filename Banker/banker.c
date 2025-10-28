#include <stdio.h>
#define MAX 10

void getSafeSequence(int max[][MAX],int allocated[][MAX],int available[MAX],int process,int resources){
    int work[MAX],finish[MAX]={0},safeSequence[MAX];
    for(int i=0;i<resources;i++){
        work[i]=available[i];
    }
    int count=0;
    while(count<process){
        int found=0;
        for(int i =0;i<process;i++){
            int canBeAllocated=1;
            for(int j=0;j<resources;j++){
                if(max[i][j]-allocated[i][j]>work[j]){
                    canBeAllocated=0;
                    break;
                }
            }
            if(canBeAllocated){
                safeSequence[count++]=i;
                finish[i]=1;
                found=1;
            }
        }
        if(!found){
            printf("System is in unsafe state!");
        }
    }
}