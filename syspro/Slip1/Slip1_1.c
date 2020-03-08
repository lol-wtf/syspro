#include<stdio.h>
#include<stdlib.h>


int main()
{
  FILE *fp;
  long mem[1000];
  int cmd[6]={0,0,0,0,0,1};
  int REG[4],pc=0,i,opcode,op1,op2,temp;
  char fname[20];
  
  printf("Enter the filename: ");
  scanf("%s",fname);
  
   fp=fopen(fname,"r");
   if(fp==NULL)
  {
  printf("cannot open the file");
     exit(0);
   }
    
     while(fscanf(fp,"%ld",&mem[pc++])!=EOF);
     fclose(fp);
   
     
     for(i=0;i<pc;i++)
     printf("%ld\n",mem[i]);
     pc=0;

     while(1)
   {
     opcode=mem[pc]/10000;
     temp=mem[pc];
     temp=temp%10000;
     op1=temp/1000;
     op2=temp%1000;
  
     switch(opcode)
 {
   case 0://STOP
           exit(0);
   case 1://ADD
           REG[op1-1]+=mem[op2];
           break;
   case 2://SUB
           REG[op1-1]-=mem[op2];
           break;
   case 3://MULT
           REG[op1-1]*=mem[op2];
           break;
   case 8://DIV
          REG[op1-1]/=mem[op2];
          break;
   case 4://MOVER
          REG[op1-1]=mem[op2];
          break;
   case 5://MOVEM
           mem[op2]= REG[op1-1];
           break;
   case 6://COMP
              if(REG[op1-1]<mem[op2])//LT
              cmd[0]=1;
              else
              cmd[0]=0;
              if(REG[op1-1]<=mem[op2])//LE
              cmd[1]=1;
              else
              cmd[1]=0;
              if(REG[op1-1]==mem[op2])//EQ
              cmd[2]=1;
              else
              cmd[2]=0;
              if(REG[op1-1]>mem[op2])//GT
              cmd[3]=1;
              else
              cmd[3]=0;
              if(REG[op1-1]>=mem[op2])//GE
              cmd[4]=1;
              else
              cmd[4]=0;
              break;
  case 7://BC
           if(cmd[op1]==1)
          {
             pc=op2;
             continue;
           }
          else
            break;
  case 9://READ
           printf("Enter value:");
           scanf("%d",&mem[op2]);
           break;
  case 10://PRINT
           printf("value=%d\n",mem[op2]);
    } //switch
   pc++;
  } //WHILE
  return(0);
 } //main

  
  


