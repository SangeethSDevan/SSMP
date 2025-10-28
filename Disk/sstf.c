#include <stdio.h>
int abs(int x){
    return (x<0)?-x:x;
}
void sstf(int requests[],int n,int head){
    printf("%d",head);
    int completed=0,total_movement=0;
    int visited[100]={0};
    int current=head;
    while(completed<n){
        int min_distance=__INT_MAX__;
        int next_index=-1;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int distance=abs(requests[i]-current);
                if(distance<min_distance){
                    min_distance=distance;
                    next_index=i;
                }
            }
        }
        if(next_index!=-1){
            printf(" -> %d",requests[next_index]);
            total_movement+=min_distance;
            current=requests[next_index];
            visited[next_index]=1;
            completed++;
        }
    }
    printf("Total distance movement: %d\n",total_movement);
}
int main(){
    int requests[] = {100,50,10,200,75};
    sstf(requests,5,60);
}