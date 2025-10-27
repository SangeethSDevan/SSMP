#include <stdio.h>
struct process{
    int id;
    int at;
    int bt;
    int tat;
    int wt;
    int ct;
};
void sjf(struct process p[],int n){
    int time=0,completed=0,isComplete[n];
    float tatAvg=0,wtAvg=0;
    for(int i=0;i<n;i++){
        isComplete[i]=0;
    }
    while(completed<n){
        int sProcess=-1,shortestBT=-1;
        for(int i=0;i<n;i++){
            if(!isComplete[i]&&p[i].at<time){
                if(p[i].bt<shortestBT||shortestBT==-1){
                    sProcess=i;
                    shortestBT=p[i].bt;
                }
            }
        }
        if(sProcess==-1){
            time++;
            continue;
        }
        p[sProcess].ct=time+p[sProcess].bt;
        time=p[sProcess].ct;
        p[sProcess].tat=p[sProcess].ct-p[sProcess].at;
        p[sProcess].wt=p[sProcess].tat-p[sProcess].bt;
        completed++;
        isComplete[sProcess]=1;
    }
}