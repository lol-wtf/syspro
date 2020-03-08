#include<stdio.h>
#define MAX 20

int ref[MAX],frames[MAX],mem[MAX][MAX],count[MAX],m,n,sp,faults;


  void Accept()
{
	int i;

	printf("Enter no.of frames:");
	scanf("%d", &n);

	printf("Enter no.of references:");
	scanf("%d", &m);

	printf("Enter reference string:\n");
	
	for(i=0;i<m;i++)
	{
		printf("[%d]=",i);
		scanf("%d",&ref[i]);
	}
}

 void display()
 {
   int i,j;
   
    for(i=0;i<m;i++)
      printf("%3d",ref[i]);
    
      printf("\n\n");
     
     for(i=0;i<n;i++)
     {
       for(j=0;j<m;j++)
       { 
	 if(mem[i][j])
	   printf("%3d",mem[i][j]);
	 else 
	   printf("  ");
       }
       printf("\n\n");
     }
     printf("Total No. of page Faults:%d\n",faults);
 }
 
 int search(int k)
 {
   int i;
    for(i=0;i<n;i++)
      if(frames[i]==k)
	return(i);
      return(-1);
 }
 
 int get_lfu(int sp)
 {
   int i,pos=999,posi;
   
    i=sp;
     
    do
     {
       if(count[i]<pos)
       {
	 pos=count[i];
	 posi=i;
       }
       i=(i+1)%n;
     }while(i!=sp);
     
    return posi;
 }
 
  void LFU()
  {
    int i,j,k;
    
    for(i=0;i<m,sp<n;i++)
    {
      k=search(ref[i]);
      
       if(k==-1)
       {
	 frames[sp]=ref[i];
	 count[sp]++;
	 faults++;
	 sp++;
       
	 for(j=0;j<n;j++)
	   mem[j][i]=frames[j];
       }
       else
	 count[k++];
    }
    
    sp=0;
    for(;i<m;i++)
	{
		k = search(ref[i]);
		if(k==-1)
		{
			sp = get_lfu(sp);
			frames[sp] = ref[i];
			count[sp]=1;
			faults++;
			sp = (sp+1)%n;

			for(j=0;j<n;j++)
				mem[j][i] = frames[j];
		}
		else
			count[k]++;
	}
}

main()
{
  Accept();
  LFU();
  display();
}
       