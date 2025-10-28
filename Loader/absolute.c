#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main(){
    FILE *fp=fopen("input.txt","r");
    char line[100];
    while(fscanf(fp,"%s",line)!=EOF){
        if(line[0]=='T'){
            char addstr[7]={0};
            strncpy(addstr,&line[1],6);
            int actual_address=(int)strtol(addstr,NULL,16);
            for(int i=9;line[i];i+=2){
                printf("%x\t%c%c\n",actual_address++,line[i],line[i+1]);
            }
        }
    }
}