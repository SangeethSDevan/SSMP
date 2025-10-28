#include <stdio.h>
int abs(int x){
    return (x<0)?-x:x;
}
void scan(int requests[],int n,int head,int disk_size){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(requests[j]>requests[j+1]){
                int temp=requests[j];
                requests[j]=requests[j+1];
                requests[j+1]=temp;
            }
        }
    }
    int pos=0;
    while(pos<n&&requests[pos]<head){
        pos++;
    }
    printf("%d",head);
    int total_movement=0;
    int current=head;
    for(int i=pos;i<n;i++){
        printf(" -> %d",requests[i]);
        total_movement+=abs(current-requests[i]);
        current=requests[i];
    }
    if(current!=disk_size){
        printf(" -> %d",disk_size-1);
        total_movement+=abs(current-(disk_size-1));
        current=disk_size-1;
    }
    for(int i=pos-1;i>=0;i--){
        printf(" -> %d",requests[i]);
        total_movement+=abs(current-requests[i]);
        current=requests[i];
    }
    printf("Total disk movement: %d\n",total_movement);
}
int main(void){
    int requests[] = {100,50,10,200,75};
    scan(requests,5,60,250);
    return 0;
}