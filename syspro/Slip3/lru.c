#include<stdio.h>


int RefString[20],Frames[10],nof,nor;

void Accept()
{
        printf("Enter Length of reference string: ");
	scanf("%d",&nor);
	printf("Enter No.of Frames: ");
	scanf("%d",&nof);
	
	int i;
	printf("Enter Reference String: \n");
	for(i=0;i<nor;i++)
	{
		printf("[%d]=",i+1);
		scanf("%d",&RefString[i]);
	}
}

int IsPageFault(int k)
{
	int i;
	for(i=0;i<nof; i++)
		if(Frames[i]==k)
			return(i);
	return(-1);
}

int GetLRU(int e)
{
	int i,j,Pos=99,Posi,k;
	for(i=0;i<nof;i++)
	{
		for(j=e-1;j>=0;j--)
		{
			if(Frames[i]==RefString[j])
			{
				if(j<Pos)
				{
					Pos=j;
					Posi=i;
				}
				break;
			}
		}
	}
	return(Posi);
}



void LRU()
{
	int i,j,k,Pg_Fault=0;

	for(i=0,k=0; i<nor && k<nof; i++)
	{
		printf("\nPage No %2d:",RefString[i]);
		
		if(IsPageFault(RefString[i])==-1)
		{
			Frames[k]=RefString[i];
			
			for(j=0;j<3;j++)
			{
				if(Frames[j])
					printf("%2d",Frames[j]);
			}


			Pg_Fault++;
			k++;
		}
	}
	
	while(i<nor)
	{
		printf("\nPage No %2d:",RefString[i]);
		
		if(IsPageFault(RefString[i])==-1)
		{
			k = GetLRU(i);
			Frames[k]=RefString[i];
		
			for(j=0;j<nof;j++)
			{
				printf("%2d",Frames[j]);
			}
			Pg_Fault++;
		}
		i++;
	}
	printf("\nTotal Page Faults: %d",Pg_Fault);
}

 void main()
{
	
	
	
	Accept();
	
	LRU();

	
}

