#include <stdio.h>
void display(int frames[],int f){
    for(int i=0;i<f;i++){
        if(frames[i]==-1){
            printf("-");
        }else{
            printf("%d",frames[i]);
        }
    }
    printf("\n");
}
void fifo(int pages[],int p,int f){
    int frames[f],index=0,pageFaults=0;
    for(int i=0;i<f;i++){
        frames[i]==-1;
    }
    for(int i=0;i<p;i++){
        int hit=0;
        for(int j=0;j<f;j++){
            if(pages[i]==frames[j]){
                hit=1;
                break;
            }
        }
        if(!hit){
            frames[index]=pages[i];
            index=(index+1)%f;
            pageFaults++;
        }
        display(frames,f);
    }
}