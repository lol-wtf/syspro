#include<stdio.h>
#define MAX 20

int frames[MAX],ref[MAX],mem[MAX][MAX],count[MAX],sp,m,n,faults;

 void accept()
 {
    int i;
     
    printf("\n Enter the length of Reference String:");
    scanf("%d",&m);
    
    printf("\n Enter Number of Frames:");
    scanf("%d",&n);
    
    printf("Enter Reference String:\n");
    
    for(i=0;i<m;i++)
    {
      printf("[%d]:",i+1);
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
	printf("\n");
      }
      printf("\n Total Page Faults:%d\n",faults);
 }
 
 int search(int k)
 { 
   int i;
   for(i=0;i<n;i++)
   {
     if(frames[i]==k)
       return(i);
   }
     return(-1);
 }
 
 
 int get_mfu(int sp)
 {
   int i,pos=-9999,posi;
    i=sp;
    
    do
    {
      if(count[i]>pos)
      {
	pos=count[i];
	posi=i;
      }
      i=(i+1)%n;
    }while(i!=sp);
    return(posi);
 }
 
 void mfu()
 {
   int i,j,k;
   
   for(i=0;i<m && sp<n;i++)
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
     else count[k]++;
   }
   
   sp=0;
   for(;i<m;i++)
   {
     k=search(ref[i]);
     
     if(k==-1)
     {
       sp=get_mfu(sp);
       frames[sp]=ref[i];
       count[sp]=1;
       faults++;
       sp=(sp+1)%n;
       
       for(j=0;j<n;j++)
        mem[j][i]=frames[j];
     }
     else count[k]++;
   }
 }
 
 main()
 {
    accept();
    mfu();
    display();
 }