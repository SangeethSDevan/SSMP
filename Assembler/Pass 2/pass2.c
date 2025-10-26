#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_to_hex(int value,char * buffer){
    sprintf(buffer,"%02x",value);
}
void main(){
    FILE *fpAssmlist,*fpIntermed,*fpSymtab,*fpObjcode;
    int address=0,start_address=0,prev_address=0,final_address=0,sym_address=0;
    char label[20],opcode[20],operand[20],symbol[20],buffer[10];
    char mnemonics[15][15]={"LDA","STA","LDCH","STCH"};
    char code[15][15]={"33","44","53","57"};

    fpAssmlist=fopen("assmlist.txt","w");
    fpIntermed=fopen("intermed.txt","r");
    fpObjcode=fopen("objcode.txt","w");
    fpSymtab=fopen("symtab.txt","r");

    fscanf(fpIntermed,"%s%s%s",label,opcode,operand);
    while(strcmp(opcode,"END")!=0){
        prev_address=address;
        fscanf(fpIntermed,"%d%s%s%s",&address,label,opcode,operand);
    }
    final_address=address;
    fclose(fpIntermed);
    
    fpIntermed=fopen("intermed.txt","r");
    fscanf(fpIntermed,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        fprintf(fpObjcode,"H^%s^00%s^00%x\n",label,operand,final_address);
        fprintf(fpAssmlist,"\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fpIntermed,"%d%s%s%s",&address,label,opcode,operand);
        start_address=address;
        int diff=prev_address-start_address;
        fprintf(fpObjcode,"T^%02x^%02x",address,diff);
    }
    while(strcmp(opcode,"END")!=0){
        if(strcmp(opcode,"BYTE")==0){
            fprintf(fpAssmlist,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
            int len=strlen(operand)-3;
            fprintf(fpObjcode,"^");
            for(int i=2;i<len+2;i++){
                int_to_hex(operand[i],buffer);
                fprintf(fpAssmlist,"%s",buffer);
                fprintf(fpObjcode,"%s",buffer);
            }
            fprintf(fpAssmlist,"\n");
        }else if(strcmp(opcode,"WORD")==0){
            sprintf(buffer,"%06d",atoi(operand));
            fprintf(fpAssmlist,"%d\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,buffer);
            fprintf(fpObjcode,"^%s",buffer);
        }else if(strcmp(opcode,"RESB")==0 || strcmp(opcode,"RESW")==0){
            fprintf(fpAssmlist,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
        }else{
            int j=0;
            while(strcmp(opcode,mnemonics[j])!=0 && j<15){
                j++;
            }
            if(strcmp(operand,"COPY")==0){
                fprintf(fpAssmlist,"%d\t%s\t%s\t%s\t%s0000\n",address,label,opcode,operand,code[j]);
            }else{
                rewind(fpSymtab);
                fscanf(fpSymtab,"%s%d",symbol,&sym_address);
                while(strcmp(operand,symbol)!=0 && !feof(fpSymtab)){
                    fscanf(fpSymtab,"%s%d",symbol,&sym_address);
                }
                fprintf(fpAssmlist,"%d\t%s\t%s\t%s\t%s%x",address,label,opcode,operand,code[j],sym_address);
                fprintf(fpObjcode,"^%s%x",code[j],sym_address);
            }
        }
        fscanf(fpIntermed,"%d%s%s%s",&address,label,opcode,operand);
    }
    fprintf(fpAssmlist,"%d\t%s\t%s\t%s\t%s\n",address,label,opcode,operand);
    fprintf(fpObjcode,"\nE^%02x\n",start_address);
    fclose(fpAssmlist);
    fclose(fpIntermed);
    fclose(fpObjcode);
    fclose(fpSymtab);
}