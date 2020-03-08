#include<stdio.h>
#include<stdlib.h>

int main()
{
  FILE *fp;
  long mem[1000];
  int cmd[6]={0,0,0,0,0,1};
  int REG[4],pc=0,i,op1,op2,opcode,temp;
  char fname[20];
  
  printf("Enter file Name: ");
  scanf("%s",fname);
  
  fp=fopen(fname,"r");
  
   if(fp==NULL)
   {
     printf("Cannot open file");
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
       case 0:exit(0);
       
       case 1:printf("Enter Value:");
              scanf("%ld",&mem[op2]);
	      break;
       case 2:
	      printf("Value=%ld",mem[op2]);
	      break;
	      
       case 3:
	      REG[op1-1] +=mem[op2];
	      break;
	      
       case 4:
	      REG[op1-1] -=mem[op2];
	      break;
       case 5:
	      REG[op1-1] =mem[op2];
	      break;
       case 6:
	      mem[op2] =REG[op1-1];
	      break;
      case 7:
	      REG[op1-1] *=mem[op2];
	      break;
      case 8:
	      REG[op1-1] /=mem[op2];
	      break;
      case 9:
	     if(cmd[op1]==1)
	     {
	       pc=op2;
	       continue;
	     }
	     else
	       break;
      case 10:
	      if(REG[op1-1]<mem[op2])
		cmd[0]=1;
	      else
		cmd[0]=0;
		if(REG[op1-1]<=mem[op2])
		cmd[1]=1;
	      else
		cmd[1]=0;
		if(REG[op1-1]==mem[op2])
		cmd[2]=1;
	      else
		cmd[2]=0;
		if(REG[op1-1]>mem[op2])
		cmd[3]=1;
	      else
		cmd[3]=0;
		if(REG[op1-1]>=mem[op2])
		cmd[4]=1;
	      else
		cmd[4]=0;
	       break;
	      
     }
     pc++;
   }
   return(0);
}		
	      
