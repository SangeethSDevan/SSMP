#include <stdio.h>
int abs(int value){
    return value<0?-value:value;
}
void fcfs(int request[],int n,int head){
    printf("%d",head);
    int current=head;
    int totalMovement=0;
    for(int i=0;i<n;i++){
        printf(" -> %d",request[i]);
        totalMovement+=abs(current-request[i]);
        current=request[i];
    }
    printf("\nTotal head movement: %d\n",totalMovement);
}
int main(void){
    int requests[] = {100,50,10,200,75};
    fcfs(requests,5,60);
    return 0;
}