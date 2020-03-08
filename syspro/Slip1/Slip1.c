#include<stdio.h>
#include<stdlib.h>
#define MAX 20

int main()
{
	char FileName[MAX];
	long Mem[100];
	int  REG[4], OpCode, Operand, Reg, Cond[6]={0,0,0,0,0,1}, PC=0, i;
	FILE *fpSrc;

	printf("\nEnter Source File Name: ");
	scanf("%s",FileName);
	if((fpSrc=fopen(FileName,"r"))==NULL)
	{
		printf("\nError in opening file %s", FileName);
		exit(0);
	}
	while(fscanf(fpSrc,"%ld",&Mem[PC++])!=EOF);
	fclose(fpSrc);
	PC = 0;
	while(1)
	{
		OpCode = Mem[PC]/10000;
		Reg = (Mem[PC]%10000)/1000-1;
		Operand = (Mem[PC]%10000)%1000;
		switch(OpCode)
		{
			case 0:							// STOP
					exit(0);
			case 1:								// ADD
					REG[Reg] += Mem[Operand];
					break;
			case 2:							// SUB
					REG[Reg] -= Mem[Operand];
					break;
			case 3:								// MUL
					REG[Reg] *= Mem[Operand];
					break;
			case 4:								// MOVER
					REG[Reg] = Mem[Operand];
					break;
			case 5:								// MOVEM
					Mem[Operand] = REG[Reg];
					break;
			case 6:							// COMP
					if(REG[Reg] < Mem[Operand])
					{
						Cond[0] = 1;
					}
					if(REG[Reg] <= Mem[Operand])
					{
						Cond[1] = 1;
					}
					if(REG[Reg] == Mem[Operand])
					{
						Cond[2] = 1;
					}
					if(REG[Reg] > Mem[Operand])
					{
						Cond[3] = 1;
					}
					if(REG[Reg] >= Mem[Operand])
					{
						Cond[4] = 1;
					}
					break;
			case 7:							// BC
					if(Cond[Reg] == 1)
					{
						PC = Operand - 1;
					}
					for(i=0; i<5; i++)
						Cond[0] = 0;
					break;
			case 8:								// DIV
					REG[Reg] /= Mem[Operand];
					break;
			case 9:								// READ
					printf("\nEnter Value: ");
					scanf("%ld",&Mem[Operand]);
					break;
			case 10:							// PRINT
					printf("\nValue: %ld",Mem[Operand]);
					
					break;
		}
		PC++;
	}return(0);
}
