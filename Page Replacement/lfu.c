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
int findLFU(int count[],int times[],int f){
    int min=count[0],pos=0;
    for(int i=0;i<f;i++){
        if(min>count[i]){
            min=count[i];
            pos=i;
        }else if(min==count[i]){
            if(times[i]<times[pos]){
                min=count[i];
                pos=i;
            }
        }
    }
    return pos;
}
void lfu(int pages[],int p,int f){
    int frames[f],count[f],times[f],pageFaults=0;
    for(int i=0;i<f;i++){
        frames[i]=-1;
        count[i]=0;
        times[i]=0;
    }
    for(int i=0;i<p;i++){
        int hit=0;
        for(int j=0;j<f;j++){
            if(frames[j]==pages[i]){
                hit=1;
                count[j]++;
                times[j]++;
                break;
            }
        }
        if(!hit){
            int pos=-1;
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    pos=j;
                    break;
                }
            }
            if(pos==-1){
                pos=findLFU(count,times,f);
            }
            frames[pos]=pages[i];
            count[pos]=1;
            times[pos]++;
            pageFaults++;
        }
        display(frames,f);
    }
}