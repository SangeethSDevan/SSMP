#include <stdio.h>

struct process{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void sort(struct process p[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(p[j].at>p[j+1].at){
                struct process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}
void fcfs(struct process p[],int n){
    sort(p,n);
    int time=0;
    float tatAvg=0,wtAvg=0;
    for(int i=0;i<n;i++){
        if(time<p[i].at){
            time=p[i].at;
        }
        printf("P%d ( %d - %d )|",p[i].id,time,p[i].ct);
        p[i].ct=time+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        time=p[i].ct;

        tatAvg+=p[i].tat;
        wtAvg+=p[i].wt;
    }
    printf("Average waiting time: %f\n",wtAvg/n);
    printf("Average tat: %f\n",tatAvg/n);
}
