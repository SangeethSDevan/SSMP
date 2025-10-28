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
int findLRU(int count[],int f){
    int min=count[0],pos=0;
    for(int i=0;i<f;i++){
        if(count[i]<min){
            pos=i;
        }
    }
    return pos;
}
void lru(int pages[],int p,int f){
    int frames[f],count[f],pageFaults=0;
    for(int i=0;i<f;i++){
        frames[i]=-1;
        count[i]=0;
    }
    for(int i=0;i<p;i++){
        int hit=0;
        for(int j=0;j<f;j++){
            if(pages[i]==frames[j]){
                hit=1;
                count[i]++;
                break;
            }
        }
        if(!hit){
            int pos=0;
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    pos=j;
                    break;
                }
            }
            if(pos==-1){
                pos=findLRU(count,f);
            }
            frames[pos]=pages[i];
            count[pos]=1;
            pageFaults++;
        }
        display(frames,f);
    }
}