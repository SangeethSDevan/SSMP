#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE * fpOptab,*fpIntermed,*fpSymtab,*fpInput;
int optabSize=0,symtabSize=0,locctr=0,startAddress=0,totalSize=0;
char label[10],opcode[10],operand[10];
struct OpTab{
    char opcode[10];
    char hexcode[10];
}OT[10];
struct SymTab{
    char symbol[10];
    int addr;
}ST[10];
void readOptab(){
    while(fscanf(fpOptab,"%s %s",OT[optabSize].opcode,OT[optabSize].hexcode)!=EOF){
        optabSize++;
    }
}
int searchOptab(char * opcode){
    for(int i=0;i<optabSize;i++){
        if(strcmp(OT[i].opcode,opcode)==0) return 1;
    }
    return 0;
}
void readLine(char * label,char * opcode,char *operand){
    char line[100];
    label[0]='\0';
    opcode[0]='\0';
    operand[0]='\0';

    if(fgets(line,sizeof(line),fpInput)==NULL){
        strcpy(opcode,"END");
        return;
    }
    int count=sscanf(line,"%s %s %s",label,opcode,operand);
    if(count==1){
        strcpy(opcode,label);
        strcpy(label," ");
        strcpy(operand," ");    
    }else if(count==2){
        strcpy(operand,opcode);
        strcpy(opcode,label);
        strcpy(label," ");
    }
}
int main(){
    fpInput=fopen("input.txt","r");
    fpIntermed=fopen("intermed.txt","w");
    fpOptab=fopen("optab.txt","r");
    fpSymtab=fopen("symtab.txt","w");

    readOptab();
    readLine(label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        startAddress=(int) strtol(operand,NULL,16);
        locctr=startAddress;
        fprintf(fpIntermed,"\t%s\t%s\t%s\n",label,opcode,operand);
        readLine(label,opcode,operand);
    }else{
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0){
        fprintf(fpIntermed,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label," ")!=0){
            for(int i=0;i<symtabSize;i++){
                if(strcmp(ST[i].symbol,label)==0){
                    exit(1);
                }
            }
            strcpy(ST[symtabSize].symbol,label);
            ST[symtabSize].addr=locctr;
            symtabSize++;
        }
        if(searchOptab(opcode)){
            locctr+=3;
            totalSize+=3;
        }else if(strcmp(opcode,"WORD")==0){
            locctr+=3;
            totalSize+=3;
        }else if(strcmp(opcode,"RESW")==0){
            locctr+=3*atoi(operand);
        }else if(strcmp(opcode,"RESB")==0){
            locctr+=atoi(operand);
        }else if(strcmp(opcode,"BYTE")==0){
            int len=strlen(operand)-3;
            locctr+=len;
            totalSize+=len;
        }
        readLine(label,opcode,operand);
        printf("%x\n",locctr);
    }
    fprintf(fpIntermed,"\t%s\t%s\t%s",label,opcode,operand);
}