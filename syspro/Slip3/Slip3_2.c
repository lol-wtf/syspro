#include<stdio.h>

int RefString[20],Frames[10],nor,nof;

void accept()
{
   printf("\n Enter length of Reference string :");
   scanf("%d",&nor);
   
   printf("\n Enter Number of Frames :");
   scanf("%d",&nof);
   
   printf("\n Enter reference String:\n");
   int i;
   
   for(0;i<nor;i++)
   {
      printf("[%d]: ",i+1);
      scanf("%d",&RefString[i]);
   }
}

 int isPageFault(int k)
 {
   int i;
    for(i=0;i<nof;i++)
    
      if(Frames[i]==k)
	return(i);
      return(-1);
 }
 
 
 int getLRU(int e)
 {
    int i,j,k,pos=99,posi;
    
     for(i=0;i<nof;i++)
     {
       for(j=e-1;j>=0;j--)
       {
	 if(Frames[i]==RefString[j])
	 {
	   if(j<pos)
	   {
	    pos=j;
	    posi=i;
	   }
	  break;
	 }
       }
     }
     return(posi);
 }
    
    
   void LRU()
   {
     int i,j,k,Pg_Fault=0;
     
     for(i=0,k=0;i<nor,k<nof;i++)
     {
       printf("\n Page No %2d",RefString[i]);
       
        if(isPageFault(RefString[i])==-1)
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
     if(isPageFault(RefString[i])==-1)
     {
       k=getLRU(i);
       Frames[k]=RefString[i];
       
       for(j=0;j<nof;j++)
       {
	 printf("%2d",RefString[i]);
       }
       Pg_Fault++;
     }
     i++;
   }
   printf("\nTotal No.Of page Fault=%d",Pg_Fault);
     }
   
main()
{
  accept();
  LRU();
}