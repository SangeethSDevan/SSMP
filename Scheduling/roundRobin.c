#include <stdio.h>
struct process{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};
void roundRobin(struct process p[],int n,int quantam){
    int time=0,completed=0,isComplete[n];
    float tatAvg=0,wtAvg=0;
    while(completed<n){
        int flag=0;
        for(int i=0;i<n;i++){
            if(p[i].at<time && !isComplete[i]){
                flag=1;
                if(p[i].rt<=quantam){
                    p[i].ct=time+p[i].rt;
                    time=p[i].ct;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                    completed++;
                    isComplete[i]=1;
                }else{
                    p[i].rt-=quantam;
                    time+=quantam;
                }
            }
        }
        if(flag==0){
            time++;
        }
    }
}